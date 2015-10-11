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

int bmSearch ( char * pattern, char * text, int * comp );