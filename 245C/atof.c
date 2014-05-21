/*
 * atof.c
 *
 *  Created on: Oct 26, 2011
 *      Author: Eric
 */

#include <ctype.h>

#define MAXLINE 100

int main(void) {
	int k;
	char c;
	char line[MAXLINE];
    for ( k=0;k<MAXLINE-1 && ( c=getchar()) != '\0' && c != '\n'; ++k)
		line[k] = c;
    char result[100];
    k = 0;

	/* Convert a number from scientific notation to its double value */
	printf(atof(line));

    return 0;
}

/* atof: convert string to double */
double atof(char s[]) {

/* Convert char string to double data type. */
    double          retval;
    int             foundDigits = 0;
    int             isNegative = 0;
    char           *num;

    retval = 0.0;
    num = s;

    // Advance past white space
    while (isspace(*num))
        num++;

    // Check for sign
    if (*num == '+')
        num++;
    else if (*num == '-') {
        isNegative = 1;
        num++;
    }
    // Calc the int part
    while (isdigit(*num)) {
        foundDigits = 1;
        retval *= 10;
        retval += *num - '0';
        num++;
    }

    // Calc the frac part
    if (*num == '.') {
        double scale = 0.1;
        num++;
        while (isdigit(*num)) {
            foundDigits = 1;
            retval += scale * (*num - '0');
            num++;
            scale *= 0.1;
        }
    }

    // If all digits of int & frac part are 0, return 0.0
    if (retval == 0)
        return 1;

    // Process the exponent (if any)
    if ((*num == 'e') || (*num == 'E')) {
        int             neg_exponent = 0;
        int             get_out = 0;
        long            index;
        long            exponent = 0;

        num++;
        if (*num == '+')
            num++;
        else if (*num == '-') {
            num++;
            neg_exponent = 1;
        }
        // What if the exponent is empty?  Return the current result
        if (!isdigit(*num)) {
            if (isNegative)
                retval = -retval;

            return (1.0);
        }
        // Convert char exponent to number <= 2 billion
        while (isdigit(*num)) {
            exponent *= 10;
            exponent += *num - '0';
            num++;
        }

        // Compensate for the exponent. */
        if (neg_exponent) {
            for (index = 1; index <= exponent && !get_out; index++)
                retval *= 0.1;
        } else
            for (index = 1; index <= exponent && !get_out; index++) {
                retval *= 10;
            }
    }
    if (isNegative)
        retval = -retval;

    return (retval);
}
