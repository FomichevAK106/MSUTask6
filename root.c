#include "main_math.h"
#include <math.h>
#include <stdio.h>

// Finding a root by the Chord Method. x_from and x_to preserve the left and right bounds of the current interval. Adds the number of iterations to itercount argument.
double root(double (*func1)(double), double (*func2)(double), double x_from, double x_to, double precision, int *itercount) {
    double f_from = func2(x_from) - func1(x_from);
    double f_to = func2(x_to) - func1(x_to);
    double f_new;
    double x_new = x_from, x_old = x_to;

    ++(*itercount);
    while (fabs(x_new - x_old) > precision) {
        x_old = x_new;
        x_new = x_from - f_from * (x_to - x_from) / (f_to - f_from);
        f_new = func2(x_new) - func1(x_new);

        if (f_new * f_from < 0) {
            f_to = f_new;
            x_to = x_new;
        } else {
            f_from = f_new;
            x_from = x_new;
        }
        ++(*itercount);
    }

    return x_new;
}
