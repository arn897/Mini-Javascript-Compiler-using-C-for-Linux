
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interpreter.h"

#define MAX_VAR 100

typedef struct {
    char name[64];
    double value;
    int is_const;
} Variable;

static Variable vars[MAX_VAR];
static int var_count = 0;

void interpreter_declare_variable(const char* name, double value, int is_const) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            fprintf(stderr, "Error: variable '%s' already declared\n", name);
            exit(1);
        }
    }
    if (var_count >= MAX_VAR) {
        fprintf(stderr, "Error: too many variables\n");
        exit(1);
    }
    strcpy(vars[var_count].name, name);
    vars[var_count].value = value;
    vars[var_count].is_const = is_const;
    var_count++;
}

int interpreter_assign_variable(const char* name, double value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            if (vars[i].is_const) {
                fprintf(stderr, "Error: cannot assign to constant variable '%s'\n", name);
                exit(1);
            }
            vars[i].value = value;
            return 1;
        }
    }
    return 0;
}

int interpreter_get_variable(const char* name, double* out_value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            *out_value = vars[i].value;
            return 1;
        }
    }
    return 0;
}

void interpreter_print(double val) {
    printf("%g\n", val);
}
