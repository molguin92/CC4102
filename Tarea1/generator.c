//
// Created by arachnid92 on 24-09-15.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "generator.h"

void generateRandomString(
        size_t len_alphabet,
        char *alphabet,
        size_t len_string,
        char *string
                         )
{
    size_t i;
    srand ( time ( NULL ) );

    for ( i = 0; i < len_string; i++ )
        string[ i ] = alphabet[ rand () % len_alphabet ];

}

void generatePatterns(char * alphabet)
{


    size_t len_alphabet = strlen (alphabet);
    FILE * f = fopen (strcat(alphabet, "_input.out"), "w");
    int i;
    size_t a;
    char * pattern;

    for ( i = 2; i < 8; i++ )
    {
        a = (size_t) pow(2.0, i);
        pattern = (char *)malloc (a + 1);
        pattern[a] = '\0';
        generateRandomString (len_alphabet, alphabet, a, pattern);
        fprintf (f, "%s\n", pattern);
        free(pattern);
    }

    fclose (f);

}
