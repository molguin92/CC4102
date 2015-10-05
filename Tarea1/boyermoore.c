//
// Created by arachnid92 on 04-10-15.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "boyermoore.h"

void badCharTable (
        char * pattern,
        size_t len_patt,
        int * table
                  )
{
    int i;

    for ( i = 0; i < CHAR_MAX; i++ )
        table[ i ] = len_patt;
    for ( i = 0; i < len_patt; i++ )
        table[pattern[i]] = i;

    fprintf(stderr, "Terminamos de crear tabla.\n");

}

int bmSearch ( char * pattern, char * text )
{

    size_t len = strlen ( pattern );
    int index_p = len - 1;
    int pos_patt = 0;
    int count = 0;
    int tmp_pos = 0;
    int badchar[CHAR_MAX];

    badCharTable (pattern, len, badchar);

    while ( text[pos_patt + len - 1] != '\0' )
    {
        while ( !(index_p < 0) && text[pos_patt + index_p] == pattern[index_p] )
            index_p--;

        if ( index_p < 0 )
        {
            count++;
            fprintf(stderr, "Encontramos match. %d\n", pos_patt);

            tmp_pos = pos_patt + len;
            if ( text[tmp_pos] == '\0' )
                pos_patt += 1;
            else
                pos_patt += len - badchar[text[tmp_pos]];

            index_p = len - 1;
        }
        else
            if ( 1 > (index_p - badchar[text[pos_patt + index_p]]))
                pos_patt += 1;
            else
                pos_patt += index_p - badchar[text[pos_patt + index_p]];
    }

    return count;

}