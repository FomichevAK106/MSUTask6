#include <stdio.h>
#include <math.h>
#define ROOTPRECISION 0.0001 // Точность вычисления корня
#define INTEGRALPRECISION 0.0001 // Точность вычисления интеграла
#define XFROM 0.264
#define XTO 3.0


// Дополнительные (тестовые) функции
double f0_test(double x) {
    return pow(2, x) + 1;
}

double f1_test(double x) {
    return 3 * (0.5 / (x + 1) + 1);
}

double f2_test(double x) {
    return 0.35 * x * x - 0.95 * x + 2.7;
}

double f3_test(double x) {
    return 0.6 * x + 3;
}

double f4_test(double x) {
    return log(x);
}

double f5_test(double x) {
    return 3 / ((x - 1) * (x - 1) + 1);
}

double f6_test(double x) {
    return 1 + 4 / (x * x + 1);
}

double f7_test(double x) {
    return log(x) * log(x) - 0.3;
}


// Основные функции
double f1(double x) {
    return exp(-x) + 3.0;
}

double f2(double x) {
    return 2 * x - 2.0;
}

double f3(double x) {
    return 1/x;
}

// Поиск корня методом хорд. В x_from и x_to поддерживаются левая и правая границы рассматриваемого отрезка соответственно.
double root(double (*func1)(double), double (*func2)(double), double x_from, double x_to, double precision) {
    double f_from = func2(x_from) - func1(x_from);
    double f_to = func2(x_to) - func1(x_to);
    double f_new;
    double x_new = x_from, x_old = x_to;
    while ((-precision > (x_new - x_old)) || ((x_new - x_old) > precision)) {
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
    }
    return x_new;
}

// Интеграл методом средних прямоугольников.
// При оценке используется формула Рунге (для метода средних отрезков коэф. = 1/3): I - In ~ 1/3 * (I2n - In)
double integral(double (*func)(double), double x_from, double x_to, double precision) {
    int reversed = x_to < x_from;
    if (reversed) {
        double tmp = x_to;
        x_to = x_from;
        x_from = tmp;
    }
    double interval = x_to - x_from;
    double tripleprecision = precision * 3.0;
    double intgr2 = func((x_from + x_to) * 0.5) * interval; // Интеграл с 2 * steps прямоугольниками
    double intgr; // Интеграл со steps количеством прямоугольников
    double h; // длина шага
    double xi; // текущий Xi = левая координата прямоугольника
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

    } while ((-tripleprecision > (intgr2 - intgr)) || ((intgr2 - intgr) > tripleprecision));

    return (reversed) ? (-intgr2) : (intgr2);
}

// Площадь области, ограниченной тремя функциями.
double area(double (*func1)(double), double (*func2)(double), double (*func3)(double), double x_from, double x_to) {
    double x12 = root(func1, func2, x_from, x_to, ROOTPRECISION);
    double x23 = root(func2, func3, x_from, x_to, ROOTPRECISION);
    double x31 = root(func3, func1, x_from, x_to, ROOTPRECISION);
    double i1 = integral(func1, x31, x12, INTEGRALPRECISION);
    double i2 = integral(func2, x12, x23, INTEGRALPRECISION);
    double i3 = integral(func3, x23, x31, INTEGRALPRECISION);
    return i1 + i2 + i3;
}

