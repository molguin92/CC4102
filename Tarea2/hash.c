// Created by Manuel Olguin on 12-11-15.
// hash is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include "hash.h"

uint32_t convert_DNAChar(char c)
{
    uint32_t ret = 0;
    switch (c)
    {
        case ('G'):
            ret = 0x00;
            break;
        case ('C'):
            ret = 0x01;
            break;
        case ('A'):
            ret = 0x02;
            break;
        case ('T'):
            ret = 0x03;
            break;
        default:
            break;
    }

    return ret;
}

uint32_t hash_sequence ( char * sequence )
{
    uint32_t ret = 0x00000000;
    uint8_t i;

    for ( i = 0; i < VALUE_LEN - 1; i++)
    {
        uint32_t c = convert_DNAChar (sequence[i]);
        c = c << (( VALUE_LEN - 2 - i ) * 2);
        ret += c;
    }

    return ret;
}
