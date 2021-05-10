#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TESTFUNCTIONSNUM 11

#define ROOTPRECISION 0.0001 // root calculation precision
#define INTEGRALPRECISION 0.0001 // integral calculation precision
#define XFROM 0.264
#define XTO 3.0

// command line arguments flags
#define HELPFLAG 0x80
#define ROOTFLAG 0x40
#define COUNTFLAG 0x20
#define PRETESTFLAG 0x10

// holds states set by command line parameters
static unsigned char flags = 0x0;


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


// main functions

// y = e^(-x) + 3
extern double f1(double x);

// y = 2x - 2
extern double f2(double x);

// y = 1 / x
extern double f3(double x);

//double f1(double x) { 
//    return exp(-x) + 3.0; 
//}

//double f2(double x) {
//    return 2.0 * x - 2.0;
//}

//double f3(double x) { 
//    return 1 / x; 
//}

// Finding a root by the Chord Method. x_from and x_to preserve the left and right bounds of the current interval.
double root(double (*func1)(double), double (*func2)(double), double x_from, double x_to, double precision) {
    double f_from = func2(x_from) - func1(x_from);
    double f_to = func2(x_to) - func1(x_to);
    double f_new;
    double x_new = x_from, x_old = x_to;

    int itercount = 1;
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
        ++itercount;
    }

    if (flags & COUNTFLAG)
        printf("%d", itercount);

    return x_new;
}

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

// Area bounded between 3 functions
double area(double (*func1)(double), double (*func2)(double), double (*func3)(double), double x_from, double x_to) {
    double x12, x23, x31;

    if (flags & COUNTFLAG) {
        printf("func1 and func2 root required ");
        x12 = root(func1, func2, x_from, x_to, ROOTPRECISION);
        printf(" iterations to be calculated\n"
               "func2 and func3 root required ");
        x23 = root(func2, func3, x_from, x_to, ROOTPRECISION);
        printf(" iterations to be calculated\n"
               "func3 and func1 root required ");
        x31 = root(func3, func1, x_from, x_to, ROOTPRECISION);
        printf(" iterations to be calculated\n\n");

    } else {
        x12 = root(func1, func2, x_from, x_to, ROOTPRECISION);
        x23 = root(func2, func3, x_from, x_to, ROOTPRECISION);
        x31 = root(func3, func1, x_from, x_to, ROOTPRECISION);
    }

    if (flags & ROOTFLAG) {
        printf("func1 and func2 intersect at the point x = %lf \n", x12);
        printf("func2 and func3 intersect at the point x = %lf \n", x23);
        printf("func3 and func1 intersect at the point x = %lf \n\n", x31);
    }

    double i1 = integral(func1, x31, x12, INTEGRALPRECISION);
    double i2 = integral(func2, x12, x23, INTEGRALPRECISION);
    double i3 = integral(func3, x23, x31, INTEGRALPRECISION);
    return i1 + i2 + i3;
}


// Testing tools
// all functions for testing
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
        assert_equal(root(test->func1, test->func2, test->from, test->to, test->precision), test->true_value, test->precision);
}

