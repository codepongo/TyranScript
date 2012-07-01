#include <tyranscript/tyran_opcode_ids.h>
#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_opcode.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/debug/tyran_print_opcodes.h>


const char* tyran_opcode_names[TYRAN_OPCODE_MAX_ID] = {
	"NOP",
	"LD",
	"LDC",
	"LDB",
	"LDN",
	"ADD",
	"DIV",
	"MOD",
	"MUL",
	"NEG",
	"NOT",
	"POW",
	"SUB",
	"JB",
	"JBLD",
	"JEQ",
	"JLT",
	"JLE",
	"JMP",
	"RET",
	"CALL",
	"NEW",
	"SET",
	"GET",
	"DEBUG"
};

void tyran_print_opcode(const tyran_opcode* opcode, int ip, int highlight)
{
	tyran_opcode code = *opcode;
	int instruction = code & 0x3f;
	
	TYRAN_LOG("%d %s", ip, tyran_opcode_names[instruction]);
}

void tyran_print_opcodes(const struct tyran_opcodes* ops, const tyran_opcode* ip)
{
	int i = 0;
	const tyran_opcode* tyran_opcodes = ops->codes;
	int octet_length = ops->code_len;

	TYRAN_LOG("opcode octets:%d", octet_length);

	for (i = 0; i < octet_length; ++i) {
		tyran_print_opcode(&tyran_opcodes[i], i, ip == &tyran_opcodes[i]);
	}
}
