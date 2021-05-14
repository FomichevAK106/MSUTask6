#ifndef MAIN_MATH_H
#define MAIN_MATH_H

// Finding a root by the Chord Method. x_from and x_to preserve the left and right bounds of the current interval.
double root(double (*func1)(double), double (*func2)(double), double x_from, double x_to, double precision, int *itercount);

// Calculates integral with the Mean Rectangles Method
// Runge formula is used for estimation. (for the Mean Rectangles Method coef. = 1/3): I - In ~ 1/3 * (I2n - In)
double integral(double (*func)(double), double x_from, double x_to, double precision);

#endif