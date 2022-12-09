#include <stdio.h>
#include <math.h>

static const char exp1_str[] = "y = 1 - 1/4 sin^2(2x) + cos(2x);";
static const char exp2_str[] = "y = cos^2(x) + cos^4(x);";
double calc_exp1(double angle);
double calc_exp2(double angle);

int main(void)
{
    int exp_no, res;
    double angle;

    printf("\n\nWelcome! This application calculates the values of predefined trigonometric expressions given an angle in radians. \nInput format: [expression number (int)] [calc at x value (double)].\n\nExpression 1: %s\nExpression 2: %s\n\nInput: ", exp1_str, exp2_str);
    
    input:
    if(res = scanf("%i %lf", &exp_no, &angle) == 2)
    {
        switch (exp_no)
        {
        case 0:
            break;
        case 1:
            printf("\n\nCalculation result: %lf;\nContinue with the application of input '0 0' to exit.\n\nInput: ", calc_exp1(angle));
            goto input;
        case 2:
            printf("\n\nCalculation result: %lf;\nContinue with the application of input '0 0' to exit.\n\nInput: ", calc_exp2(angle));
            goto input;
        default:
            printf("\nInvalid input, please try again! Input '0 0' to exit.\n\nInput: ");
            goto input;
        }
    }
    else
    {
        printf("\nError: scanf() function did not execute successfully.\n\n");
    }

    printf("\n\nThanks for using this application! Exiting.\n\n");

    return 0;
}

double calc_exp1(double angle)
{
    angle += angle;
    
    return 1 - pow(sin(angle), 2)/4 + cos(angle);
}

double calc_exp2(double angle)
{
    double cossq = pow(cos(angle), 2);

    return cossq + pow(cossq, 2);
}