#include <tyranscript/parser/mocha/tyran_parser.h>
#include <tyranscript/parser/tyran_lexer.h>
#include "tyran_script_parser.tab.h"
#include <tyranscript/tyran_string.h>

tyran_parser* tyran_parser_alloc(const char* buf)
{
	tyran_parser* parser = TYRAN_MALLOC_TYPE(tyran_parser, 1);
	parser->position = 0;
	parser->lexer = tyran_lexer_new(buf);

	return parser;
}


static int tyran_parser_next_token(tyran_lexer_token_data* token, tyran_lexer_position_info* lexer_position_info, tyran_lexer* lexer)
{
	tyran_lexer_set_begin(lexer_position_info, lexer);

	char c = tyran_lexer_next_character_skip_whitespace(lexer);
	if (!c) {
		return 0;
	}

	if (tyran_lexer_is_alpha(c) || c == '_' || c == '$') {
		tyran_lexer_parse_identifier(lexer, c, lexer_position_info, token);
		return IDENTIFIER;
	} else if (tyran_lexer_is_digit(c)) {
		tyran_lexer_parse_number(lexer, c, lexer_position_info, token);
		return NUMBER;
	} else if (c == '"' || c == '\'') {
		return tyran_lexer_parse_whole_string(lexer, c, lexer_position_info, token);
	} else if (c == '/') {
		int r = tyran_lexer_parse_comment(lexer);
		if (r) {
			return r;
		}
	} else {
		return c;
	}

	tyran_lexer_push_character(c, lexer);

	tyran_lexer_set_end(lexer_position_info, lexer);

	return 0;
}


int TYRAN_PARSER_lex(YYSTYPE *lvalp, YYLTYPE *llocp, tyran_parser* parser)
{
	tyran_lexer_token_data token;
	tyran_lexer_position_info info;
	
	int ch = tyran_parser_next_token(&token, &info, parser->lexer);
	// TYRAN_LOG("Lex:%d", ch);
	return ch;
}

void TYRAN_PARSER_error(YYLTYPE* lexer_position_info, tyran_parser* ps, const char* message)
{
	TYRAN_LOG("Error:%s", message);
}

int tyran_parser_parse(tyran_parser* parser)
{
	TYRAN_PARSER_parse(parser);
	return 0;
}

NODE tyran_parser_block(NODE b)
{
	TYRAN_LOG("block");
	return 0;
}
NODE tyran_parser_compound_assignment(NODE a, NODE b, NODE c)
{
	TYRAN_LOG("compound assignment");
	return 0;
}
NODE tyran_parser_assignment(NODE a, NODE b)
{
	TYRAN_LOG("assignment");
	return 0;
}
NODE tyran_parser_object_assignment(NODE a, NODE b)
{
	TYRAN_LOG("object assignment");
	return 0;
}

NODE tyran_parser_value(NODE a)
{
	TYRAN_LOG("value");
	return 0;
}
NODE tyran_parser_return(NODE expression)
{
	TYRAN_LOG("return");
	return 0;
}
NODE tyran_parser_comment(NODE comment)
{
	return 0;
}
NODE tyran_parser_code(NODE a, NODE b, NODE c)
{
	TYRAN_LOG("code");
	return 0;
}
NODE tyran_parser_concat(NODE a, NODE b)
{
	return 0;
}
NODE tyran_parser_parameter(NODE a, NODE b, NODE c)
{
	TYRAN_LOG("parameter");
	return 0;
}
NODE tyran_parser_splat(NODE a)
{
	return 0;
}
NODE tyran_parser_accessor(NODE a)
{
	TYRAN_LOG("accessor");
	return 0;
}
NODE tyran_parser_index_soak(NODE a)
{
	TYRAN_LOG("index soak");
	return 0;
}
NODE tyran_parser_index(NODE a)
{
	TYRAN_LOG("index");
	return 0;
}
NODE tyran_parser_slice(NODE b)
{
	TYRAN_LOG("slice");
	return 0;
}
NODE tyran_parser_object(NODE a)
{
	TYRAN_LOG("object");
	return 0;
}
NODE tyran_parser_class(NODE name, NODE extends, NODE block)
{
	TYRAN_LOG("class");
	return 0;
}
NODE tyran_parser_call(NODE a, NODE b, NODE c)
{
	TYRAN_LOG("call");
	return 0;
}
NODE tyran_parser_arguments(NODE a)
{
	TYRAN_LOG("arguments");
	return 0;
}
NODE tyran_parser_self()
{
	TYRAN_LOG("self");
	return 0;
}
NODE tyran_parser_self_identifier(NODE a)
{
	TYRAN_LOG("self identifier");
	return 0;
}
NODE tyran_parser_array(NODE a)
{
	TYRAN_LOG("array");
	return 0;
}
NODE tyran_parser_range(NODE a, NODE b, NODE c)
{
	TYRAN_LOG("range");
	return 0;
}
NODE tyran_parser_parens(NODE a)
{
	TYRAN_LOG("parens");
	return 0;
}
NODE tyran_parser_while(NODE a)
{
	TYRAN_LOG("while");
	return 0;
}
NODE tyran_parser_while_condition(NODE a, NODE b)
{
	TYRAN_LOG("while condition");
	return 0;
}
NODE tyran_parser_for(NODE a, NODE b)
{
	TYRAN_LOG("for");
	return 0;
}
NODE tyran_parser_for_body(NODE a)
{
	TYRAN_LOG("for body");
	return 0;
}
NODE tyran_parser_for_start(NODE a, NODE b)
{
	TYRAN_LOG("for start");
	return 0;
}
NODE tyran_parser_for_variables(NODE a)
{
	TYRAN_LOG("for var");
	return 0;
}
NODE tyran_parser_switch(NODE a, NODE b, NODE block)
{
	TYRAN_LOG("switch");
	return 0;
}
NODE tyran_parser_when(NODE a, NODE b)
{
	TYRAN_LOG("when");
	return 0;
}
NODE tyran_parser_if(NODE a, NODE b)
{
	TYRAN_LOG("if");
	return 0;
}
NODE tyran_parser_if_else(NODE a, NODE b)
{
	TYRAN_LOG("if else");
	return 0;
}
NODE tyran_parser_operand(NODE a, NODE b)
{
	TYRAN_LOG("operand");
	return 0;
}
NODE tyran_parser_operand_binary(NODE a, NODE b, NODE c)
{
	TYRAN_LOG("operand binary");
	return 0;
}
NODE tyran_parser_extends(NODE a, NODE b)
{
	TYRAN_LOG("extends");
	return 0;
}

NODE tyran_parser_null()
{
	TYRAN_LOG("null");
	return 0;
}
NODE tyran_parser_bool(int boolean)
{
	TYRAN_LOG("bool");
	return 0;
}
NODE tyran_parser_undefined()
{
	TYRAN_LOG("undefined");
	return 0;
}
NODE tyran_parser_literal_number(NODE number)
{
	TYRAN_LOG("literal number");
	return 0;
}
NODE tyran_parser_literal_string(struct tyran_string* string)
{
	TYRAN_LOG("literal string");
	return 0;
}
NODE tyran_parser_literal_identifier(struct tyran_string* string)
{
	TYRAN_LOG("literal identifier");
	return 0;
}
NODE tyran_parser_call_super(NODE a)
{
	TYRAN_LOG("super");
	return 0;
}
