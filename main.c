
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

int main() {
    printf("Mini JS Compiler - Supports let, var, const, arithmetic, print\n");
    printf("Enter your code. End input with EOF (Ctrl+D on Linux/Mac, Ctrl+Z on Windows).\n\n");

    char buffer[1024];
    char* program = NULL;
    size_t program_size = 0;

    while (fgets(buffer, sizeof(buffer), stdin)) {
        size_t len = strlen(buffer);
        char* temp = realloc(program, program_size + len + 1);
        if (!temp) {
            free(program);
            fprintf(stderr, "Out of memory\n");
            return 1;
        }
        program = temp;
        memcpy(program + program_size, buffer, len);
        program_size += len;
        program[program_size] = '\0';
    }

    lexer_init(program);
    lexer_next_token();
    parser_init();
    parser_parse();

    free(program);
    return 0;
}
