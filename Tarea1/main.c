//
// Created by arachnid92 on 23-09-15.
//

#include <stdio.h>
#include "brute_force.h"

int main ( char argc, char * argv[] )
{

    char * pattern = argv[1];
    char * text = argv[2];

    int count = brute_force( pattern, text);

    fprintf ( stdout, "Ocurrences of %s in %s: %d\n", pattern, text, count);

    return 0;
}
