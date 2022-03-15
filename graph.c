#include "graph.h"

int main() {
    char **screen = NULL;
    system("clear");
    struct expr *expr_in = read_expr();
    if (expr_in != NULL) {
        convert_to_pn(expr_in->f_in, expr_in->pn);
        if (is_correct_expression(expr_in->pn)) {
            screen = (char**)malloc(SCR_H * sizeof(char*) + SCR_H * (SCR_W + 1) * sizeof(char));
            for (int i = 0; i < SCR_H; i++)
            screen[i] = (char*)screen + SCR_H * sizeof(char**) + i * (SCR_W + 1);
            init_table_screen(screen);
            fill_table_screen(screen, expr_in->pn);
            draw_graph(screen);
        } else {
            printf("n/a");
        }
        free(expr_in);
        free(screen);
    }
    return 0;
}

void init_table_screen(char **screen) {
  for (int i = 0; i < SCR_H; i++) {
    for (int j = 0; j < SCR_W; j++) {
      screen[i][j] = '.';
    }
    screen[i][80] = '\0';
  }
}

void fill_table_screen(char** screen, char* func) {
    double max_x = MAX_X;
    double x = (max_x / (SCR_W - 1));
    for (int i = 0; i < SCR_W; i++) {
        double y = calculate(func, x * i);
        long screen_y = lround((y - MIN_Y) / (MAX_Y - MIN_Y) * (SCR_H - 1));
        if (screen_y >= 0 && screen_y < SCR_H)
            screen[screen_y][i] = '*';
    }
}

void draw_graph(char **screen) {
  printf("\033c");
  for (int i = SCR_H - 1; i >=0; i--) {
    printf("%s\n", screen[i]);
  }
}

double calculate(char* expr, double x) {
    st_calc* pn = NULL;
    double out = 0;
    int i = 0;
    while (expr[i] != '\0') {
        if (is_digit(expr[i])) {
            int k = 1;
            double num = 0;
            while (is_digit(expr[i + k])) k++;
            while (k) {
                num += symb_to_digit(expr[i], &k);
                i++;
            }
            pn = push_calc(pn, num);
        } else if ((expr[i]) == 'x') {
            pn = push_calc(pn, x);
        } else if (is_math_symbol(expr[i])) {
            pn = operation(expr[i], pn);
        } else if (is_math_func(expr[i])) {
            pn = function(expr[i], pn);
        }
        i++;
    }
    if (pn != NULL) out = (pn->digit);
    pop_calc(&pn);
    return out;
}

double symb_to_digit(char value, int* len_value) {
    double d = 0;
    d += ((int)value + 2) % 10 * pow(10, *len_value - 1);
    *len_value = *len_value - 1;
    return d;
}
