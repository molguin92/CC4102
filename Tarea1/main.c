//
// Created by arachnid92 on 23-09-15.
//

#include <stdio.h>
#include "brute_force.h"
#include "kmp.h"
#include "boyermoore.h"

int main ( char argc, char * argv[] )
{

    char * pattern = "abcaba";
    char * text = "xxxxxxxxxxxxxxabcababcabaxxxxxx";
    size_t len = 2;

    int count = brute_force( pattern, text );

    fprintf ( stdout, "Ocurrences of %s in %s: %d\n", pattern, text, count);

    count = KMPSearch (pattern, text);

    fprintf ( stdout, "Ocurrences of %s in %s: %d\n", pattern, text, count);

    count = bmSearch ( pattern, text );

    fprintf ( stdout, "Ocurrences of %s in %s: %d\n", pattern, text, count);

    return 0;
}
