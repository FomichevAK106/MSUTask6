#include "main_math.h"
#include <math.h>

// Calculates integral with the Mean Rectangles Method
// Runge formula is used for estimation. (for the Mean Rectangles Method coef. = 1/3): I - In ~ 1/3 * (I2n - In)
double integral(double (*func)(double), double x_from, double x_to, double precision) {
    int reversed = x_to < x_from;
    if (reversed) {
        double tmp = x_to;
        x_to = x_from;
        x_from = tmp;
    }
    double interval = x_to - x_from;
    double tripleprecision = precision * 3.0;
    double intgr2 = func((x_from + x_to) * 0.5) * interval; // Integral with the <2 * steps> rectangles
    double intgr; // Integral with the <steps> number of rectangles
    double h; // step length
    double xi; // current Xi = left coordinate of a rectangle
    int steps = 1;
    do {
        steps *= 2;
        intgr = intgr2;
        intgr2 = 0;
        h = interval / (double)steps;
        xi = x_from;
        for (int i = 0; i < steps; ++i) {
            intgr2 += func(xi + h * 0.5) * h;
            xi += h;
        }

    } while (fabs(intgr2 - intgr) > tripleprecision);

    return (reversed) ? (-intgr2) : (intgr2);
}