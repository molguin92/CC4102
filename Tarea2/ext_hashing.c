// Created by Manuel Olguin on 12-11-15.
// ext_hashing is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include "ext_hashing.h"
#include "hash.h"

void     read_Bucket ( struct Bucket * des, int k );
void     write_Bucket ( struct Bucket * src, int k );
uint32_t simple_split ( struct Bucket * bucket, struct Bucket * split, uint32_t hash_i );
void     double_directory ( u_int8_t local_depth );

struct
{
    uint8_t global_depth_d;
    uint32_t bucket_count;
    uint32_t * table;
} directory;

struct stat s = { 0 };

uint32_t hashd ( char * value, uint8_t d )
{
    return hash_sequence ( value ) % ( 0x01 << d );
}

void init_hashing ()
{

    if ( stat ( "./.ext_hash", &s ) == -1 )
    {
        mkdir ( "./.ext_hash", 0700 );
        directory.global_depth_d = 8;
        directory.bucket_count = 1;
        uint32_t table_n = (uint32_t)(1 << directory.global_depth_d);
        directory.table  = ( uint32_t * ) malloc ( table_n * sizeof ( uint32_t ) );
        for ( int i = 0; i < table_n; directory.table[ i++ ] = directory.bucket_count );

        FILE * f = fopen ("./.ext_hash/directory", "wb");
        if ( f != NULL )
        {
            fwrite ( &directory, sizeof ( directory ), 1, f );
            fclose ( f );
        }

        struct Bucket * bucket = (struct Bucket *) malloc ( sizeof(struct Bucket) );
        bucket->local_depth_k = 0;
        bucket->n_entries = 0;
        f = fopen ("./.ext_hash/1.bucket", "wb");
        {
            fwrite ( bucket, sizeof ( struct Bucket ), 1, f );
            fclose ( f );
        }
        free(bucket);
    }
    else
    {
        FILE * f = fopen ( ".btree/directory", "rb" );
        if ( f != NULL )
        {
            fread ( &directory, sizeof ( directory ), 1, f );
            fclose ( f );
        }
    }
}

void insert_value( char * value )
{

    uint32_t hash = hashd ( value, directory.global_depth_d );
    struct Bucket * bucket = ( struct Bucket * ) malloc ( sizeof ( struct Bucket ) );
    read_Bucket ( bucket, directory.table[ hash ] );

    if ( bucket->n_entries < 255 )
    {
        strcpy ( ( char * ) bucket->values[ bucket->n_entries ], value );
        bucket->n_entries++;
        write_Bucket ( bucket, directory.table[ hash ] );
        free ( bucket );
        return;
    }

    /*
     * Else, we need to split the bucket.
     *
     * There's two possible cases:
     *  1. local_depth + 1 <= global_depth: only need to split the block
     *  2. local_depth + 1 > global_depth: first need to double directory size, then split.
     */

    struct Bucket * split = ( struct Bucket * ) malloc ( sizeof ( struct Bucket ) );
    uint32_t split_pos;
    while ( bucket->n_entries == 255 )
    {
        bucket->local_depth_k++;
        if ( bucket->local_depth_k <= directory.global_depth_d )
        {
            split_pos = simple_split ( bucket, split, hash );

            if ( split->n_entries == 255 ) {
                write_Bucket (bucket, directory.table[hash]);
                bucket = split;
            }
            else
            {
                write_Bucket (split, split_pos);
            }
        }
        else
        {
            double_directory ( bucket->local_depth_k );
            split_pos = simple_split ( bucket, split, hash );

            if ( split->n_entries == 255 ) {
                write_Bucket (bucket, directory.table[hash]);
                bucket = split;
            }
            else
            {
                write_Bucket (split, split_pos);
            }
        }

    }

}

uint32_t simple_split( struct Bucket * bucket, struct Bucket * split, uint32_t hash_i )
{

    directory.bucket_count++;
    char temp[255][16] = {{0}};
    const char * null_value = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    for ( int i = 0; i < 255; i++)
    {
        strcpy ((char *)temp[i], (char *)bucket->values[i]);
        strcpy ((char *)bucket->values[i], null_value);
    }

    // redistribute
    bucket->n_entries = 0;
    uint8_t k = bucket->local_depth_k;
    uint32_t x = 0, y = 0;
    for ( int i = 0; i < 255; i++)
    {
        uint32_t h = hash_sequence (temp[i]);
        uint32_t bit = (h >> (k + 1)) & 0x01;

        switch (bit)
        {
            case 0:
                strcpy ((char *)bucket->values[x], (char *)temp[i]);
                x++;
                bucket->n_entries++;
                break;
            case 1:
                strcpy ((char *)split->values[y], (char *)temp[i]);
                y++;
                split->n_entries++;
                break;
            default:
                continue;
        }
    }

    bucket->local_depth_k++;
    split->local_depth_k = bucket->local_depth_k;
    hash_i = hash_i | ( 1 << (bucket->local_depth_k - 1));
    directory.table[hash_i] = directory.bucket_count;
    return directory.bucket_count;
}

void double_directory ( u_int8_t local_depth )
{
    uint8_t old_d = directory.global_depth_d;
    uint32_t table_n = (uint32_t)(1 << old_d);
    uint32_t * temp_table = ( uint32_t * ) malloc ( table_n * sizeof ( uint32_t ) );

    // temporarily store the values of the table before expanding it
    for (int i = 0; i < table_n; i++)
        temp_table[i] = directory.table[i];

    while (directory.global_depth_d < local_depth )
    {
        directory.global_depth_d = directory.global_depth_d << 1;
    }

    free (directory.table);
    directory.table = ( uint32_t * ) malloc ( (1 << directory.global_depth_d) * sizeof ( uint32_t ) );

    // copy back the old values to the bigger table
    for (int i = 0; i < table_n; i++)
        directory.table[i] = temp_table[i];

    free (temp_table);

    // map the new slots
    for ( int i = table_n; i < ( 1 << directory.global_depth_d); i++ )
    {
        directory.table[i] = directory.table[i % table_n];
    }
}

void read_Bucket ( struct Bucket * des, int k )
{
    char path[50];
    sprintf ( path, "./.btree/%d.bucket", k );
    FILE * f = fopen ( path, "rb" );
    if ( f != NULL )
    {
        fread ( des, sizeof ( struct Bucket ), 1, f );
        fclose ( f );
    }
}

void write_Bucket ( struct Bucket * src, int k )
{
    char path[50];
    sprintf ( path, "./.btree/%d.bucket", k );
    FILE * f = fopen ( path, "wb" );
    if ( f != NULL )
    {
        fwrite ( src, sizeof ( struct Bucket ), 1, f );
        fclose ( f );
    }
}