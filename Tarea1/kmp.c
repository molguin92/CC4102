#include<stdio.h>
#include<string.h>
#include "kmp.h"

/*
 * Implementation of the Knuth-Morris-Pratt string search algorithm.
 * Based on wikipedia's (https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm)
 * description of the algorithm.
 */

int KMPSearch ( char * pattern, char * text, int * comp )
{
    // returns the number of occurrences of
    // pattern in text.

    int count = 0; //number of occurrences
    int index_t = 0; //current index in the text
    int index_p = 0; //current index in the pattern
    size_t len = strlen ( pattern );
    int lps_table[len];
    *comp = 0;

    //first, we calculate the prefix table.
    computeLPSArray (pattern, len, lps_table);

    while ( text[index_t + index_p] != '\0')
    {
        *comp++;
        if ( pattern[index_p] == text[index_t + index_p] )
        {
            if ( index_p == len - 1)
            {
                //found a match
                count++;
                index_p = 0;
                index_t++;
                continue;
            }
            else
                //keep searching
                index_p++;
        }
        else
        {
            //mismatch
            if ( lps_table[index_p] > -1 )
            {
                //fall back according to the table.
                index_t += index_p - lps_table[index_p];
                index_p = lps_table[index_p];
            }
            else
            {
                //no fallback possible, just move forward.
                index_p = 0;
                index_t++;
            }
        }
    }

    return  count;
}

void computeLPSArray ( char * pattern, int len_patt, int * lps_table )
{
    // populates the prefix table.

    int pos = 2;
    int cnd = 0;

    lps_table[0] = -1;
    lps_table[1] = 0;

    while ( pos < len_patt )
    {
        if ( pattern[pos - 1] == pattern[cnd] )
        {
            cnd++;
            lps_table[pos] = cnd;
            pos++;
        }
        else if ( cnd > 0 )
            cnd = lps_table[cnd];
        else
        {
            lps_table[pos] = 0;
            pos++;
        }
    }
}