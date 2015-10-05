//
// Created by arachnid92 on 04-10-15.
//

#include <stddef.h>
#include <limits.h>

#ifndef TAREA1_BOYERMOORE_H
#define TAREA1_BOYERMOORE_H

#endif //TAREA1_BOYERMOORE_H

void badCharTable (
        char * pattern,
        size_t len_patt,
        int * table
                  );

void goodSuffix1 (
                 char * pattern,
                 size_t len_patt,
                 int * table,
                 int * aux_table
                 );

void goodSuffix2 (
                 char * pattern,
                 size_t len_patt,
                 int * table,
                 int * aux_table
                 );

void bmPreprocess ( char * pattern, size_t len_patt );

int bmSearch( char * pattern, char * text );