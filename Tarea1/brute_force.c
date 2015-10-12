//
// Created by arachnid92 on 23-09-15.
// Implementation of a naive (brute force) string search algorithm.
//

#include "brute_force.h"

int brute_force ( char pattern[], char text[], int * comp )
{
    // returns the number of occurrences of pattern in text.
    int count = 0;
    int i, j, k;
    *comp = 0;

    for ( i = 0; text[i] != '\0' ;i++ )
    {
        /* k is a temporary index for checking substrings of the text */
        k = i;
        for ( j = 0; ;j++ )
        {
            (*comp)++;
            if ( pattern[j] == '\0' )
            {
                /*
                 * Reached the end of the pattern
                 * <==>
                 * Found an ocurrence of the pattern in the text.
                 */
                count++;
                (*comp)--;
                break;
            }
            else if ( text[k] == pattern[j] )
            {
                /*
                 * Characters match.
                 * Move both indexes one step to the right and
                 * compare again.
                 */
                k++;
                continue;
            }
            else
                /*
                 * Characters don't match
                 * Reset the pattern index, and move the text index
                 * a step to the right.
                 */
                break;
        }
    }
    return count;
}