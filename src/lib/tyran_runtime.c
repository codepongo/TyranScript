#include "tyran_runtime_macros.h"
#include <tyranscript/tyran_configuration.h>


#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_runtime.h>
#include <tyranscript/tyran_opcode_ids.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_runtime_stack.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_constants.h>
#include <tyranscript/tyran_number_operator.h>

#include <tyranscript/debug/tyran_print_runtime_state.h>

#if defined TYRAN_CONFIGURATION_DEBUG
#define TYRAN_RUNTIME_DEBUG
#endif

#define TYRAN_RUNTIME_INVOKE_BINARY_OPERATOR(DESTINATION, OBJECT, PARAMS, PARAM_COUNT, OPERATOR) \
	{ tyran_value member; \
	tyran_object_lookup_prototype(&member, (OBJECT).data.object, &runtime->binary_operator_symbols[OPERATOR]); \
	TYRAN_ASSERT(!tyran_value_is_nil(&member), "Couldn't find operator:%d %d", OPERATOR, runtime->binary_operator_symbols[OPERATOR].hash); \
	const tyran_function* function = member.data.object->data.function->static_function; \
	function->data.callback(runtime, &member, PARAMS, PARAM_COUNT, &OBJECT, DESTINATION, TYRAN_FALSE); }

#define TYRAN_RUNTIME_INVOKE_UNARY_OPERATOR(DESTINATION, OBJECT, OPERATOR) \
	{ tyran_value member; \
	tyran_object_lookup_prototype(&member, (OBJECT).data.object, &runtime->binary_operator_symbols[OPERATOR]); \
	TYRAN_ASSERT(!tyran_value_is_nil(&member), "Couldn't find operator:%d %d", OPERATOR, runtime->binary_operator_symbols[OPERATOR].hash); \
	const tyran_function* function = member.data.object->data.function->static_function; \
	function->data.callback(runtime, &member, 0, 0, &OBJECT, DESTINATION, TYRAN_FALSE); }

void tyran_register_copy(tyran_value* target, tyran_value* source, int count)
{
	for (int i=0; i<count; ++i) {
		tyran_value_replace(target[i], source[i]);
	}
}

#define TYRAN_RUNTIME_DO_JMP \
	instruction = *pc++; \
	instruction >>= 5; \
	TYRAN_REGISTER_BR; \
	pc += br;

