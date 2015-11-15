// Created by Manuel Olguin on 01-11-15.
// main is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include <stdio.h>
#include <stdlib.h>
#include "lin_hashing.h"

int main ()
{
    fprintf (stdout, "Testing insert into hash.\n");
    init_linhashing ();
    put_value_linhashing ( "GGGGGGGGGGGGGGG" );
    put_value_linhashing ( "CCCCCCCCCCCCCCC" );
    put_value_linhashing ( "AAAAAAAAAAAAAAA" );
    put_value_linhashing ( "TTTTTTTTTTTTTTT" );
}