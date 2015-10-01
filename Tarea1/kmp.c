//
// Created by arachnid92 on 29-09-15.
//

#include <stddef.h>
#include <stdlib.h>
#include "kmp.h"

/*
 * prefixfunction ( pattern, table, len)
 * inputs:
 *      pattern:    the text pattern to analyze
 *      table:      the prefix table to populate
 *      len:        length of the pattern (and table)
 */
void prefixfunction ( char * pattern, char * table, size_t len )
{

    /*
     * Initial conditions
     */
    table = ( char * ) malloc ( len * sizeof ( char ) );
    /*sizeof(char) = 1, but we keep it for clarity*/

    table[ 0 ] = 0;
    int j = 0;
    int i;

    while ( j < len )
    {
        i     = table[ j ];
        while ( i > 0 && pattern[ i + 1 ] != pattern[ j + 1 ] )
            i = table[ i ];

        if ( pattern[ i + 1 ] == pattern[ j + 1 ] )
            table[ j + 1 ] = i + 1;
        else
            table[ j + 1 ] = 0;

        j++;
    }
}

int knuthmorrispratt( char * pattern, char * text, size_t len_patt )
{

    /*
     * First things first: create prefix table
     */

    char * table;


}