// Created by Manuel Olguin on 01-11-15.
// main is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include <stdio.h>
#include "lin_hashing.h"
#include "ext_hashing.h"
#include "generator.h"

#define ALPHABET "GCAT"
#define ALPH_LEN 4

int main ()
{
    init_linhashing ();
    init_exthashing ();
    // Random Data
    uint32_t count = 1 << 25;
    char value[VALUE_LEN];
    for ( uint32_t i = 0; i < count; i++ )
    {
        if ( i % 10000 == 0 )
            printf ("%d\n", i);

        generateRandomString (ALPH_LEN, ALPHABET, VALUE_LEN - 1, value);
        put_value_linhashing (value);
        put_value_exthashing (value);
    }


}