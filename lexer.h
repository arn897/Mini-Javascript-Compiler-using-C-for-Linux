
#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_EOF,
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_ASSIGN,
    TOKEN_SEMI,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_PRINT,
    TOKEN_LET,
    TOKEN_VAR,
    TOKEN_CONST,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char text[64];
    double value;
} Token;

void lexer_init(const char* input);
void lexer_next_token();
Token lexer_get_current_token();

#endif
