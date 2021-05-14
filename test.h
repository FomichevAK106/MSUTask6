#ifndef TEST_H
#define TEST_H

#define TESTFUNCTIONSNUM 11

// main functions

// y = e^(-x) + 3
extern double f1(double x);

// y = 2x - 2
extern double f2(double x);

// y = 1 / x
extern double f3(double x);

// testing functions

// y = 2^x + 1
double f0_test(double x);

// y = 3(0.5 / (x + 1) + 1)
double f1_test(double x);

// y = 0.35x^2 - 0.95x + 2.7
double f2_test(double x);

// y = 0.6x + 3
double f3_test(double x);

// y = ln(x)
double f4_test(double x);

// y = 3 / ((x - 1)^2 + 1)
double f5_test(double x);

// y = 1 + 4 / (x^2 + 1)
double f6_test(double x);

// y = ln(x)^2 - 0.3
double f7_test(double x);


// all functions for testing
//double (*test_functions[TESTFUNCTIONSNUM])(double);

// Testing tools

typedef struct {
    char name[17];
    double (*func)(double);
    double from, to;
    double precision;
    double true_value;
} IntegralTest;

typedef struct {
    char name[17];
    double (*func1)(double);
    double (*func2)(double);
    double from, to;
    double precision;
    double true_value;
} RootTest;

// checks if two values are equal with certain precision
void assert_equal(double val1, double val2, double precision);

// runs integral test defined by structure IntegralTest
void runI(IntegralTest *test);

// runs root test defined by structure RootTest
void runR(RootTest *test);

// runs pretests
void pretest(double root_precision, double integral_precision);

// runs root() with given values in test mode
void root_test(int func1_index, int func2_index, double x_from, double x_to, double precision);

// runs integral() with given values in test mode
void integral_test(int func_index, double x_from, double x_to, double precision);

#endif