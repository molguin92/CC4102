//
// Created by arachnid92 on 11-10-15.
//

#include <stdio.h>
#include <string.h>
#include "generator_main.h"
#include "generator.h"

int main ( int argc, char * argv[] )
{
    int i;
    //binary, random
    char * alphabet = "01";

    //1MB text file
    FILE * f = fopen ("binario.in", "w");
    char text[MB + 1]; //+1 for EOL symbol \0
    generateRandomString (strlen (alphabet), alphabet, MB, text);
    fprintf (f, "%s", text);
    fclose (f);

    //real DNA
    alphabet = "GCAT";
    f = fopen ("real_dna.in", "w");
    extractStringFromFile ("dna.in", text, MB, alphabet);
    fprintf (f, "%s", text);
    fclose (f);

    //synthetic DNA
    f = fopen ("synth_dna.in", "w");
    generateRandomString (strlen (alphabet), alphabet, MB, text);
    fprintf (f, "%s", text);
    fclose (f);

    //real natural language
    alphabet = "abcdefghijklmnopqrstuvwvxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    f = fopen ("real_lang.in", "w");
    extractStringFromFile_convertSeparators ("lang.in", text, MB, alphabet, ' ');
    fprintf (f, "%s", text);
    fclose (f);

    //synthetic natural language
    alphabet = "abcdefghijklmnopqrstuvwvxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    f = fopen ("synth_lang.in", "w");
    generateRandomString (strlen (alphabet), alphabet, MB, text);
    fprintf (f, "%s", text);
    fclose (f);




}
