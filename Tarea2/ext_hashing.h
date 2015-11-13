// Created by Manuel Olguin on 12-11-15.
// ext_hashing is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include <stdint.h>

#ifndef TAREA2_EXT_HASHING_H
#define TAREA2_EXT_HASHING_H

#endif //TAREA2_EXT_HASHING_H

struct Bucket
{
    uint8_t local_depth_k;
    uint8_t n_entries;
    uint8_t values[255][16];
};

void init_hashing();
void insert_value( char * value );