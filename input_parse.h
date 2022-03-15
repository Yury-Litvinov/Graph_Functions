#ifndef SRC_INPUT_PARSE_H_
#define SRC_INPUT_PARSE_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conditions.h"

typedef struct expr {
    int len;
    char* in_str;
    char* f_in;
    char* pn;
} EXPR;

#define SIZE_STR_PART 100
#define ROWS 6
#define COLS 6

struct expr *read_expr(void);
struct expr *create_new_expr(int size_str);
char read_symbol(struct expr *s, int *size_str);
void func_names_to_abbrev(struct expr *expr);
void end_read_expr(struct expr *s);
void write_expr_to_f_in(struct expr *expr);
void find_replace(struct expr *expr, char names[][COLS], const char *abbrev, const int *len);
#endif  // SRC_INPUT_PARSE_H_
