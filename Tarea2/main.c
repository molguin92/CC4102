// Created by Manuel Olguin on 01-11-15.
// main is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "ext_hashing.h"

int main ()
{
    fprintf (stdout, "Testing insert into hash.\n");
    init_hashing ();
    put_value ( "GGGGGGGGGGGGGGG" );
    put_value ( "CCCCCCCCCCCCCCC" );
    put_value ( "AAAAAAAAAAAAAAA" );
    put_value ( "TTTTTTTTTTTTTTT" );

    int a = search ("AAAAAAAAAAAAAAA");
    if ( a == 1 )
        printf ("A was found.");
}