void tyran_runtime_execute(tyran_runtime* runtime, struct tyran_value* return_value, const struct tyran_runtime_callbacks* event_callbacks)
{
	u8t a;
	u8t x;
	u8t y;
	u8t xc;
	u8t yc;
	int br;
	int b;
	tyran_value rcx;
	tyran_value rcy;
	int i;
//	int argument_count;
	int test;
	tyran_object* object;
	tyran_value* r;
	tyran_runtime_stack* sp = &runtime->stack[runtime->stack_pointer];
	const tyran_opcode* pc;
	const tyran_value* c;

	TYRAN_STACK_POP
	tyran_runtime_stack* base_sp = sp;

	tyran_value_set_nil(*return_value);
	tyran_value_copy(r[0], sp->_this);

	while (1) {
#ifdef TYRAN_RUNTIME_DEBUG
		tyran_print_runtime_state(pc, sp, r);
#endif
		u32t instruction = *pc++;
		u32t opcode = instruction & 0x1f;
		instruction >>= 5;

		switch (opcode) {
			case TYRAN_OPCODE_LD:
				TYRAN_REGISTER_A_X;
				tyran_value_replace(r[a], r[x]);
				break;
			case TYRAN_OPCODE_LDC:
				TYRAN_REGISTER_A_X;
				tyran_value_replace(r[a], c[x]);
				break;
			case TYRAN_OPCODE_LDCU:
				TYRAN_REGISTER_A_X;
				if (tyran_value_is_nil(&r[a])) {
					tyran_value_replace(r[a], c[x]);
				}
				break;
			case TYRAN_OPCODE_ADD:
			case TYRAN_OPCODE_DIV:
			case TYRAN_OPCODE_MOD:
			case TYRAN_OPCODE_MUL:
			case TYRAN_OPCODE_POW:
			case TYRAN_OPCODE_SUB:
			case TYRAN_OPCODE_INDEX: {
				TYRAN_REGISTER_A_RCX_RCY;
				int operator_index = opcode - TYRAN_OPCODE_ADD;
				if (tyran_value_is_number(&rcx)) {
					tyran_number_operator_binary(&r[a], operator_index, rcx.data.number, rcy.data.number);
				} else {
					TYRAN_RUNTIME_INVOKE_BINARY_OPERATOR(&r[a], rcx, &rcy, 1, operator_index);
				}
			}
			break;
			case TYRAN_OPCODE_INDEX_SET: {
				TYRAN_REGISTER_A_RCX_RCY;
				int operator_index = opcode - TYRAN_OPCODE_ADD;
				if (tyran_value_is_number(&r[a])) {
					tyran_number_operator_binary(&r[a], operator_index, rcx.data.number, rcy.data.number);
				} else {
					tyran_value temp[2];
					tyran_value_copy(temp[0], rcx);
					tyran_value_copy(temp[1], rcy);
					TYRAN_RUNTIME_INVOKE_BINARY_OPERATOR(0, r[a], temp, 2, operator_index);
				}
			}
			break;
			case TYRAN_OPCODE_ITER: {
				TYRAN_REGISTER_A_RCX;
				TYRAN_RUNTIME_INVOKE_UNARY_OPERATOR(&r[a], rcx, 11);
			}
			break;
			case TYRAN_OPCODE_NEXT: {
				TYRAN_REGISTER_A_RCX;
				TYRAN_RUNTIME_INVOKE_UNARY_OPERATOR(&r[a], rcx, 12);
				if (!tyran_value_is_nil(&r[a])) {
					pc++;
				}
			}
			break;
			case TYRAN_OPCODE_NEG:
				TYRAN_REGISTER_A_RCX;
				tyran_value_replace_number(r[a], -rcx.data.number);
				break;
			case TYRAN_OPCODE_NOT:
				TYRAN_REGISTER_A_RCX;
				tyran_value_replace_boolean(r[a], !rcx.data.boolean);
				break;
			case TYRAN_OPCODE_EQ:
			case TYRAN_OPCODE_LT:
			case TYRAN_OPCODE_LE: {
				int comparison_index = (opcode - TYRAN_OPCODE_EQ) + 8;

				TYRAN_REGISTER_A_B_RCX_RCY;
				if (tyran_value_is_object(&rcx)) {
					TYRAN_RUNTIME_INVOKE_BINARY_OPERATOR(&r[a], rcx, &rcy, 1, comparison_index);
				} else {
					test = tyran_number_operator_comparison(comparison_index, rcx.data.number, rcy.data.number);
					tyran_value_replace_boolean(r[a], test);
				}
				TYRAN_LOG("b:%d", b);
				test = r[a].data.boolean;
				if (b) {
					test = !test;
					r[a].data.boolean = test;
				}
			}
			break;
			case TYRAN_OPCODE_JB: {
				TYRAN_REGISTER_A_RCX;
				test = tyran_value_is_false(&rcx);
				if (a) {
					test = !test;
				}
				if (test) {
					TYRAN_RUNTIME_DO_JMP;
				} else {
					pc++;
				}
			}
			break;
			case TYRAN_OPCODE_JBLD: {
				TYRAN_REGISTER_A_RCX_Y;
				test = tyran_value_is_false(&rcx);
				if (y) {
					test = !test;
				}
				if (test) {
					tyran_value_replace(r[a], rcx);
					TYRAN_RUNTIME_DO_JMP;
				} else {
					pc++;
				}
			}
			break;
			case TYRAN_OPCODE_JMP:
				TYRAN_REGISTER_BR;
				pc += br;
				break;
			case TYRAN_OPCODE_RET: {
				TYRAN_REGISTER_A_X;
				tyran_value* from = &r[a];
				if (sp == base_sp) {
					tyran_value_copy(*return_value, *from);
					return;
				}
				tyran_register_copy(sp->return_register, from, x);
				tyran_value_clear((&r[1]), 100);
				TYRAN_STACK_POP;
			}
			break;
			case TYRAN_OPCODE_NEW:
			case TYRAN_OPCODE_CALL:
				TYRAN_REGISTER_A_X;
				{
					if (opcode == TYRAN_OPCODE_NEW) {
						object = TYRAN_CALLOC_TYPE(runtime->object_pool, tyran_object);
						object->created_in_runtime = runtime;
						tyran_object_set_prototype(object, r[a+1].data.object);
						tyran_value_replace_object(r[a+1], object);
					}
					TYRAN_ASSERT(tyran_value_is_function(&r[a]), "Must reference a function!");
					const tyran_function* function = r[a].data.object->data.function->static_function;
					if (function->type == tyran_function_type_normal) {
						TYRAN_STACK_PUSH;
						sp->opcodes = function->data.opcodes;
						pc = sp->opcodes->codes;
						sp->constants = function->constants;
						c = sp->constants->values;
						tyran_value* target_register = &r[a];
						r = target_register + 1;
						sp->return_register = target_register;
					} else {
						function->data.callback(runtime, &r[a], &r[a+2], x, &r[a+1], &r[a], TYRAN_FALSE);
					}
					if (opcode == TYRAN_OPCODE_NEW) {
						tyran_value_copy(r[a], r[a+1]);
					}
					if (function->type != tyran_function_type_normal) {
						tyran_value_clear((&r[a+1]), x + 1);
					}
				}
				break;
			case TYRAN_OPCODE_GET: {
				TYRAN_REGISTER_A_RCX_RCY;
				tyran_value v;
				tyran_value_object_lookup_prototype(&v, &rcx, &rcy);
				tyran_value_replace(r[a], v);
			}
			break;
			case TYRAN_OPCODE_SET:
				TYRAN_REGISTER_A_RCX_RCY;
				tyran_value_object_insert(runtime, &r[a], &rcx, &rcy);
				break;
			case TYRAN_OPCODE_FUNC: {
				TYRAN_REGISTER_A_RCX;
				TYRAN_ASSERT(c[x].type == TYRAN_VALUE_TYPE_STATIC_FUNCTION, "Must be a function");
				tyran_function* static_function = c[x].data.static_function;
				tyran_function_object* function_object = tyran_function_object_new(runtime->function_object_pool, static_function);
				tyran_object* object = tyran_object_new(runtime);
				tyran_object_set_function(object, function_object);
				tyran_value_replace_object(r[a], object);
			}
			break;
			case TYRAN_OPCODE_DEBUG:
				return;
				break;
			default:
				TYRAN_ERROR("Illegal instruction:%d",instruction);
				break;
		}
	}
}
