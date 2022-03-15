#ifndef SRC_STACK_H_
#define SRC_STACK_H_
#include <stdlib.h>

typedef struct stack_pn {
    char symbol;
    struct stack_pn* next;
} st_pn;

typedef struct stack_calc {
    double digit;
    struct stack_calc* next;
} st_calc;

st_pn* push_pn(st_pn* head, char a);
char pop_pn(st_pn** head);

st_calc* push_calc(st_calc* head, double a);
double pop_calc(st_calc** head);

#endif  // SRC_STACK_H_
