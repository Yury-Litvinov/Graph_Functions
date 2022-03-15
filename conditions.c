#include "conditions.h"

int math_symbol_prior(char a) {
    int res = 10;
    switch (a) {
        case '(':
        case ')': res = 1; break;
        case '+':
        case '-': res = 3; break;
        case '*':
        case '/': res = 4; break;
        case '^':
        case '#': res = 6; break;
        // default: return 10;
    }
    if (is_math_func(a)) res = 6;
    return res;
}

int is_math_func(char c) {
    //                    sin         cos         ctg          tg         sqrt         ln
    return (c == '#' || c == 'a' || c == 'b' || c == 'z' || c == 'd' || c == 'e' || c == 'f');
}

int is_math_symbol(char c) {
    return (c == '*' || c == '-' || c == '+' || c == '/' || c == '^');
}

int is_digit(char c) {
    return ((c >= '0' && c <= '9') || c == '.');
}

void add_digit(char symbol, char next_symbol, char* out, int* count_out) {
    out[(*count_out)++] = symbol;
    if (!is_digit(next_symbol)) out[(*count_out)++] = ' ';
}

int is_correct_expression(char* expr) {
    int i = 0, counter_math_symb = 0, counter_digits = 0, counter_func = 0, func = 0, res = 0;
    while (expr[i] != '\0') {
        if (expr[i] != '#' && is_math_func(expr[i])) {
            func++; counter_func++;
        } else if (is_digit(expr[i]) || expr[i] == 'x') {
            while (is_digit(expr[i + 1])) i++; {
                counter_digits++;
            }
        } else if (is_math_symbol(expr[i])) {
            counter_math_symb++;
        }
        i++;
    }

    if (counter_func == 1 && counter_digits == 1) {
        res = (counter_math_symb == 0);
    } else if (func == 0 || (func > 1 && counter_func == counter_digits)) {
        res = (counter_digits == counter_math_symb + 1);
    } else if (counter_digits > 1 && counter_digits > counter_func) {
        res = (counter_digits == counter_math_symb + 1);
    }
    return res;
}
