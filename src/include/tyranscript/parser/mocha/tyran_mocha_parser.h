#ifndef tyranscript_tyran_mocha_parser_h
#define tyranscript_tyran_mocha_parser_h

#include <tyranscript/parser/mocha/tyran_parser_tree.h>

struct tyran_mocha_lexer;

NODE tyran_mocha_parser_parse(struct tyran_mocha_lexer* lexer);

#endif
