#include "input_parse.h"

struct expr* read_expr(void) {
    int size_str = SIZE_STR_PART;
    struct expr* expr = create_new_expr(size_str);
    if (expr != NULL) {
        char c;
        do {
            c = read_symbol(expr, &size_str);
        } while (c != '\n' && c != EOF);

        if (c ==- EOF) {
            free(expr);
            expr = NULL;
        } else if (c == '\n') {
                func_names_to_abbrev(expr);
                end_read_expr(expr);
                write_expr_to_f_in(expr);
        }
    }
    return expr;
}

struct expr *create_new_expr(int size_str) {
    struct expr *s = (struct expr*)malloc(sizeof(struct expr));
    if (s != NULL) {
        s->len = 0;
        s->in_str = (char*)malloc(size_str * sizeof(char));
        if (s->in_str == NULL) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

char read_symbol(struct expr *s, int *size_str) {
    char c;
    if (scanf("%c", &c) != 1) {
        free(s);
        c = EOF;
    } else {
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == 'x' || c == 'X' ||
            c == 's' || c == 'i' || c == 'n' || c == 'c' || c == 'o' || c == 't' || c == 'a' || c == '^' ||
            c == 'g' || c == 'q' || c == 'r' || c == 'l' || c == 'G' || c == 'Q' || c == 'R' || c == 'L' ||
            c == 'S' || c == 'I' || c == 'N' || c == 'C' || c == 'O' || c == 'T' || c == 'A') {
            if (c >= 'A' && c <= 'Z') c = c + 32;
            if (c == '-' && (s->in_str[(s->len) - 1] == '(' ||
                is_math_symbol(s->in_str[(s->len) - 1]) || s->len == 0)) c = '#';
            if (s->len == *size_str) {
                *size_str = s->len + SIZE_STR_PART;
                char *a = (char*)realloc(s->in_str, *size_str);
                if (a == NULL) {
                    c = EOF;
                } else {
                    s->in_str = a;
                }
            }
        }
        if (c != EOF) {
            (s->in_str[s->len]) = c;
            s->len++;
        }
    }
    return c;
}

void end_read_expr(struct expr *s) {
    int i = 0, size_in_str = s->len, size_f_in = s->len, size_pn = 0;
    s->in_str[size_in_str] = '\0';
    while (s->in_str[i] != '\0') {
        if (is_digit(s->in_str[i])) {
            while (is_digit(s->in_str[i + 1])) {
                size_pn++;
                i++;
            }
        }
        size_pn += 2;
        i++;
    }

    char *a = (char*)realloc(s->in_str, size_in_str + size_f_in + size_pn);
    if (a == NULL) {
        free(s);
        s = NULL;
    } else {
        s->in_str = a;
        s->in_str[size_in_str] = '\0';
        s->f_in = s->in_str + size_in_str + 1;
        s->f_in[size_f_in] = '\0';
        s->pn = s->f_in + size_f_in + 1;
        s->pn[size_pn] = '\0';
    }
}

void func_names_to_abbrev(struct expr *expr) {
    char func_names[ROWS][COLS] = { "sin", "cos", "ctg", "tg", "sqrt", "ln" };
    char func_abbrev[COLS] = { 'a', 'b', 'z', 'd', 'e', 'f' };
    int len_func_names[COLS] = { 3, 3, 3, 2, 4, 2 };
    find_replace(expr, func_names, func_abbrev, len_func_names);
}

void find_replace(struct expr *expr, char names[][COLS], const char *abbrev, const int *len) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        char* ip = expr->in_str;
        while (ip != NULL) {
            ip = strstr(expr->in_str, names[i]);
            if (ip != NULL) {
                *(ip) = abbrev[i];
                for (j = 1; j < len[i]; j++) {
                    ip[j] = ' ';
                }
            }
        }
    }
}

void write_expr_to_f_in(struct expr *expr) {
    int i = 0, j = 0;
    while (expr->in_str[i] != '\0') {
        if (expr->in_str[i] != ' ') {
            expr->f_in[j] = expr->in_str[i];
            j++;
        }
        i++;
    }
    expr->f_in[j] = '\0';
}
