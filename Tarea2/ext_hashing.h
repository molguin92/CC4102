// Created by Manuel Olguin on 12-11-15.
// ext_hashing is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include <stdint.h>
#include "hash.h"

#ifndef TAREA2_EXT_HASHING_H
#define TAREA2_EXT_HASHING_H

#endif //TAREA2_EXT_HASHING_H

#define MAX_ENTRIES 255

struct BucketExt
{
    uint32_t id;
    uint8_t local_depth_k;
    uint8_t n_entries;
    uint8_t values[MAX_ENTRIES][VALUE_LEN];
};

struct Directory
{
    uint8_t global_depth_d;
    uint32_t bucket_count;
    uint32_t n_buckets;
    uint32_t * table;
};


void     init_exthashing ();
int      put_value_exthashing ( char * value );
int      search_exthashing ( char * value );
void     pop_random_value_exthashing ( char * pop );
void     get_read_writes_exthashing ( uint32_t * reads, uint32_t * writes );
uint32_t get_blocks_exthashing ();