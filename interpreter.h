
#ifndef INTERPRETER_H
#define INTERPRETER_H

void interpreter_declare_variable(const char* name, double value, int is_const);
int interpreter_assign_variable(const char* name, double value);
int interpreter_get_variable(const char* name, double* out_value);
void interpreter_print(double val);

#endif
