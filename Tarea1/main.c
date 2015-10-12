//
// Created by arachnid92 on 23-09-15.
//

#include <stdio.h>
#include <time.h>
#include "brute_force.h"
#include "kmp.h"
#include "boyermoore.h"
#include "generator.h"
#include "main.h"

int main ( char argc, char * argv[] )
{

    //Binary:
    FILE * f  = fopen ( "binary.in", "r" );
    char text[MB + 1];
    int  reps = 0;
    int  i;
    char pattern[128 + 1];
    char * alphabet = "01";
    int     comp;
    int     count;
    clock_t t_init;
    clock_t t_fin;
    double  delta_t;

    for ( i = 0; i < MB + 1; i++ )
        text[ i ] = ( char ) fgetc ( f );

    fclose ( f );

    printf ( "Working on: Binary alphabet.\n" );

    f = fopen ( "results_binary.csv", "w" );
    fprintf (
            f,
            "pattern_length,pattern,count_bruteforce,comp_bruteforce,t_bruteforce,count_kmp,cmp_kmp,t_kmp,count_bm,cmp_bm,t_bm\n"
            );
    for ( i = 2; i <= MAX_PATTERN; i = 2 * i ) // i = 2, 4, 8, ..., 2^7 = 128
    {
        printf ( "Searching for patterns of length %d.\n", i );
        for ( reps = 0; reps < EXP_COUNT; reps++ ) // repetir busqueda 150 veces para asegurar error de 5%
        {
            generateRandomString ( 2, alphabet, ( size_t ) i, pattern );
            fprintf ( f, "%d,%s,", i, pattern );

            //brute force
            t_init  = clock ();
            count   = brute_force ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f,", count, comp, delta_t );

            //KMP
            t_init  = clock ();
            count   = KMPSearch ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f,", count, comp, delta_t );

            //Boyer-Moore
            t_init  = clock ();
            count   = bmSearch ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f\n", count, comp, delta_t );
        }

    }
    fclose ( f );

    //Real DNA
    f       = fopen ( "real_dna.in", "r" );
    for ( i = 0; i < MB + 1; i++ )
        text[ i ] = ( char ) fgetc ( f );
    fclose ( f );

    printf ( "Working on: Real DNA.\n" );

    f = fopen ( "results_real_dna.csv", "w" );
    fprintf (
            f,
            "pattern_length,pattern,count_bruteforce,comp_bruteforce,t_bruteforce,count_kmp,cmp_kmp,t_kmp,count_bm,cmp_bm,t_bm\n"
            );
    for ( i = 2; i <= MAX_PATTERN; i = 2 * i ) // i = 2, 4, 8, ..., 2^7 = 128
    {
        printf ( "Searching for patterns of length %d.\n", i );
        for ( reps = 0; reps < EXP_COUNT; reps++ ) // repetir busqueda 150 veces para asegurar error de 5%
        {
            extractRandomSubstring ( ( size_t ) i, pattern, MB + 1, text );
            fprintf ( f, "%d,%s,", i, pattern );

            //brute force
            t_init  = clock ();
            count   = brute_force ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f,", count, comp, delta_t );

            //KMP
            t_init  = clock ();
            count   = KMPSearch ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f,", count, comp, delta_t );

            //Boyer-Moore
            t_init  = clock ();
            count   = bmSearch ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f\n", count, comp, delta_t );
        }

    }
    fclose ( f );

    //synthetic DNA
    f       = fopen ( "synth_dna.in", "r" );
    for ( i = 0; i < MB + 1; i++ )
        text[ i ] = ( char ) fgetc ( f );
    fclose ( f );

    printf ( "Working on: Synthetic DNA.\n" );
    f = fopen ( "results_synth_dna.csv", "w" );
    fprintf (
            f,
            "pattern_length,pattern,count_bruteforce,comp_bruteforce,t_bruteforce,count_kmp,cmp_kmp,t_kmp,count_bm,cmp_bm,t_bm\n"
            );
    for ( i = 2; i <= MAX_PATTERN; i = 2 * i ) // i = 2, 4, 8, ..., 2^7 = 128
    {
        printf ( "Searching for patterns of length %d.\n", i );
        for ( reps = 0; reps < EXP_COUNT; reps++ ) // repetir busqueda 150 veces para asegurar error de 5%
        {
            extractRandomSubstring ( ( size_t ) i, pattern, MB + 1, text );
            fprintf ( f, "%d,%s,", i, pattern );

            //brute force
            t_init  = clock ();
            count   = brute_force ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f,", count, comp, delta_t );

            //KMP
            t_init  = clock ();
            count   = KMPSearch ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f,", count, comp, delta_t );

            //Boyer-Moore
            t_init  = clock ();
            count   = bmSearch ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f\n", count, comp, delta_t );
        }

    }
    fclose ( f );

    //Real Language
    f       = fopen ( "real_lang.in", "r" );
    for ( i = 0; i < MB + 1; i++ )
        text[ i ] = ( char ) fgetc ( f );
    fclose ( f );

    printf ( "Working on: Real Language.\n" );
    f = fopen ( "results_real_lang.csv", "w" );
    fprintf (
            f,
            "pattern_length,pattern,count_bruteforce,comp_bruteforce,t_bruteforce,count_kmp,cmp_kmp,t_kmp,count_bm,cmp_bm,t_bm\n"
            );
    for ( i = 2; i <= MAX_PATTERN; i = 2 * i ) // i = 2, 4, 8, ..., 2^7 = 128
    {
        printf ( "Searching for patterns of length %d.\n", i );
        for ( reps = 0; reps < EXP_COUNT; reps++ ) // repetir busqueda 150 veces para asegurar error de 5%
        {
            extractRandomSubstring ( ( size_t ) i, pattern, MB + 1, text );
            fprintf ( f, "%d,%s,", i, pattern );

            //brute force
            t_init  = clock ();
            count   = brute_force ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f,", count, comp, delta_t );

            //KMP
            t_init  = clock ();
            count   = KMPSearch ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f,", count, comp, delta_t );

            //Boyer-Moore
            t_init  = clock ();
            count   = bmSearch ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f\n", count, comp, delta_t );
        }

    }
    fclose ( f );


    //synthetic Language
    f       = fopen ( "synth_lang.in", "r" );
    for ( i = 0; i < MB + 1; i++ )
        text[ i ] = ( char ) fgetc ( f );
    fclose ( f );

    printf ( "Working on: Synthetic Language.\n" );
    f = fopen ( "results_synth_lang.csv", "w" );
    fprintf (
            f,
            "pattern_length,pattern,count_bruteforce,comp_bruteforce,t_bruteforce,count_kmp,cmp_kmp,t_kmp,count_bm,cmp_bm,t_bm\n"
            );
    for ( i = 2; i <= MAX_PATTERN; i = 2 * i ) // i = 2, 4, 8, ..., 2^7 = 128
    {
        printf ( "Searching for patterns of length %d.\n", i );
        for ( reps = 0; reps < EXP_COUNT; reps++ ) // repetir busqueda 150 veces para asegurar error de 5%
        {
            extractRandomSubstring ( ( size_t ) i, pattern, MB + 1, text );
            fprintf ( f, "%d,%s,", i, pattern );

            //brute force
            t_init  = clock ();
            count   = brute_force ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f,", count, comp, delta_t );

            //KMP
            t_init  = clock ();
            count   = KMPSearch ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f,", count, comp, delta_t );

            //Boyer-Moore
            t_init  = clock ();
            count   = bmSearch ( pattern, text, &comp );
            t_fin   = clock ();
            delta_t = ( double ) ( t_fin - t_init ) / CLOCKS_PER_SEC;
            fprintf ( f, "%d,%d,%f\n", count, comp, delta_t );
        }

    }
    fclose ( f );

    printf ( "All done!\n" );

    return 0;

}
