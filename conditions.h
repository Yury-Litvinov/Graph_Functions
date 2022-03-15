#ifndef SRC_CONDITIONS_H_
#define SRC_CONDITIONS_H_

int math_symbol_prior(char a);
int is_math_func(char c);
int is_math_symbol(char c);
int is_digit(char c);
void add_digit(char symbol, char next_symbol, char* out, int* count_out);
int is_correct_expression(char* expr);

#endif  // SRC_CONDITIONS_H_
