//
// Created by arachnid92 on 04-10-15.
// Implementation of the Boyer-Moore String search
// algorithm using only the bad prefix function.
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

    //create the bad prefix table.
    int i;

    for ( i = 0; i < CHAR_MAX; i++ )
        table[ i ] = len_patt;
    for ( i = 0; i < len_patt; i++ )
        table[pattern[i]] = i;
}

int bmSearch ( char * pattern, char * text )
{
    // the actual search algorithm
    // returns the number of occurrences of pattern in text.

    size_t len = strlen ( pattern );
    int index_p = len - 1;
    int pos_patt = 0;
    int count = 0;
    int badchar[CHAR_MAX];

    badCharTable (pattern, len, badchar);

    while ( text[pos_patt + len - 1] != '\0' )
    {
        while ( index_p >= 0 && text[pos_patt + index_p] == pattern[index_p] )
            // while characters match, keep searching
            index_p--;

        if ( index_p < 0 )
        {
            // match
            count++;
            index_p = len - 1; //reset pattern index
        }

        // next we shift.
        // if the shift would be negative or zero, we instead shift 1.
        if ( 1 > (index_p - badchar[text[pos_patt + index_p]]))
            pos_patt += 1;
        else
            pos_patt += index_p - badchar[text[pos_patt + index_p]];
        index_p = len - 1; // reset pattern index

    }

    return count;

}