void test(double root_precision, double integral_precision) {
    double r1 = root(f1_test, f3_test, 1,2, root_precision);
    double r2 = root(f2_test, f5_test, 1, 2, root_precision);
    double r3 = root(f1, f0_test, XFROM, XTO, root_precision);
    double r4 = root(f2, f6_test, XFROM, XTO, root_precision);
    double r5 = root(f6_test, f2_test, 1, 2, root_precision);
    double r6 = root(f4_test, f7_test, 3, 4, root_precision);
    double r7 = root(f3, f2, XFROM, XTO, root_precision);

    double i1 = integral(f1_test, 1,2, integral_precision);
    double i2 = integral(f2_test, 2,3, integral_precision);
    double i3 = integral(f3_test, 3,4, integral_precision);
    double i4 = integral(f4_test, 5,6, integral_precision);
    double i5 = integral(f5_test, 7,8, integral_precision);
    double i6 = integral(f6_test, 9,10, integral_precision);
    double i7 = integral(f7_test, 11,12, integral_precision);
    double i8 = integral(f1, 13,14, integral_precision);
    double i9 = integral(f2, 15,16, integral_precision);
    double i10 = integral(f3, 17,18, integral_precision);

    printf("Test root()...\n"
           "func1   func2   precision         calculated val     true val(Wolfram)  delta:\n");
    printf("f1_test f3_test %.12lf %+18.12lf %+18.12lf %+18.12lf\n", root_precision, r1, 1.158312395177700, r1 - 1.158312395177700);
    printf("f2_test f5_test %.12lf %+18.12lf %+18.12lf %+18.12lf\n", root_precision, r2, 1.661058635519296, r2 - 1.661058635519296);
    printf("f1      f0_test %.12lf %+18.12lf %+18.12lf %+18.12lf\n", root_precision, r3, 1.202004558148803, r3 - 1.202004558148803);
    printf("f2      f6_test %.12lf %+18.12lf %+18.12lf %+18.12lf\n", root_precision, r4, 1.925017246276293, r4 - 1.925017246276293);
    printf("f6_test f2_test %.12lf %+18.12lf %+18.12lf %+18.12lf\n", root_precision, r5, 1.640661448622048, r5 - 1.640661448622048);
    printf("f4_test f7_test %.12lf %+18.12lf %+18.12lf %+18.12lf\n", root_precision, r6, 3.461215571832334, r6 - 3.461215571832334);
    printf("f3      f2      %.12lf %+18.12lf %+18.12lf %+18.12lf\n", root_precision, r7, 1.366025403784439, r7 - 1.366025403784439);

    printf("\nTest integral()...\n"
           "func     precision         calculated val     true val(Wolfram)  delta:\n");
    printf("f1_test  %.12lf %+18.12lf %+18.12lf %+18.12lf\n", integral_precision, i1, 3.608197662162, i1 - 3.608197662162);
    printf("f2_test  %.12lf %+18.12lf %+18.12lf %+18.12lf\n", integral_precision, i2, 2.541666666667, i2 - 2.541666666667);
    printf("f3_test  %.12lf %+18.12lf %+18.12lf %+18.12lf\n", integral_precision, i3, 5.100000000000, i3 - 5.100000000000);
    printf("f4_test  %.12lf %+18.12lf %+18.12lf %+18.12lf\n", integral_precision, i4, 1.703367253198, i4 - 1.703367253198);
    printf("f5_test  %.12lf %+18.12lf %+18.12lf %+18.12lf\n", integral_precision, i5, 0.069754868431, i5 - 0.069754868431);
    printf("f6_test  %.12lf %+18.12lf %+18.12lf %+18.12lf\n", integral_precision, i6, 1.043954274731, i6 - 1.043954274731);
    printf("f7_test  %.12lf %+18.12lf %+18.12lf %+18.12lf\n", integral_precision, i7, 5.664149972183, i7 - 5.664149972183);
    printf("f1       %.12lf %+18.12lf %+18.12lf %+18.12lf\n", integral_precision, i8, 3.000001428801, i8 - 3.000001428801);
    printf("f2       %.12lf %+18.12lf %+18.12lf %+18.12lf\n", integral_precision, i9, 29.00000000000, i9 - 29.00000000000);
    printf("f3       %.12lf %+18.12lf %+18.12lf %+18.12lf\n", integral_precision, i10, 0.05715841384, i10 - 0.05715841384);
}

int main(int argc, char **argv) {
    test(ROOTPRECISION, INTEGRALPRECISION);
    return 0;
}