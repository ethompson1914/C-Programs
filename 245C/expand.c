/*
 * expand.c
 *
 *  Created on: Oct 26, 2011
 *      Author: Eric
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 100

void expand(char * s1, char * s2);

int main(void) {
	int k;
	char c;
	char line[MAXLINE];
    for ( k=0;k<MAXLINE-1 && ( c=getchar()) != EOF && c != '\n'; ++k)
		line[k] = c;
    char result[100];
    k = 0;

    while ( line[k] ) {

        /*  Expand and print the next string in our array s[]  */

        expand(result, line[k]);
        printf("Before expansion: %s\n", line[k]);
        printf("After expansion: %s\n", result);
        ++k;
    }

    return 0;
}


/*  Expands ranges such as 'a-z' and '8-3'. Copies string s1 to s2 and
		manipulates s2 so it can be used later   */

void expand(char * s1, char * s2) {
    static char upperCaseChar[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static char lowerCaseChar[27] = "abcdefghijklmnopqrstuvwxyz";
    static char digits[11]     = "0123456789";

    char * start, * end, * p;
    int i = 0;
    int j = 0;


    /*  Loop through characters in s2  */

    while ( s2[i] ) {
        switch( s2[i] ) {
        case '-':
            if ( i == 0 || s2[i+1] == '\0' ) {

                /*  '-' is leading or trailing, so just put it
					at the end of the array  */

                s1[j++] = '-';
                ++i;
                break;
            }
            else {

                 /*  Range to expand   */

                if ( (start = strchr(upperCaseChar, s2[i-1])) &&
                     (end   = strchr(upperCaseChar, s2[i+1])) )
                    ;
                else if ( (start = strchr(lowerCaseChar, s2[i-1])) &&
                          (end   = strchr(lowerCaseChar, s2[i+1])) )
                    ;
                else if ( (start = strchr(digits, s2[i-1])) &&
                          (end   = strchr(digits, s2[i+1])) )
                    ;
                else {

                    /*  Mismatched notation (such as a-R or 1-b)  */

                    fprintf(stdout, "Error: Mismatched operands '%c-%c'\n",
                            s2[i-1], s2[i+1]);
                    s1[j++] = s2[i-1];
                    s1[j++] = s2[i++];
                    break;
                }


                /*  Expand the range  */

                p = start;
                while ( p != end ) {
                    s1[j++] = *p;
                    if ( end > start )
                        ++p;
                    else
                        --p;
                }
                s1[j++] = *p;
                i += 2;
            }
            break;

        default:
            if ( s2[i+1] == '-' && s2[i+2] != '\0' ) {
                ++i;
            }
            else {

                /*  Just a normal character, so copy it  */

                s1[j++] = s2[i++];
            }
            break;
        }
    }
    s1[j] = s2[i];    /*  For the null character  */
}
