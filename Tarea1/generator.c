//
// Created by arachnid92 on 24-09-15.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "generator.h"

void generate_text ( size_t len_alphabet, char * alphabet, size_t size_text )
{

    /*
     * char = 8bits = 1byte
     */

    int init_t = time();
    char * text = ( char * ) malloc ( ( size_text + 1 ) * sizeof ( char ) );

    size_t i;
    size_t j;
    char c;
    FILE * f;

    srand (time(NULL));
    text[size_text] = '\0';

    for ( i = 0; i < size_text; i++ )
    {
        j = rand() % len_alphabet;
        c = alphabet[j];
        text[i] = c;
    }


    f = fopen ( "gen_text.out", "w" );
    fprintf ( f, text );

}
