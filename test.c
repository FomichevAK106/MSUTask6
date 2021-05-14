#include "test.h"
#include "main_math.h"
#include <stdio.h>
#include <math.h>

// testing functions

// y = 2^x + 1
double f0_test(double x) {
    return pow(2, x) + 1;
}

// y = 3(0.5 / (x + 1) + 1)
double f1_test(double x) {
    return 3 * (0.5 / (x + 1) + 1);
}

// y = 0.35x^2 - 0.95x + 2.7
double f2_test(double x) {
    return 0.35 * x * x - 0.95 * x + 2.7;
}

// y = 0.6x + 3
double f3_test(double x) {
    return 0.6 * x + 3;
}

// y = ln(x)
double f4_test(double x) {
    return log(x);
}

// y = 3 / ((x - 1)^2 + 1)
double f5_test(double x) {
    return 3 / ((x - 1) * (x - 1) + 1);
}

// y = 1 + 4 / (x^2 + 1)
double f6_test(double x) {
    return 1 + 4 / (x * x + 1);
}

// y = ln(x)^2 - 0.3
double f7_test(double x) {
    return log(x) * log(x) - 0.3;
}

double (*test_functions[TESTFUNCTIONSNUM])(double) = {
    f0_test, // y = 2^x + 1
    f1_test, // y = 3(0.5 / (x + 1) + 1)
    f2_test, // y = 0.35x^2 - 0.95x + 2.7
    f3_test, // y = 0.6x + 3
    f4_test, // y = ln(x)
    f5_test, // y = 3 / ((x - 1)^2 + 1)
    f6_test, // y = 1 + 4 / (x^2 + 1)
    f7_test, // y = ln(x)^2 - 0.3
    f1,
    f2,
    f3
};

// Testing tools

// checks if two values are equal with certain precision
void assert_equal(double val1, double val2, double precision) {
    printf("%18.12lf %18.12lf %18.12lf %18.12lf", precision, val1, val2, val1 - val2);
    if (fabs(val2 - val1) > precision)
        printf(" ---> Attention: value does not meet precision criteria!");
    printf("\n");
}

// runs integral test
void runI(IntegralTest *test) {
        printf("%-18s %8.5lf %10.5lf ", test->name, test->from, test->to);
        assert_equal(integral(test->func, test->from, test->to, test->precision), test->true_value, test->precision);
}

// runs root test
void runR(RootTest *test) {
        printf("%-18s %8.5lf %10.5lf ", test->name, test->from, test->to);
        int temp = 0;
        assert_equal(root(test->func1, test->func2, test->from, test->to, test->precision, &temp), test->true_value, test->precision);
}

void pretest(double root_precision, double integral_precision) {
    RootTest root_test_1 = {"f1_test f3_test", f1_test, f3_test, 1,     2, 0.0001, 1.158312395177700};
    RootTest root_test_2 = {"f2_test f5_test", f2_test, f5_test, 1,     2, 0.0002, 1.661058635519296};
    RootTest root_test_3 = {"f1      f0_test", f1,      f0_test, 0.256, 3, 0.0003, 1.202004558148803};
    RootTest root_test_4 = {"f2      f6_test", f2,      f6_test, 0.256, 3, 0.0004, 1.925017246276293};
    RootTest root_test_5 = {"f6_test f2_test", f6_test, f2_test, 1,     2, 0.0005, 1.640661448622048};
    RootTest root_test_6 = {"f6_test f2_test", f4_test, f7_test, 3,     4, 0.0006, 3.461215571832334};
    RootTest root_test_7 = {"f4_test f7_test", f3,      f2,      0.256, 3, 0.0007, 1.366025403784439};

    IntegralTest integral_test_1  = {"f1_test", f1_test,  1,  2, 0.0001, 3.608197662162};
    IntegralTest integral_test_2  = {"f2_test", f2_test,  2,  3, 0.0001, 2.541666666667};
    IntegralTest integral_test_3  = {"f3_test", f3_test,  3,  4, 0.0001, 5.100000000000};
    IntegralTest integral_test_4  = {"f4_test", f4_test,  5,  6, 0.0001, 1.703367253198};
    IntegralTest integral_test_5  = {"f5_test", f5_test,  7,  8, 0.0001, 0.069754868431};
    IntegralTest integral_test_6  = {"f6_test", f6_test,  9, 10, 0.0001, 1.043954274731};
    IntegralTest integral_test_7  = {"f7_test", f7_test, 11, 12, 0.0001, 5.664149972183};
    IntegralTest integral_test_8  = {"f1",      f1     , 13, 14, 0.0001, 3.000001428801};
    IntegralTest integral_test_9  = {"f2",      f2     , 15, 16, 0.0001, 29.00000000000};
    IntegralTest integral_test_10 = {"f3",      f3     , 17, 18, 0.0001, 0.057158413840};

    printf("Test root()...\n"
           "Method: Chords\n"
           "func1   func2       from       to          precision          calculated val     true val(Wolfram)  delta:\n");
    runR(&root_test_1);
    runR(&root_test_2);
    runR(&root_test_3);
    runR(&root_test_4);
    runR(&root_test_5);
    runR(&root_test_6);
    runR(&root_test_7);

    printf("\nTest integral()...\n"
           "Method: Mean Rectangles\n"
           "func                from       to          precision          calculated val     true val(Wolfram)  delta:\n");
    runI(&integral_test_1);
    runI(&integral_test_2);
    runI(&integral_test_3);
    runI(&integral_test_4);
    runI(&integral_test_5);
    runI(&integral_test_6);
    runI(&integral_test_7);
    runI(&integral_test_8);
    runI(&integral_test_9);
    runI(&integral_test_10);

    printf("\n");
}

void root_test(int func1_index, int func2_index, double x_from, double x_to, double precision) {
	int temp = 0;
    printf("Test root()...\n"
           "Method: Chords\n"
           "func1: <%d>\n"
           "func2: <%d>\n"
           "interval: [%.12lf, %.12lf]\n"
           "precision: %.12lf\n"
           "calculated value: %.12lf\n"
           "\n",
            func1_index, func2_index, x_from, x_to, precision, root(test_functions[func1_index], test_functions[func2_index], x_from, x_to, precision, &temp));
}

void integral_test(int func_index, double x_from, double x_to, double precision) {
    printf("Test integral()...\n"
           "Method: Mean Rectangles\n"
           "func: <%d>\n"
           "interval: [%.12lf, %.12lf]\n"
           "precision: %.12lf\n"
           "calculated value: %.12lf\n"
           "\n",
            func_index, x_from, x_to, precision, integral(test_functions[func_index], x_from, x_to, precision));
}
