// Created by Manuel Olguin on 03-11-15.
// btree is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

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

    struct Header * header = ( struct Header * ) malloc ( sizeof (struct Header ) );
    header->n_nodes = 1;
    header->root = 0;
    FILE * f = fopen ( ".btree/header", "wb" );
    if ( f != NULL )
    {
        fwrite ( header, sizeof ( struct Header ), 1, f );
        fclose ( f );
    }
    free(header);

    struct Node * root = ( struct Node * ) malloc ( sizeof ( struct Node ) );
    write_node ( root, 0 );
    free ( root );
}


int insert_value_at_leaf ( char * value, int node_k )
{

    /* if handed the header of the tree, give the value to the root */

    if ( node_k == -1 )
    {
        struct Header * h = ( struct Header * ) malloc ( sizeof (struct Header ) );
        FILE * f = fopen ( "./.btree/header", "rb" );
        if ( f != NULL )
        {
            fread ( h, sizeof ( struct Header ), 1, f );
            fclose ( f );
        }
        node_k = h->root;
        free(h);
        return insert_value_at_leaf (value, node_k);
    }


    /* read data from node file */
    struct Node * node = ( struct Node * ) malloc ( sizeof ( struct Node ) );
    read_node ( node, node_k );
    uint32_t subtree_root;

    /* check if a split is needed */
    


    /*
     * check if node is leaf.
     * if not, hand the value to the correct subtree.
     */

    if ( node-> n_subtrees != 0 ) //not a leaf
    {
        subtree_root = find_subtree (value, node);
        return insert_value_at_leaf (value, subtree_root);
    }

    /*
     * if node has less than B + 1 values, insert value in this node
     * Keep node ordered!
     */
    if ( node->n_entries < B + 1)
    {
        insert_ordered ( value, node );
        write_node ( node, node_k );
        free ( node );
        return node_k;
    }


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
    char path[50];
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
    char path[50];
    sprintf ( path, "./.btree/%d.node", node_k );
    FILE * f = fopen ( path, "wb" );
    if ( f != NULL )
    {
        fwrite ( src, sizeof ( struct Node ), 1, f );
        fclose ( f );
    }
}

uint32_t find_subtree ( char * value, struct Node * node )
{

    uint32_t i;

    for ( i = 0; i < node->n_entries; i++ )
    {
        if ( strcmp (value, (char *) node->entries[i] ) < 0 )
            break;
    }

    return node->subtrees[i];
}
