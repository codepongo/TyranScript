//
//  tyran_mocha_lexer_debug.h
//  tyranscript
//
//  Created by Peter Björklund on 2012-07-29.
//
//

#ifndef tyranscript_tyran_mocha_lexer_debug_h
#define tyranscript_tyran_mocha_lexer_debug_h

struct tyran_mocha_lexer;
struct tyran_mocha_token;

void tyran_mocha_lexer_debug(struct tyran_mocha_lexer* lexer);
void tyran_mocha_lexer_debug_tokens(const char* description, struct tyran_mocha_token* first, struct tyran_mocha_token* last);
void tyran_mocha_lexer_debug_token(struct tyran_mocha_token* last);

#endif
