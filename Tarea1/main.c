//
// Created by arachnid92 on 23-09-15.
//

#include <stdio.h>
#include "brute_force.h"
#include "kmp.h"
#include "boyermoore.h"
#include "generator.h"

int main ( char argc, char * argv[] )
{

    //generatePatterns ("01");


    char * pattern = "11";
    char * text = "11111111111111";
    size_t len = 2;

    int count = brute_force( pattern, text );

    fprintf ( stdout, "Ocurrences of %s in %s: %d\n", pattern, text, count);

    count = KMPSearch (pattern, text);

    fprintf ( stdout, "Ocurrences of %s in %s: %d\n", pattern, text, count);

    count = bmSearch ( pattern, text );

    fprintf ( stdout, "Ocurrences of %s in %s: %d\n", pattern, text, count);

    return 0;
}
