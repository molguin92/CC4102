// Created by Manuel Olguin on 03-11-15.
// btree is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include <stddef.h>
#include <stdint.h>

#ifndef TAREA2_BTREE_H
#define TAREA2_BTREE_H

#endif //TAREA2_BTREE_H

/*
 * Node:
 *
 * 205 addresses of subtrees (nodes), each of 4 bytes:  820 bytes
 * 204 values stored in the node, each of 16 bytes:    3264 bytes
 * 1 4-byte value to store number of entries:             4 bytes
 * 1 4-byte value to store ID of the node:                4 bytes
 * Total size of a node:                               4092 bytes
 * Page size:                                          4096 bytes
 */

#define PAGE_SIZE 4096
#define VALUE_SIZE 16
#define B 204

struct Node
{
    uint32_t node_k;
    uint32_t n_entries;
    uint32_t subtrees[205];
    uint8_t  entries[B][VALUE_SIZE];
};

struct Header
{
    uint32_t root;
    uint32_t n_nodes;
};


struct Header * init_BTREE ();

int insert_value_at_leaf ( char * value, int node_k, int parent_k );

int insert_ordered ( char * new, struct Node * des );

void read_node ( struct Node * des, int node_k );

void write_node ( struct Node * src, int node_k );

uint32_t find_subtree ( char * value, struct Node * node );

void split_node ( struct Node * src, struct Node * sibling, char ** median );

void insert_split( int parent_k, char * value, int left, int right );

void close_tree();