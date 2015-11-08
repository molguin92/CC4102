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
struct Header * Btree; // TODO: FREE THE MOTHERFUCKING MEMORY

struct Header * init_BTREE ()
{

    Btree = ( struct Header * ) malloc ( sizeof (struct Header ) );

    if ( stat ( "./.btree", &st ) == -1 )
    {
        mkdir ( "./.btree", 0700 );
        Btree->n_nodes = 1;
        Btree->root = 1;
        FILE * f = fopen ( ".btree/header", "wb" );
        if ( f != NULL )
        {
            fwrite ( Btree, sizeof ( struct Header ), 1, f );
            fclose ( f );
        }

        struct Node * root = ( struct Node * ) malloc ( sizeof ( struct Node ) );
        root->n_entries = 0;
        root->node_k = 1;
        write_node ( root, root->node_k );
        free ( root );
    }
    else
    {
        FILE * f = fopen ( ".btree/header", "rb" );
        if ( f != NULL )
        {
            fread ( Btree, sizeof ( struct Header ), 1, f );
            fclose ( f );
        }
    }

}


void split_node ( struct Node * src, struct Node * sibling, char ** median )
{

    uint32_t i;
    char null[16] = {0};
    for ( i = B/2 + 1; i < B; i++ )
    {
        // move upper half of entries to new node
        strcpy ((char *)sibling->entries[i - (B/2 + 1)], (char *)src->entries[i]);
        strcpy ((char *) src->entries[i], (char *)null);

        // move references as well
        sibling->subtrees[i - (B/2 + 1)] = src->subtrees[i];
        src->subtrees[i] = 0;
    }

    // move last reference
    sibling->subtrees[B/2 - 1] = src->subtrees[B];
    src->subtrees[B] = 0;

    strcpy (*median, (char *)src->entries[B/2]);
    strcpy ( (char *) src->entries[B/2], (char *)null);

    src->n_entries = B/2;
    sibling->n_entries = B/2 - 1;
}

int insert_value_at_leaf ( char * value, int node_k, int parent_k )
{

    /* if handed the header of the tree, give the value to the root */

    if ( node_k < 0 )
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
        return insert_value_at_leaf ( value, node_k, -1 );
    }


    /* read data from node file */
    struct Node * node = ( struct Node * ) malloc ( sizeof ( struct Node ) );
    read_node ( node, node_k );
    uint32_t subtree_root;

    /*
     * check if node is leaf.
     * if not, hand the value to the correct subtree.
     */

    if ( node->subtrees[0] != 0 ) //not a leaf
    {
        subtree_root = find_subtree (value, node);
        return insert_value_at_leaf ( value, subtree_root, node_k );
    }

    /*
     * if node has less than B values, insert value in this node
     * Keep node ordered!
     */
    if ( node->n_entries < B )
        insert_ordered ( value, node );

    if ( node->n_entries == B ) // need to split
    {
        struct Node * sibling = ( struct Node * ) malloc ( sizeof ( struct Node ) );
        char * median[16] = {0};

        split_node (node, sibling, median);
        Btree->n_nodes++;
        sibling->node_k = Btree->n_nodes;
        write_node (sibling, sibling->node_k);

        insert_split (parent_k, *median, node_k, sibling->node_k);

        free(sibling);
        free (node);
        return node_k;
    }
    else
    {
        write_node ( node, node_k );
        free ( node );
        return node_k;
    }
}

int insert_ordered ( char * new, struct Node (  * des) )
{
    /* inserts the value "new" into the node,
     * while maintaining the order of the values.
     * Returns the index of where the value was inserted. */

    uint32_t i, j, delta;
    char     temp[B][VALUE_SIZE] = { { 0 } };
    int      comp;
    for ( i = 0; i < des->n_entries; i++ )
    {
        comp = strcmp ( new, ( char * ) des->entries[ i ] );
        if ( comp == 0 ) // entry already exists, do nothing.
            return i;
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
    return i;

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

void insert_split ( int parent_k, char * value, int left, int right )
{

    // inserts a value from a split node into its parent.

    /* read data from node file */
    struct Node * node = ( struct Node * ) malloc ( sizeof ( struct Node ) );
    read_node ( node, parent_k );

    if ( node->n_entries < B )
    {
        // enough space, just insert
    }

}
