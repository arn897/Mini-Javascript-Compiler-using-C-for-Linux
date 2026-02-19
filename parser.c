
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "interpreter.h"
#include "parser.h"

static Token current_token;

static void error(const char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

static void expect(TokenType type) {
    if (current_token.type != type) {
        error("Unexpected token");
    }
    lexer_next_token();
    current_token = lexer_get_current_token();
}

static double parse_expression();
static double parse_term();
static double parse_factor();

static double parse_expression() {
    double left = parse_term();
    while (current_token.type == TOKEN_PLUS || current_token.type == TOKEN_MINUS) {
        TokenType op = current_token.type;
        lexer_next_token();
        current_token = lexer_get_current_token();
        double right = parse_term();
        if (op == TOKEN_PLUS) left += right;
        else left -= right;
    }
    return left;
}

static double parse_term() {
    double left = parse_factor();
    while (current_token.type == TOKEN_MUL || current_token.type == TOKEN_DIV) {
        TokenType op = current_token.type;
        lexer_next_token();
        current_token = lexer_get_current_token();
        double right = parse_factor();
        if (op == TOKEN_MUL) left *= right;
        else {
            if (right == 0) error("Division by zero");
            left /= right;
        }
    }
    return left;
}

static double parse_factor() {
    if (current_token.type == TOKEN_NUMBER) {
        double val = current_token.value;
        lexer_next_token();
        current_token = lexer_get_current_token();
        return val;
    } else if (current_token.type == TOKEN_IDENTIFIER) {
        char varname[64];
        strcpy(varname, current_token.text);
        lexer_next_token();
        current_token = lexer_get_current_token();
        double val;
        if (!interpreter_get_variable(varname, &val)) {
            char err[128];
            snprintf(err, sizeof(err), "Undefined variable '%s'", varname);
            error(err);
        }
        return val;
    } else if (current_token.type == TOKEN_LPAREN) {
        lexer_next_token();
        current_token = lexer_get_current_token();
        double val = parse_expression();
        expect(TOKEN_RPAREN);
        return val;
    } else {
        error("Expected number, variable or '('");
        return 0;
    }
}

static void parse_statement() {
    if (current_token.type == TOKEN_LET ||
        current_token.type == TOKEN_VAR ||
        current_token.type == TOKEN_CONST) {

        int is_const = (current_token.type == TOKEN_CONST);
        lexer_next_token();
        current_token = lexer_get_current_token();

        if (current_token.type != TOKEN_IDENTIFIER)
            error("Expected variable name after declaration keyword");

        char varname[64];
        strcpy(varname, current_token.text);

        lexer_next_token();
        current_token = lexer_get_current_token();

        expect(TOKEN_ASSIGN);

        double val = parse_expression();

        interpreter_declare_variable(varname, val, is_const);

        expect(TOKEN_SEMI);

    } else if (current_token.type == TOKEN_IDENTIFIER) {
        char varname[64];
        strcpy(varname, current_token.text);
        lexer_next_token();
        current_token = lexer_get_current_token();
        expect(TOKEN_ASSIGN);
        double val = parse_expression();

        if (!interpreter_assign_variable(varname, val)) {
            char err[128];
            snprintf(err, sizeof(err), "Undefined variable '%s'", varname);
            error(err);
        }

        expect(TOKEN_SEMI);

    } else if (current_token.type == TOKEN_PRINT) {
        lexer_next_token();
        current_token = lexer_get_current_token();
        expect(TOKEN_LPAREN);
        double val = parse_expression();
        expect(TOKEN_RPAREN);
        expect(TOKEN_SEMI);
        interpreter_print(val);
    } else if (current_token.type == TOKEN_EOF) {
        return;
    } else {
        double val = parse_expression();
        expect(TOKEN_SEMI);
    }
}

void parser_init() {
    current_token = lexer_get_current_token();
}

void parser_parse() {
    while (current_token.type != TOKEN_EOF) {
        parse_statement();
    }
}
