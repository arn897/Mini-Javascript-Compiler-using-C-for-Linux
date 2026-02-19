
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

static const char* src;
static int pos;
static Token current_token;

static int is_keyword(const char* str) {
    return (strcmp(str, "print") == 0 ||
            strcmp(str, "let") == 0 ||
            strcmp(str, "var") == 0 ||
            strcmp(str, "const") == 0);
}

void lexer_init(const char* input) {
    src = input;
    pos = 0;
}

void lexer_next_token() {
    while (isspace(src[pos])) pos++;

    if (src[pos] == '\0') {
        current_token.type = TOKEN_EOF;
        return;
    }

    char c = src[pos];

    if (isdigit(c) || c == '.') {
        int start = pos;
        while (isdigit(src[pos]) || src[pos] == '.') pos++;
        int len = pos - start;
        if (len >= sizeof(current_token.text)) len = sizeof(current_token.text) - 1;
        strncpy(current_token.text, src + start, len);
        current_token.text[len] = '\0';
        current_token.type = TOKEN_NUMBER;
        current_token.value = atof(current_token.text);
        return;
    }

    if (isalpha(c) || c == '_') {
        int start = pos;
        while (isalnum(src[pos]) || src[pos] == '_') pos++;
        int len = pos - start;
        if (len >= sizeof(current_token.text)) len = sizeof(current_token.text) - 1;
        strncpy(current_token.text, src + start, len);
        current_token.text[len] = '\0';

        if (is_keyword(current_token.text)) {
            if (strcmp(current_token.text, "print") == 0)
                current_token.type = TOKEN_PRINT;
            else if (strcmp(current_token.text, "let") == 0)
                current_token.type = TOKEN_LET;
            else if (strcmp(current_token.text, "var") == 0)
                current_token.type = TOKEN_VAR;
            else if (strcmp(current_token.text, "const") == 0)
                current_token.type = TOKEN_CONST;
        } else {
            current_token.type = TOKEN_IDENTIFIER;
        }
        return;
    }

    pos++;
    switch (c) {
        case '+': current_token.type = TOKEN_PLUS; break;
        case '-': current_token.type = TOKEN_MINUS; break;
        case '*': current_token.type = TOKEN_MUL; break;
        case '/': current_token.type = TOKEN_DIV; break;
        case '=': current_token.type = TOKEN_ASSIGN; break;
        case ';': current_token.type = TOKEN_SEMI; break;
        case '(': current_token.type = TOKEN_LPAREN; break;
        case ')': current_token.type = TOKEN_RPAREN; break;
        default: current_token.type = TOKEN_UNKNOWN; break;
    }
}

Token lexer_get_current_token() {
    return current_token;
}
