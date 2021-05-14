#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "main_math.h"
#include "test.h"

// holds states set by command line parameters
double global_root_precision = 0.000005; // root calculation precision
double global_integral_precision = 0.000005; // integral calculation precision
double global_x_from = 0.264;
double global_x_to = 3.0;

// command line arguments flags
unsigned char help_flag = 0;
unsigned char root_flag = 0;
unsigned char count_flag = 0;
unsigned char verbose_flag = 0;
unsigned char pretest_flag = 0;
unsigned char root_test_flag = 0;
unsigned char integral_test_flag = 0;


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

// Area bounded between 3 functions
double area(double (*func1)(double), double (*func2)(double), double (*func3)(double), double x_from, double x_to, char display_iter_count, char display_roots) {
    int itercount12 = 0, itercount23 = 0, itercount31 = 0;
    double x12 = root(func1, func2, x_from, x_to, global_root_precision, &itercount12);
    double x23 = root(func2, func3, x_from, x_to, global_root_precision, &itercount23);
    double x31 = root(func3, func1, x_from, x_to, global_root_precision, &itercount31);

    if (display_iter_count) {
        printf("func1 and func2 root required %d iterations to be calculated\n"
               "func2 and func3 root required %d iterations to be calculated\n"
               "func3 and func1 root required %d iterations to be calculated\n\n",
               itercount12,
               itercount23,
               itercount31);
    }

    if (display_roots) {
        printf("func1 and func2 intersect at the point x = %lf \n", x12);
        printf("func2 and func3 intersect at the point x = %lf \n", x23);
        printf("func3 and func1 intersect at the point x = %lf \n\n", x31);
    }

    double i1 = integral(func1, x31, x12, global_integral_precision);
    double i2 = integral(func2, x12, x23, global_integral_precision);
    double i3 = integral(func3, x23, x31, global_integral_precision);
    return i1 + i2 + i3;
}

int main(int argc, char *argv[]) {

    for (int i = 1; i < argc; ++i) {
        if ((strcmp(argv[i], "-help") == 0) && !(help_flag)) {
            help_flag = 1;
            printf("Available keywords:\n"
               "    -help : display all keywords\n"
               "    -verbose : display task description\n"
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
        }
        else
        if (strcmp(argv[i], "-x") == 0) {
            root_flag = 1;
        }
        else
        if (strcmp(argv[i], "-c") == 0) {
            count_flag = 1;
        }
        else
        if (strcmp(argv[i], "-verbose") == 0) {
            verbose_flag = 1;
            printf("Program description:\n"
                "    Calculates area surrounded by 3 curves of given functions with set precision.\n"
                "    f1: y = e^(-x) + 3\n"
                "    f2: y = 2x - 2\n"
                "    f3: y = 1 / x\n"
                "    Root search interval: [%lf, %lf]\n"
                "    Root calculation precision: %lf\n"
                "    Root calculation method: Chords\n"
                "    Integral calculation precision: %lf\n"
                "    Integral caluclation method: Mean Rectangles\n"
                "\n",
                global_x_from, global_x_to, global_root_precision, global_integral_precision);
        }
        else
        if ((strcmp(argv[i], "-pretest") == 0) && !(pretest_flag)) {
            pretest_flag = 1;
            pretest(global_root_precision, global_integral_precision);
        }
        else
        if (strcmp(argv[i], "-root_t") == 0) {
            char **endptr = NULL;
            char sufficient_params = 1;
            char correct_params = 1;
            int f1_i, f2_i;
            double x_from, x_to, precision;
            root_test_flag = 1;

            char *parameter_names[5] = {"f1_i", "f2_i", "from", "to", "prec"};
            char *parameter_types[5] = {"integer", "integer", "double", "double", "double"};
            char *parameter_type_specifiers[5] = {"%d", "%d", "%lf", "%lf", "%lf"};
            void *parameters[5] = {&f1_i, &f2_i, &x_from, &x_to, &precision};

            for (int t = 0; t < 5; ++t) {
                if ((argc == i + 1) || argv[i + 1][0] == '-') {
                    printf("In -root_t:\n    "
                        "Error: Insufficient number of arguments: %d (expected 5).\n\n", t);
                    sufficient_params = 0;
                    break;
                }
                ++i;

                if (!sscanf(argv[i], parameter_type_specifiers[t], parameters[t])) {
                    printf("In -root_t:\n    "
                        "Error: Invalid <%s> parameter value: %s <--- this parameter must be [%s].\n\n", parameter_names[t], argv[i], parameter_types[t]);
                    correct_params = 0;
                }
            }
            if (!sufficient_params)
                continue;

            if (correct_params)
                root_test(f1_i, f2_i, x_from, x_to, precision);
        }
        else
        if (strcmp(argv[i], "-integral_t") == 0) {
            char **endptr = NULL;
            char sufficient_params = 1;
            char correct_params = 1;
            int func_i;
            double x_from, x_to, precision;

            integral_test_flag = 1;

            char *parameter_names[4] = {"func_i", "from", "to", "prec"};
            char *parameter_types[4] = {"integer", "double", "double", "double"};
            char *parameter_type_specifiers[4] = {"%d", "%lf", "%lf", "%lf"};
            void *parameters[4] = {&func_i, &x_from, &x_to, &precision};

            for (int t = 0; t < 4; ++t) {
                if ((argc == i + 1) || argv[i + 1][0] == '-') {
                    printf("In -integral_t:\n    "
                        "Error: Insufficient number of arguments: %d (expected 4).\n\n", t);
                    sufficient_params = 0;
                    break;
                }
                ++i;

                if (!sscanf(argv[i], parameter_type_specifiers[t], parameters[t])) {
                    printf("In -integral_t:\n    "
                        "Error: Invalid <%s> parameter value: %s <--- this parameter must be [%s].\n\n", parameter_names[t], argv[i], parameter_types[t]);
                    correct_params = 0;
                }
            }
            if (!sufficient_params)
                continue;

            if(correct_params)
                integral_test(func_i,  x_from, x_to, precision);
        }
    }

    if (!pretest_flag && !root_test_flag && !integral_test_flag && !verbose_flag) {
        printf("Calculating area between functions f1, f2 and f3...\n"
           "root precision: %.12lf\n"
           "integral precision: %.12lf\n"
           "interval: [%.12lf, %.12lf]\n"
           "result: %.12lf\n",
            global_root_precision, global_integral_precision, global_x_from, global_x_to, area(f1, f2, f3, global_x_from, global_x_to, count_flag, root_flag));
    }

    return 0;
}