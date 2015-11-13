// Created by Manuel Olguin on 01-11-15.
// main is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

int main ()
{
    fprintf ( stdout, "%d\n", ( int ) sizeof ( struct Node ) );
    init_BTREE ();
    insert_value_at_leaf ( "wolololz", 1, 0 );

    struct Node * node = ( struct Node * ) malloc ( sizeof ( struct Node ) );
    FILE        * f    = fopen ( "./.btree/1.node", "rb" );
    if ( f != NULL )
    {
        fread ( node, sizeof ( struct Node ), 1, f );
        fprintf ( stdout, "%d\n", node->n_entries );
        fprintf ( stdout, "%s\n", node->entries[ 0 ] );
        fprintf ( stdout, "%s\n", node->entries[ 1 ] );
        fclose ( f );
    }
}