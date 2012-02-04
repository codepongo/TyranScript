#include <tyranscript/tyran_runtime.h>
#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_opcode.h>
#include <tyranscript/tyran_scope_stack.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_scope.h>
#include <tyranscript/tyran_object_iterator.h>
#include <tyranscript/tyran_object_array.h>
#include <tyranscript/tyran_object.h>

#include "tyran_runtime_helper.h"
#include "tyran_value_convert.h"
#include "tyran_stack.h"
#include <tyranscript/tyran_runtime_callbacks.h>

#include "debug/tyran_print_runtime.h"
#include <tyranscript/debug/tyran_print_value.h>

/* #define TYRAN_RUNTIME_VERBOSE */

void tyran_runtime_execute(tyran_runtime* runtime, const tyran_opcodes* opcodes, tyran_scope_stack* scope, tyran_value* current_scope, tyran_value* _this, tyran_value* return_value, const tyran_runtime_callbacks* eventCallbacks)
{
	const tyran_opcode* ip = &opcodes->codes[0];
	tyran_opcode* end = &opcodes->codes[opcodes->code_len];

	tyran_value* stack = runtime->stack;
	int sp = runtime->stack_pointer;

	
	tyran_value_set_undefined(*return_value);

	while(ip < end) {
#ifdef TYRAN_RUNTIME_VERBOSE
		tyran_print_runtime(stack, sp, _this, ip, ip - opcodes->codes);
#endif
		switch(ip->opcode) {
			case TYRAN_OPCODE_MAX_ID:
			case TYRAN_OPCODE_INTERNAL:
				TYRAN_ERROR("Illegal opcode");
				break;
			case TYRAN_OPCODE_NOP:
				break;
			case TYRAN_OPCODE_PUSH_NUMBER:
				tyran_value_set_number(stack[sp], (*((const double *)ip->data.pointer)));
				sp++;
				break;
			case TYRAN_OPCODE_PUSH_STRING:
				tyran_value_set_string(stack[sp], tyran_string_strdup((const tyran_string*)ip->data.pointer));
				sp++;
				break;
			case TYRAN_OPCODE_PUSH_VARIABLE: {
				const tyran_variable_name_info* info = (const tyran_variable_name_info*) ip->data.pointer;
				const tyran_string* variable_name = info->data.variable_name;
				const tyran_object_key* requested_key = (const tyran_object_key*) variable_name;
				tyran_value* value = tyran_value_object_lookup(current_scope, requested_key, 0);
				if (!value) {
					value = tyran_scope_stack_lookup(scope, requested_key);
					if (!value) {
						tyran_value* key = tyran_value_new();
						tyran_value_set_string(*key, variable_name);

						tyran_value* undefined = tyran_value_new();
						tyran_value_set_undefined(*undefined);
						value = tyran_value_object_insert_key_and_flag(current_scope, key, undefined, 0);
					} else {
					}
				}
				tyran_value_set_variable(stack[sp], value);
				sp++;
				break;
			}
			case TYRAN_OPCODE_PUSH_UNDEFINED:
				tyran_value_set_undefined(stack[sp]);
				sp++;
				break;
			case TYRAN_OPCODE_PUSH_BOOLEAN:
				tyran_value_set_boolean(stack[sp], ip->data.integer);
				sp++;
				break;
			case TYRAN_OPCODE_PUSH_FUNCTION: {
				tyran_function_object* fo = tyran_function_object_new((const tyran_function *)ip->data.pointer);
				fo->scope = tyran_scope_stack_clone_and_add(scope, current_scope);

				tyran_object* object = tyran_object_new();
				tyran_object_set_function(object, fo);

				tyran_value* function_prototype = tyran_value_object_new();
				tyran_value_object_set_prototype(function_prototype, tyran_object_prototype);

				tyran_value_set_object(stack[sp], object);
				tyran_value_object_set_prototype(&stack[sp], function_prototype);
				sp++;
				break;
			}
			case TYRAN_OPCODE_PUSH_SCOPE:
				tyran_value_copy(stack[sp], *current_scope);
				sp++;
				break;
			case TYRAN_OPCODE_PUSH_THIS:
				tyran_value_copy(stack[sp], *_this);
				sp++;
				break;
			case TYRAN_OPCODE_PUSH_TOP:
				tyran_value_copy(stack[sp], TYRAN_STACK_TOP);
				sp++;
				break;
			case TYRAN_OPCODE_PUSH_TOP2:
				tyran_value_copy(stack[sp], TYRAN_STACK_TOP2);
				tyran_value_copy(stack[sp + 1], TYRAN_STACK_TOP);
				sp += 2;
				break;
			case TYRAN_OPCODE_POP:
				TYRAN_STACK_POP_N(ip->data.integer);
				break;
			case TYRAN_OPCODE_NEGATE:
				TYRAN_STACK_TOP_VARIABLE_TO_VALUE();
				TYRAN_ASSERT(tyran_value_is_number(&TYRAN_STACK_TOP), "Can only negate numbers");
				TYRAN_STACK_TOP.data.number = -(TYRAN_STACK_TOP.data.number);
				break;
			case TYRAN_OPCODE_NOT: {
				int value;
				TYRAN_STACK_TOP_VARIABLE_TO_VALUE();
				value = tyran_value_is_true(&TYRAN_STACK_TOP);
				tyran_value_replace_boolean(TYRAN_STACK_TOP, !value);
				break;
			}
			case TYRAN_OPCODE_ADD: {
				TYRAN_STACK_TOP2_VARIABLE_TO_VALUE();

				if (tyran_value_is_string(&TYRAN_STACK_TOP) || tyran_value_is_string(&TYRAN_STACK_TOP2)) {
					tyran_value_convert_to_string(&TYRAN_STACK_TOP);
					tyran_value_convert_to_string(&TYRAN_STACK_TOP2);

					const tyran_string* str = tyran_string_strcat(TYRAN_STACK_TOP2.data.str, TYRAN_STACK_TOP.data.str);

					tyran_value_replace_string(TYRAN_STACK_TOP2, str);
				} else {
					double value = TYRAN_STACK_TOP.data.number + TYRAN_STACK_TOP2.data.number;
					tyran_value_replace_number(TYRAN_STACK_TOP2, value);
				}
				TYRAN_STACK_POP();
				break;
			}
			case TYRAN_OPCODE_SUBTRACT:
				tyran_runtime_arithmetic(-);
				break;
			case TYRAN_OPCODE_MULTIPLY:
				tyran_runtime_arithmetic(*);
				break;
			case TYRAN_OPCODE_DIVIDE:
				tyran_runtime_arithmetic(/);
				break;
			case TYRAN_OPCODE_MODULUS: {
				TYRAN_STACK_TOP2_VARIABLE_TO_VALUE();
				TYRAN_STACK_TOP2.data.number = fmod(TYRAN_STACK_TOP2.data.number, TYRAN_STACK_TOP.data.number);
				TYRAN_STACK_POP();
				break;
			}
			case TYRAN_OPCODE_INCREASE:
			case TYRAN_OPCODE_DECREASE: {
				int delta = ip->opcode == TYRAN_OPCODE_INCREASE ? 1 : -1;
				tyran_value* variable = TYRAN_STACK_TOP.data.variable;
				variable->data.number += delta;
				TYRAN_STACK_TOP_VARIABLE_TO_VALUE();
				if (ip->data.integer) {
					TYRAN_STACK_TOP.data.number -= delta;
				}
				break;
			}
			case TYRAN_OPCODE_BITWISE_NOT: {
				TYRAN_STACK_TOP_VARIABLE_TO_VALUE();
				TYRAN_STACK_TOP.data.number = (double)(~(tyran_value_to_integer(&TYRAN_STACK_TOP)));
				break;
			}
			case TYRAN_OPCODE_BITWISE_AND:
				tyran_runtime_bitwise_operation(&);
				break;
			case TYRAN_OPCODE_BITWISE_OR:
				tyran_runtime_bitwise_operation(|);
				break;
			case TYRAN_OPCODE_BITWISE_XOR:
				tyran_runtime_bitwise_operation(^);
				break;
			case TYRAN_OPCODE_BITWISE_SHIFT: {
				TYRAN_STACK_TOP2_VARIABLE_TO_VALUE();
				int value = tyran_value_to_integer(&TYRAN_STACK_TOP2);
				int shift_steps = ((unsigned int) tyran_value_to_integer(&TYRAN_STACK_TOP)) & 0x1f;
				enum tyran_shift_mode mode = (enum tyran_shift_mode)ip->data.integer;
				switch (mode) {
					case tyran_shift_left:
						value <<= shift_steps;
						tyran_value_set_number(TYRAN_STACK_TOP2, value);
						break;
					case tyran_shift_right_unsigned: {
						unsigned int unsigned_value = (unsigned int) value;
						unsigned_value >>= shift_steps;
						tyran_value_set_number(TYRAN_STACK_TOP2, unsigned_value);
						break;
					}
					case tyran_shift_right:
						value >>= shift_steps;
						tyran_value_set_number(TYRAN_STACK_TOP2, value);
						break;
				}
				TYRAN_STACK_POP();
				break;
			}
			case TYRAN_OPCODE_COMPARE_LESS:
				TYRAN_STACK_TOP2_VARIABLE_TO_VALUE();
				tyran_runtime_logical_less(TYRAN_STACK_TOP2, TYRAN_STACK_TOP, &TYRAN_STACK_TOP2);
				TYRAN_STACK_POP();
				break;
			case TYRAN_OPCODE_COMPARE_GREATER:
				TYRAN_STACK_TOP2_VARIABLE_TO_VALUE();
				tyran_runtime_logical_less(TYRAN_STACK_TOP, TYRAN_STACK_TOP2, &TYRAN_STACK_TOP2);
				TYRAN_STACK_POP();
				break;
			case TYRAN_OPCODE_COMPARE_LESS_EQUAL:
				TYRAN_STACK_TOP2_VARIABLE_TO_VALUE();
				tyran_runtime_logical_less(TYRAN_STACK_TOP, TYRAN_STACK_TOP2, &TYRAN_STACK_TOP2);
				TYRAN_STACK_TOP2.data.boolean = !TYRAN_STACK_TOP2.data.boolean;
				TYRAN_STACK_POP();
				break;
			case TYRAN_OPCODE_COMPARE_GREATER_EQUAL:
				TYRAN_STACK_TOP2_VARIABLE_TO_VALUE();
				tyran_runtime_logical_less(TYRAN_STACK_TOP2, TYRAN_STACK_TOP, &TYRAN_STACK_TOP2);
				TYRAN_STACK_TOP2.data.boolean = !TYRAN_STACK_TOP2.data.boolean;
				TYRAN_STACK_POP();
				break;
			case TYRAN_OPCODE_COMPARE_NOT_EQUAL:
			case TYRAN_OPCODE_COMPARE_EQUAL: {
				int b = 0;
				TYRAN_STACK_TOP2_VARIABLE_TO_VALUE();
				if (tyran_value_is_same_type(&TYRAN_STACK_TOP, &TYRAN_STACK_TOP2)) {
					switch (TYRAN_STACK_TOP.type) {
						case TYRAN_VALUE_TYPE_UNDEFINED:
						case TYRAN_VALUE_TYPE_NULL:
							b = 1;
							break;
						case TYRAN_VALUE_TYPE_NUMBER:
							b = (TYRAN_STACK_TOP.data.number == TYRAN_STACK_TOP2.data.number);
							break;
						case TYRAN_VALUE_TYPE_BOOLEAN:
							b = (TYRAN_STACK_TOP.data.boolean == TYRAN_STACK_TOP2.data.boolean);
							break;
						case TYRAN_VALUE_TYPE_STRING:
							b = (tyran_string_strcmp(TYRAN_STACK_TOP2.data.str, TYRAN_STACK_TOP.data.str) == 0);
						break;
						case TYRAN_VALUE_TYPE_OBJECT:
							b = (TYRAN_STACK_TOP.data.object == TYRAN_STACK_TOP2.data.object);
							break;
						default:
							TYRAN_ERROR("Illegal value to compare with");
					}
				}
				b = (ip->opcode == TYRAN_OPCODE_COMPARE_EQUAL) ? b : !b;
				tyran_value_replace_boolean(TYRAN_STACK_TOP2, b);
				TYRAN_STACK_POP();
				break;
			}
			case TYRAN_OPCODE_JUMP_TRUE:
			case TYRAN_OPCODE_JUMP_FALSE:
			case TYRAN_OPCODE_JUMP_TRUE_POP:
			case TYRAN_OPCODE_JUMP_FALSE_POP: {
				TYRAN_STACK_TOP_VARIABLE_TO_VALUE();
				int offset = ip->data.integer - 1;
				int r = tyran_value_is_true(&TYRAN_STACK_TOP);

				if (ip->opcode == TYRAN_OPCODE_JUMP_TRUE_POP || ip->opcode == TYRAN_OPCODE_JUMP_FALSE_POP) {
					TYRAN_STACK_POP();
				}
				ip += ((ip->opcode == TYRAN_OPCODE_JUMP_TRUE_POP || ip->opcode == TYRAN_OPCODE_JUMP_TRUE) ^ r) ? 0 : offset;
				break;
			}
			case TYRAN_OPCODE_JUMP_POP:
				TYRAN_STACK_POP_N(((tyran_jump_pop_info *)ip->data.pointer)->pop_count);
			case TYRAN_OPCODE_JUMP: {
				int offset = ip->opcode == TYRAN_OPCODE_JUMP ? ip->data.integer - 1 : ((tyran_jump_pop_info *)ip->data.pointer)->offset - 1;
				ip += offset;
				break;
			}
			case TYRAN_OPCODE_CALL:
			case TYRAN_OPCODE_NEW: {
				int is_constructor_call = (ip->opcode == TYRAN_OPCODE_NEW);
				int argument_count = ip->data.integer;
				TYRAN_STACK_TOP_N_VARIABLE_TO_VALUE(argument_count + 1);

				/* Find the function object */
				int function_object_index = sp - argument_count - 1;
				tyran_value* function_object_to_call = &stack[function_object_index];
				
				const tyran_function* static_function = function_object_to_call->data.object->data.function->static_function;

				/* Create a new function scope */
				tyran_value* function_scope = tyran_value_new();
				tyran_value_set_object(*function_scope, tyran_object_new_array((const tyran_value*)&stack[sp - argument_count], argument_count));

				/* Set the name for the arguments (not just the indexes) */
				tyran_scope_set_variable_names(function_scope, static_function->argument_names);

				/* Fill scope with local variables */
				tyran_scope_set_local_variables(function_scope, static_function);

				TYRAN_STACK_POP_N(argument_count);

				if (is_constructor_call) {
					tyran_value* newvalue = tyran_value_new();
					tyran_object* newobj = tyran_object_new();
					tyran_value* function_object_prototype = tyran_object_get_prototype(function_object_to_call->data.object);
					if (function_object_prototype && function_object_prototype->type == TYRAN_VALUE_TYPE_OBJECT) {
						tyran_object_set_prototype(newobj, function_object_prototype);
					} else {
						tyran_object_set_prototype(newobj, tyran_object_prototype);
					}

					tyran_print_value("new prototype", tyran_object_get_prototype(newobj), 1);

					tyran_value_set_object(*newvalue, newobj);

					_this = newvalue;
				}

				tyran_value return_value;
				tyran_value_set_undefined(return_value);

				if (static_function->type == tyran_function_type_normal) {
					runtime->stack_pointer = sp;
					tyran_runtime_execute(runtime, static_function->data.opcodes, function_object_to_call->data.object->data.function->scope, function_scope, _this, &return_value, eventCallbacks);
				} else {
					static_function->data.callback(runtime, function_object_to_call, function_scope, _this, &return_value, is_constructor_call);
				}

				if (is_constructor_call) {
					tyran_value_replace(return_value, *_this);
				}

				tyran_value_replace(TYRAN_STACK_TOP, return_value);
				tyran_value_free(function_scope);
				break;
			}
			case TYRAN_OPCODE_RETURN: {
				TYRAN_STACK_TOP_VARIABLE_TO_VALUE();
				tyran_value_copy(*return_value, TYRAN_STACK_TOP);
				TYRAN_STACK_POP_N(ip->data.integer);
				return;
			}
			case TYRAN_OPCODE_MAKE_OBJECT: {
				int value_count = ip->data.integer * 2;		
				TYRAN_STACK_TOP_N_VARIABLE_TO_VALUE(value_count);
				tyran_object* object = tyran_object_new_from_items(&stack[sp - value_count], value_count);
				TYRAN_STACK_POP_N(value_count- 1);
				tyran_value_replace_object(TYRAN_STACK_TOP, object);
				break;
			}
			case TYRAN_OPCODE_MAKE_ARRAY: {
				int itemcount = ip->data.integer;
				TYRAN_STACK_TOP_N_VARIABLE_TO_VALUE(itemcount);
				tyran_object* object = tyran_object_new_array(&stack[sp - itemcount], itemcount);
				TYRAN_STACK_POP_N(itemcount - 1);
				tyran_value_replace_object(TYRAN_STACK_TOP, object);
				break;
			}
			case TYRAN_OPCODE_DELETE: {
				enum tyran_assign_mode mode = (enum tyran_assign_mode) ip->data.integer;
				switch (mode) {
					case tyran_assign_variable: {
						tyran_value* v = TYRAN_STACK_TOP.data.variable;
						tyran_value_release(*v);
						TYRAN_STACK_POP();
						}
						break;
					case tyran_assign_object:
						TYRAN_STACK_TOP2_VARIABLE_TO_VALUE();
						tyran_value_object_delete(&TYRAN_STACK_TOP2, &TYRAN_STACK_TOP);
						TYRAN_STACK_POP();
						TYRAN_STACK_POP();
						break;
				}
				break;
			}
			case TYRAN_OPCODE_ASSIGN: {
				if (((enum tyran_assign_mode) ip->data.integer) == tyran_assign_variable) {
					TYRAN_STACK_TOP_VARIABLE_TO_VALUE();
					tyran_value_replace(*(TYRAN_STACK_TOP2.data.variable), TYRAN_STACK_TOP);
					tyran_value_replace(TYRAN_STACK_TOP2, TYRAN_STACK_TOP);
					TYRAN_STACK_POP();
				} else {
					TYRAN_STACK_TOP_N_VARIABLE_TO_VALUE(3);
					tyran_value_object_insert_key_and_flag(&stack[sp - 3], &TYRAN_STACK_TOP2, &TYRAN_STACK_TOP, 0);
					if (stack[sp-3].data.object->flags == 1 && eventCallbacks != 0) {
						eventCallbacks->assign_callback(runtime, &stack[sp-3], &TYRAN_STACK_TOP2, &TYRAN_STACK_TOP);
 					}
					tyran_value_replace(stack[sp - 3], TYRAN_STACK_TOP);
					TYRAN_STACK_POP_N(2);
				}
				break;
			}
			case TYRAN_OPCODE_UNREFERENCE:
				TYRAN_STACK_TOP_VARIABLE_TO_VALUE();
				break;
			case TYRAN_OPCODE_SUBSCRIPT: {
				TYRAN_STACK_TOP2_VARIABLE_TO_VALUE();
				tyran_value result;
				tyran_value_set_undefined(result);
				tyran_runtime_value_object_subscript(&TYRAN_STACK_TOP2, &TYRAN_STACK_TOP, &result, (enum tyran_subscript_mode) ip->data.integer);
				tyran_value_replace(TYRAN_STACK_TOP2, result);
				TYRAN_STACK_POP();
				break;
			}
			case TYRAN_OPCODE_KEY: {
				TYRAN_STACK_TOP_VARIABLE_TO_VALUE();
				tyran_value result;
				tyran_value_object_fetch_key_iterator(&TYRAN_STACK_TOP, &result);
				stack[sp] = result;
				sp++;
				break;
			}
			case TYRAN_OPCODE_NEXT: {
				tyran_object_iterator* iterator = TYRAN_STACK_TOP2.data.object->data.iterator;

				while (iterator->iterator < iterator->count) {
					if (tyran_value_object_has_key(&stack[sp-3], iterator->keys[iterator->iterator])) break;
					iterator->iterator++;
				}

				if (iterator->iterator == iterator->count) {
					tyran_value_replace_number(TYRAN_STACK_TOP, 0);
				} else {
					tyran_value_replace_string(*TYRAN_STACK_TOP.data.variable, tyran_string_strdup(iterator->keys[iterator->iterator]));
					tyran_value_replace_number(TYRAN_STACK_TOP, 1);
					iterator->iterator++;
				}
				break;
			}
			case TYRAN_OPCODE_LOAD_THIS: {
				_this = (&TYRAN_STACK_TOP2)->data.variable;
				break;
			}
		}
		ip++;
	}
}
