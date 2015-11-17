// Created by Manuel Olguin on 14-11-15.
// lin_hashing is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include "hash.h"

#ifndef TAREA2_LIN_HASHING_H
#define TAREA2_LIN_HASHING_H

#endif //TAREA2_LIN_HASHING_H

#define INIT_M 2
#define MAX_ENTRIES 255



struct PrimaryBucket
{
    uint32_t id;
    uint8_t n_entries;
    uint8_t overflow;
    uint8_t entries[MAX_ENTRIES][VALUE_LEN];
};

struct OverflowBucket
{
    uint8_t n_entries;
    uint8_t entries[MAX_ENTRIES][VALUE_LEN];
};


struct BucketLin
{
    struct PrimaryBucket * primary;
    struct OverflowBucket ** overflow;
};

void init_linhashing ();
void put_value_linhashing ( char * value );
int  search_linhashing ( char * value );
void pop_random_value_linhashing ( char * pop );