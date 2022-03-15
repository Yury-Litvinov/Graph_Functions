#include "pn.h"

void convert_to_pn(char* expr_in, char* expr_pn) {
    st_pn* st = NULL;
    int i = 0, ind_pn = 0;
    while (expr_in[i] != '\0') {
        if (expr_in[i] == ')') {
            // выталкиваем из стека в выходную стpоку все знаки опеpаций до ближайшей '('
            while ((st->symbol) != '(') {
                expr_pn[ind_pn++] = pop_pn(&st);
                expr_pn[ind_pn++] = ' ';
            }
            pop_pn(&st);  // после чего удаляем из стека саму откpывающую скобку
        } else if (expr_in[i] == '(') {
            st = push_pn(st, '(');  // заталкиваем её в стек
        } else if (is_digit(expr_in[i]) || expr_in[i] == 'x') {  // унарные и цифры сразу на выход, без стека
            add_digit(expr_in[i], expr_in[i + 1], expr_pn, &ind_pn);  // собираем многосимвольное число
        } else if (is_math_symbol(expr_in[i]) || is_math_func(expr_in[i])) {
            while (st && math_symbol_prior(st->symbol) >= math_symbol_prior(expr_in[i])) {
                expr_pn[ind_pn++] = pop_pn(&st);
                expr_pn[ind_pn++] = ' ';
            }
            st = push_pn(st, expr_in[i]);
        }
        i++;
    }
    // после pассмотpения всего выpажения
    while (st != NULL)
        expr_pn[ind_pn++] = pop_pn(&st);  // все опеpации из стека в выходную стpоку
    expr_pn[ind_pn] = '\0';  // и дописываем символ конца строки
}

st_calc* operation(char c, st_calc* pn) {
    double a, b;
    a = pop_calc(&pn);
    b = pop_calc(&pn);
    switch (c) {
        case '*': pn = push_calc(pn, a * b); break;
        case '+': pn = push_calc(pn, a + b); break;
        case '-': pn = push_calc(pn, b - a); break;
        case '/':
            if (a != 0) {
                pn = push_calc(pn, b / a);
                break;
            } else {
                pn = push_calc(pn, 1);
                break;
            }
        case '^': pn = push_calc(pn, pow(b, a)); break;
    }
    return pn;
}

st_calc* function(char c, st_calc* pn) {
    double a = pop_calc(&pn);
    switch (c) {
        case '#': pn = push_calc(pn, a * (-1)); break;
        case 'a': pn = push_calc(pn, sin(a)); break;
        case 'b': pn = push_calc(pn, cos(a)); break;
        case 'z':  // ctg
            if (sin(a) != 0) {
                pn = push_calc(pn, cos(a) / sin(a));
                break;
            } else {
                pn = push_calc(pn, 1);
                break;
            }
        case 'd':  // tg, tan
            pn = push_calc(pn, tan(a)); break;
        case 'e': pn = push_calc(pn, sqrt(a)); break;
        case 'f': pn = push_calc(pn, log(a)); break;
    }
    return pn;
}
