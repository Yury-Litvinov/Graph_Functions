# Graph_Functions
Program in C for creating graphs of functions defined by arbitrary expressions.

To calculate the values ​​of expressions, used Dijkstra's algorithm for translating expressions into Polish notation.
The program is assembled using a Makefile. The name of the build stage is all. The executable file stored in the build folder named graph. ==
Conditions
The size of the field for displaying graphs is a rectangle of 25 by 80 points.
Definition area - [0; 4 Pi]
Range of values - [-1; 1]
Orientation of the coordinate plane - the ordinate axis is directed downward, the abscissa axis is directed to the right.
The center of coordinates is middle of the left border (point {0, 13}).
Not to draw axes. 
Values are rounded according to the rules of mathematics.
Possible operations & functions \ "+" \ "-" (unary and binary) \ "*" \ "/" \ "()" \ sin(x) \ cos(x) \ tan(x) \ ctg(x) \ sqrt(x) \ ln(x)
Graphics
The field displayed using Star symbol for the chart line and "." for the rest of the screen space.
Modules
Expression parsing and creating a list of lexical units.
Translation into Polish notation and calculation using this notation.
Drawing a graph in the terminal.

Example Input: sin(x) + cos(2*x)
