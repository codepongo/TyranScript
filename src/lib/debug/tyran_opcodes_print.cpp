#include <tyranscript/tyran_opcode_ids.h>
#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_opcode.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/debug/tyran_opcodes_print.h>

const char* tyran_opcode_names[100] = {
	"NOP",
	"PUSH_NUMBER",
	"PUSH_STRING",
	"PUSH_VARIABLE",
	"PUSH_UNDEFINED",
	"PUSH_BOOLEAN",
	"PUSH_FUNCTION",
	"PUSH_SCOPE",
	"PUSH_THIS",
	"PUSH_TOP",
	"PUSH_TOP2",
	"POP",

	"NEGATE",
	"NOT",
	"ADD",
	"SUBTRACT",
	"MULTIPLY",
	"DIVIDE",
	"MODULUS",
	"INCREASE",
	"DECREASE",

	"BITWISE_AND",
	"BITWISE_OR",
	"BITWISE_XOR",
	"BITWISE_NOT",
	"BITWISE_SHIFT",

	"COMPARE_EQUAL",
	"COMPARE_NOT_EQUAL",
	"COMPARE_LESS",
	"COMPARE_GREATER",
	"COMPARE_LESS_EQUAL",
	"COMPARE_GREATER_EQUAL",

	"JUMP",
	"JUMP_POP",
	"JUMP_TRUE",
	"JUMP_FALSE",
	"JUMP_TRUE_POP",
	"JUMP_FALSE_POP",
	"CALL",
	"NEW",
	"RETURN",

	"MAKE_OBJECT",
	"MAKE_ARRAY",
	"DELETE",
	"ASSIGN",
	"SUBSCRIPT",
	"UNREFERENCE",

	"KEY",
	"NEXT",

	"LOAD_THIS"
};

void tyran_opcodes_print_opcode(const struct tyran_opcode* opcode, int ip)
{
	const int max_size = 2048;
	char value[max_size];
	value[0] = 0;
	
	switch (opcode->opcode)
	{
	case TYRAN_OPCODE_PUSH_BOOLEAN:
	case TYRAN_OPCODE_CALL:
	case TYRAN_OPCODE_POP:
	case TYRAN_OPCODE_ASSIGN:
	case TYRAN_OPCODE_RETURN:
	case TYRAN_OPCODE_NEW:
	case TYRAN_OPCODE_DELETE:
	case TYRAN_OPCODE_MAKE_OBJECT:
	case TYRAN_OPCODE_MAKE_ARRAY:
	case TYRAN_OPCODE_BITWISE_SHIFT:
	case TYRAN_OPCODE_INCREASE:
	case TYRAN_OPCODE_DECREASE:
		tyran_snprintf(value, max_size, "%d", opcode->data.integer);
		break;

	case TYRAN_OPCODE_PUSH_NUMBER:
		tyran_snprintf(value, max_size, "%g", *((double *)opcode->data.pointer));
		break;

	case TYRAN_OPCODE_PUSH_STRING:
		tyran_snprintf(value, max_size, "\"%s\"", tyran_string_to_c_str((const tyran_string*) opcode->data.pointer));
		break;

	case TYRAN_OPCODE_PUSH_VARIABLE:
		tyran_snprintf(value, max_size, "\"%s\"", tyran_string_to_c_str(((const tyran_variable_name_info *)opcode->data.pointer)->data.variable_name));
		break;
		
	case TYRAN_OPCODE_JUMP_TRUE:
	case TYRAN_OPCODE_JUMP_FALSE:
	case TYRAN_OPCODE_JUMP_TRUE_POP:
	case TYRAN_OPCODE_JUMP_FALSE_POP:
	case TYRAN_OPCODE_JUMP:
		tyran_snprintf(value, max_size, "%d (offset:%d)", ip + opcode->data.integer, opcode->data.integer);
		break;

	case TYRAN_OPCODE_JUMP_POP: {
			tyran_jump_pop_info *jp = (tyran_jump_pop_info*) opcode->data.pointer;
			tyran_snprintf(value, max_size, "%d (offset:%d) pop:%d", ip + jp->offset, jp->offset, jp->pop_count);
		}
		break;

	default:
		break;
	}
	
	TYRAN_LOG("%d: %s %s", ip, (tyran_opcode_names[opcode->opcode]), value);
	
	if (opcode->opcode == TYRAN_OPCODE_PUSH_FUNCTION) {
		const tyran_function* function = (const tyran_function*) opcode->data.pointer;
		tyran_opcodes_print(function->data.opcodes);
	}
}

void tyran_opcodes_print(const struct tyran_opcodes* ops)
{
	int i = 0;
	tyran_opcode* tyran_opcodes = ops->codes;
	int octet_length = ops->code_len;

	TYRAN_LOG("opcode octets:%d", octet_length);

	for (i = 0; i < octet_length; ++i) {
		tyran_opcodes_print_opcode(&tyran_opcodes[i], i);
	}
}
