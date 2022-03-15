#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_
#include <math.h>
#define _USE_MATH_DEFINES
#include "stack.h"
#include "conditions.h"
#include "input_parse.h"
#include "pn.h"
#define _CRT_SECURE_NO_WARNINGS

#define MIN_Y -1
#define MAX_Y 1
#define MIN_X 0
#define MAX_X 4.0 * M_PI
#define SCR_H 25
#define SCR_W 80

void init_table_screen(char **screen);
void draw_graph(char **screen);
void fill_table_screen(char **screen, char *func);
double calculate(char* expr, double x);

#endif  // SRC_GRAPH_H_
