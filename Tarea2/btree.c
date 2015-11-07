// Created by Manuel Olguin on 03-11-15.
// btree is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

// Page size: 4096 bytes (4KB)
// Pointer size: 8 bytes (64 bit arch)
// B-trees: B/2 minimum offspring, max B offspring
// 15 (16 with null delimiter) bytes per value
// B = 256, B/2 = 128

/*
 * Structure of a Node:
 * Size: 4096 bytes (1 IO page)
 * B = 255 (16 bytes each), starting from byte 16.
 * First 16 bytes (0 - 15) reserved for metadata:
 *      Bytes [0, 1]: Number of subtrees of present node (uint16_t)
 *      Bytes [2, 5]: Node ID (uint32_t)
 */

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "btree.h"

struct stat st = { 0 };

void init_BTREE ()
{
    if ( stat ( "./.btree", &st ) == -1 )
    {
        mkdir ( "./.btree", 0700 );
    }
    else
    {
        system ( "rm -rf ./.btree" );
        mkdir ( "./.btree", 0700 );
    }

    struct Node * root = ( struct Node * ) malloc ( sizeof ( struct Node ) );
    write_node ( root, 0 );
    free ( root );
}


int insert_value ( char * value, int node_k )
{

    /* read data from node file */
    struct Node * node = ( struct Node * ) malloc ( sizeof ( struct Node ) );
    read_node ( node, node_k );

    /*
     * if node has less than B values, insert value in this node
     * Keep node ordered!
     */
    if ( node->n_entries < B )
    {
        insert_ordered ( value, node );
        write_node ( node, node_k );
        free ( node );
        return node_k;
    }

    /* else,we need to split this sucker */


    return 0;
}

void insert_ordered ( char * new, struct Node (  * des) )
{
    /* inserts the value "new" into the node,
     * while maintaining the order of the values. */

    uint32_t i, j, delta;
    char     temp[B][VALUE_SIZE] = { { 0 } };
    int      comp;
    for ( i = 0; i < des->n_entries; i++ )
    {
        comp = strcmp ( new, ( char * ) des->entries[ i ] );
        if ( comp < 0 ) // new < entry
            break;
    }

    delta   = des->n_entries - i;
    for ( j = 0; j < delta; j++ )
    {
        strcpy ( ( char * ) temp[ j ], ( char * ) des->entries[ i + j ] );
    }

    strcpy ( ( char * ) des->entries[ i ], new );

    for ( j = 0; j < delta; j++ )
    {
        strcpy ( ( char * ) des->entries[ i + j + 1 ], ( char * ) temp[ j ] );
    }

    des->n_entries++;

}


void read_node ( struct Node * des, int node_k )
{
    char path[5];
    sprintf ( path, "./.btree/%d.node", node_k );
    FILE * f = fopen ( path, "rb" );
    if ( f != NULL )
    {
        fread ( des, sizeof ( struct Node ), 1, f );
        fclose ( f );
    }
}

void write_node ( struct Node * src, int node_k )
{
    char path[5];
    sprintf ( path, "./.btree/%d.node", node_k );
    FILE * f = fopen ( path, "wb" );
    if ( f != NULL )
    {
        fwrite ( src, sizeof ( struct Node ), 1, f );
        fclose ( f );
    }
}