void pretest() {
    RootTest root_test_1 = {"f1_test f3_test", f1_test, f3_test, 1,     2,   ROOTPRECISION, 1.158312395177700};
    RootTest root_test_2 = {"f2_test f5_test", f2_test, f5_test, 1,     2,   ROOTPRECISION, 1.661058635519296};
    RootTest root_test_3 = {"f1      f0_test", f1,      f0_test, XFROM, XTO, ROOTPRECISION, 1.202004558148803};
    RootTest root_test_4 = {"f2      f6_test", f2,      f6_test, XFROM, XTO, ROOTPRECISION, 1.925017246276293};
    RootTest root_test_5 = {"f6_test f2_test", f6_test, f2_test, 1,     2,   ROOTPRECISION, 1.640661448622048};
    RootTest root_test_6 = {"f6_test f2_test", f4_test, f7_test, 3,     4,   ROOTPRECISION, 3.461215571832334};
    RootTest root_test_7 = {"f4_test f7_test", f3,      f2,      XFROM, XTO, ROOTPRECISION, 1.366025403784439};

    IntegralTest integral_test_1  = {"f1_test", f1_test,  1,  2, INTEGRALPRECISION, 3.608197662162};
    IntegralTest integral_test_2  = {"f2_test", f2_test,  2,  3, INTEGRALPRECISION, 2.541666666667};
    IntegralTest integral_test_3  = {"f3_test", f3_test,  3,  4, INTEGRALPRECISION, 5.100000000000};
    IntegralTest integral_test_4  = {"f4_test", f4_test,  5,  6, INTEGRALPRECISION, 1.703367253198};
    IntegralTest integral_test_5  = {"f5_test", f5_test,  7,  8, INTEGRALPRECISION, 0.069754868431};
    IntegralTest integral_test_6  = {"f6_test", f6_test,  9, 10, INTEGRALPRECISION, 1.043954274731};
    IntegralTest integral_test_7  = {"f7_test", f7_test, 11, 12, INTEGRALPRECISION, 5.664149972183};
    IntegralTest integral_test_8  = {"f1",      f1     , 13, 14, INTEGRALPRECISION, 3.000001428801};
    IntegralTest integral_test_9  = {"f2",      f2     , 15, 16, INTEGRALPRECISION, 29.00000000000};
    IntegralTest integral_test_10 = {"f3",      f3     , 17, 18, INTEGRALPRECISION, 0.057158413840};

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
    printf("Test root()...\n"
           "Method: Chords\n"
           "func1: <%d>\n"
           "func2: <%d>\n"
           "interval: [%.12lf, %.12lf]\n"
           "precision: %.12lf\n"
           "calculated value: %.12lf\n"
           "\n",
            func1_index, func2_index, x_from, x_to, precision, root(test_functions[func1_index], test_functions[func2_index], x_from, x_to, precision));
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

int main(int argc, char *argv[]) {

    for (int i = 1; i < argc; ++i) {
        if ((strcmp(argv[i], "-help") == 0) && !(flags & HELPFLAG)) {
            printf("Available keywords:\n"
               "    -help : display all keywords\n"
               "    -pretest : run predefined tests of the root and integral functions\n"
               "    -x : display function intersections x coordinates\n"
               "    -c : display number of iterations needed to find roots\n"
               "\n"
               "    -root_t <f1_i> <f2_i> <from> <to> <prec> : runs root() with given parameters\n"
               "        <f1_i> : [int] index of the first function (from the Function List)\n"
               "        <f2_i> : [int] index of the second function (from the Function List)\n"
               "        <from> : [double] lower root search boundary\n"
               "        <to>   : [double] upper root search boundary\n"
               "        <prec> : [double] calculation precision\n"
               "\n"
               "    -integral_t <func_i> <from> <to> <prec> : runs integral() with given parameters\n"
               "        <func_i> : [int] index of the first function (from the Function List)\n"
               "        <from>   : [double] lower integral boundary\n"
               "        <to>     : [double] upper integral boundary\n"
               "        <prec>   : [double] calculation precision\n"
               "\n"
               "Function List:\n"
               "    [0] y = 2^x + 1\n"
               "    [1] y = 3(0.5 / (x + 1) + 1)\n"
               "    [2] y = 0.35x^2 - 0.95x + 2.7\n"
               "    [3] y = 0.6x + 3\n"
               "    [4] y = ln(x)\n"
               "    [5] y = 3 / ((x - 1)^2 + 1)\n"
               "    [6] y = 1 + 4 / (x^2 + 1)\n"
               "    [7] y = ln(x)^2 - 0.3\n"
               "    [8] y = e^(-x) + 3\n"
               "    [9] y = 2x - 2\n"
               "   [10] y = 1 / x\n"
               "\n");
            flags |= HELPFLAG;
        }
        else 
        if (strcmp(argv[i], "-x") == 0) {
            flags |= ROOTFLAG;
        }
        else
        if (strcmp(argv[i], "-c") == 0) {
            flags |= COUNTFLAG;
        }
        else
        if ((strcmp(argv[i], "-pretest") == 0) && !(flags & PRETESTFLAG)) {
            char t_flags = flags;
            flags &= ~COUNTFLAG; // temporeraly sets COUNTFLAG to zero
            pretest(ROOTPRECISION, INTEGRALPRECISION);
            flags = t_flags;
            flags |= PRETESTFLAG;

        }
        else
        if (strcmp(argv[i], "-root_t") == 0) {
            char t_flags = flags;
            flags &= ~COUNTFLAG; // temporeraly sets COUNTFLAG to zero
            char **endptr = NULL;
            root_test(strtol(argv[i + 1], endptr, 10), strtol(argv[i + 2], endptr, 10), strtod(argv[i + 3], endptr), strtod(argv[i + 4], endptr), strtod(argv[i + 5], endptr));
            flags = t_flags;
            i += 5;
        } 
        else
        if (strcmp(argv[i], "-integral_t") == 0) {
            char t_flags = flags;
            flags &= ~COUNTFLAG; // temporeraly sets COUNTFLAG to zero
            char **endptr = NULL;
            integral_test(strtol(argv[i + 1], endptr, 10),  strtod(argv[i + 2], endptr), strtod(argv[i + 3], endptr), strtod(argv[i + 4], endptr));
            flags = t_flags;
            i += 4;
        }
    }

    printf("Calculating area between functions f1, f2 and f3...\n"
           "root precision: %.12lf\n"
           "integral precision: %.12lf\n"
           "interval: [%.12lf, %.12lf]\n"
           "result: %.12lf\n",
            ROOTPRECISION, INTEGRALPRECISION, XFROM, XTO, area(f1, f2, f3, XFROM, XTO));

    return 0;
}