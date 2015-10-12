//
// Created by arachnid92 on 24-09-15.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "generator.h"


void generateRandomString(
        size_t len_alphabet,
        char *alphabet,
        size_t len_string,
        char *string
                         )
{

    //generates a random string from an alphabet
    size_t i;
    srand ( time ( NULL ) );

    for ( i = 0; i < len_string; i++ )
        string[ i ] = alphabet[ rand () % len_alphabet ];
    string[len_string] = '\0';

}

int charInAlphabet( char c, char * alphabet, size_t len_alphabet )
{
    // checks if char belongs to alphabet
    int i;
    for ( i = 0; i < len_alphabet; i++ )
    {
        if ( c == alphabet[i] )
            return 1;
    }

    return 0;
}

void extractStringFromFile( const char * filename, char * string, size_t len, char * alphabet )
{

    //extracts the first len bytes from a file.
    FILE * f = fopen (filename, "r");
    int i = 0;
    char c;
    size_t len_alphabet = strlen (alphabet);

    while ( i < len )
    {
        c = (char)fgetc (f);
        if ( charInAlphabet (c, alphabet, len_alphabet))
        {
            string[i] = c;
            i++;
        }
    }
    string[len] = '\0';

    fclose (f);
}

void extractStringFromFile_convertSeparators( const char * filename, char * string, size_t len, char * alphabet, char separator )
{

    //sames as extractStringFromFile, but converts all non-alphabet separators to spaces

    FILE * f = fopen (filename, "r");
    int i = 0;
    char c;
    size_t len_alphabet = strlen (alphabet);

    while ( i < len )
    {
        c = (char)fgetc (f);
        if ( charInAlphabet (c, alphabet, len_alphabet))
            string[i] = c;
        else
        {
            string[ i ] = separator;
            while ( !charInAlphabet ((c = (char)fgetc (f)), alphabet, len_alphabet) ){}
            i++;
            string[i] = c;
        }


        i++;
    }
    string[len] = '\0';

    fclose (f);
}

void extractRandomSubstring ( size_t len_substring, char * substring, size_t len_string, char * string )
{
    //extracts a random substring from a string

    srand ( time ( NULL ) );
    long r = rand () % (len_string - len_substring);
    long offset = r;

    for ( r; (r - offset) < len_substring; r++ )
    {
        substring[r - offset] = string[r];
    }
    substring[len_substring] = '\0';

}


