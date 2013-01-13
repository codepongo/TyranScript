#include "tyran_runtime_macros.h"

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

#define TYRAN_RUNTIME_DEBUG

#define TYRAN_RUNTIME_INVOKE_BINARY_OPERATOR(DESTINATION, OBJECT, PARAMS, PARAM_COUNT, OPERATOR) \
	tyran_value* member = tyran_object_lookup_prototype((OBJECT).data.object, &runtime->binary_operator_symbols[OPERATOR]); \
	TYRAN_ASSERT(member, "Couldn't find operator:%d %d", OPERATOR, runtime->binary_operator_symbols[OPERATOR].hash); \
	const tyran_function* function = member->data.object->data.function->static_function; \
	function->data.callback(runtime, member, PARAMS, PARAM_COUNT, &OBJECT, DESTINATION, TYRAN_FALSE);

#define TYRAN_RUNTIME_INVOKE_UNARY_OPERATOR(DESTINATION, OBJECT, OPERATOR) \
	tyran_value* member = tyran_object_lookup_prototype((OBJECT).data.object, &runtime->binary_operator_symbols[OPERATOR]); \
	TYRAN_ASSERT(member, "Couldn't find operator:%d %d", OPERATOR, runtime->binary_operator_symbols[OPERATOR].hash); \
	const tyran_function* function = member->data.object->data.function->static_function; \
	function->data.callback(runtime, member, 0, 0, &OBJECT, DESTINATION, TYRAN_FALSE);

void tyran_register_copy(tyran_value* target, tyran_value* source, int count)
{
	for (int i=0; i<count; ++i) {
		tyran_value_copy(target[i], source[i]);
	}
}

#define TYRAN_RUNTIME_DO_JMP \
	instruction = *pc++; \
	instruction >>= 6; \
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
	tyran_value rcx;
	tyran_value rcy;
	u32t i;
	int test;
	tyran_object* object;
	tyran_value* r;
	tyran_runtime_stack* sp = &runtime->stack[runtime->stack_pointer];
	const tyran_opcode* pc;
	const tyran_value* c;

	TYRAN_STACK_POP
	tyran_runtime_stack* base_sp = sp;

	tyran_value_set_undefined(*return_value);
	tyran_value_copy(r[0], sp->_this);

	while (1) {
#ifdef TYRAN_RUNTIME_DEBUG
		tyran_print_runtime_state(pc, sp, r);
#endif
		u32t instruction = *pc++;
		u32t opcode = instruction & 0x3f;
		instruction >>= 6;

		switch (opcode) {
			case TYRAN_OPCODE_LD:
				TYRAN_REGISTER_A_X;
				TYRAN_SET_REGISTER(a, x);
				TYRAN_ADD_REF(r[a]);
				break;
			case TYRAN_OPCODE_LDC:
				TYRAN_REGISTER_A_X;
				tyran_value_replace(r[a], c[x]);
				break;
			case TYRAN_OPCODE_LDCU:
				TYRAN_REGISTER_A_X;
				if (tyran_value_is_undefined(&r[a])) {
					tyran_value_replace(r[a], c[x]);
				}
				break;
			case TYRAN_OPCODE_ADD:
			case TYRAN_OPCODE_DIV:
			case TYRAN_OPCODE_MOD:
			case TYRAN_OPCODE_MUL:
			case TYRAN_OPCODE_POW:
			case TYRAN_OPCODE_SUB:
			case TYRAN_OPCODE_INDEX:
			case TYRAN_OPCODE_INDEX_SET:
				TYRAN_REGISTER_A_RCX_RCY;
				{
					int operator_index = opcode - TYRAN_OPCODE_ADD;
					if (tyran_value_is_number(&rcx)) {
						tyran_number_operator_binary(&r[a], operator_index, rcx.data.number, rcy.data.number);
					} else {
						if (opcode == TYRAN_OPCODE_INDEX_SET) {
							tyran_value_replace(r[a+1], rcx);
							tyran_value_replace(r[a+2], rcy);
							TYRAN_RUNTIME_INVOKE_BINARY_OPERATOR(&r[a], r[a], &r[a+1], 2, operator_index);
						} else {
							TYRAN_RUNTIME_INVOKE_BINARY_OPERATOR(&r[a], rcx, &rcy, 1, operator_index);
						}
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
				if (!tyran_value_is_undefined(&r[a])) {
					pc++;
				}
			}
			break;
			case TYRAN_OPCODE_NEG:
				TYRAN_REGISTER_A_RCX;
				tyran_value_set_number(r[a], -rcx.data.number);
				break;
			case TYRAN_OPCODE_NOT:
				TYRAN_REGISTER_A_RCX;
				tyran_value_set_boolean(r[a], !rcx.data.boolean);
				break;
			case TYRAN_OPCODE_JEQ:
			case TYRAN_OPCODE_JLT:
			case TYRAN_OPCODE_JLE: {
				int comparison_index = (opcode - TYRAN_OPCODE_JEQ) + 8;

				TYRAN_REGISTER_A_RCX_RCY;
				if (tyran_value_is_object(&rcx)) {
					tyran_value dest;

					TYRAN_RUNTIME_INVOKE_BINARY_OPERATOR(&dest, rcx, &rcy, 1, comparison_index);
					test = dest.data.boolean;
				} else {
					test = tyran_number_operator_comparison(comparison_index, rcx.data.number, rcy.data.number);
				}
				if (test != a) {
					pc++;
				} else {
					TYRAN_RUNTIME_DO_JMP;
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
				TYRAN_STACK_POP;
			}
			break;
			case TYRAN_OPCODE_NEW:
			case TYRAN_OPCODE_CALL:
				TYRAN_REGISTER_A_X;
				{
					if (opcode == TYRAN_OPCODE_NEW) {
						object = TYRAN_CALLOC_TYPE(runtime->object_pool, tyran_object);
						tyran_object_set_prototype(object, r[a+1].data.object);
						tyran_value_set_object(r[a+1], object);
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
				}
				break;
			case TYRAN_OPCODE_GET: {
				TYRAN_REGISTER_A_RCX_RCY;
				const tyran_value* v = tyran_value_object_lookup_prototype(&rcx, &rcy);
				if (!v) {
					tyran_value_set_undefined(r[a]);
				} else {
					tyran_value_copy(r[a], *v);
					TYRAN_ADD_REF(r[a]);
				}
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
				tyran_value_set_object(r[a], object);
			}
			break;
			case TYRAN_OPCODE_DEBUG:
				return;
				break;
		}
	}
}
