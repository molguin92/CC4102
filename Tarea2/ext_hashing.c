// Created by Manuel Olguin on 12-11-15.
// ext_hashing is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include "ext_hashing.h"
#include "hash.h"

void    read_Bucket ( struct Bucket * des, int k );
void    write_Bucket ( struct Bucket * src );
void    simple_split ( struct Bucket * bucket );
void    double_directory ( u_int8_t local_depth );
uint8_t bit_at_k(uint32_t hash, uint8_t k);


struct stat s = { 0 };
struct Directory * directory;

uint8_t  bit_at_k(uint32_t hash, uint8_t k)
{
    return (uint8_t)((hash >> (k - 1)) & 0x01);
}

uint32_t hashd ( char * value, uint8_t d )
{
    return hash_sequence ( value ) % ( 0x01 << d );
}

void init_hashing ()
{
    directory = (struct Directory *) malloc (sizeof(struct Directory));

    if ( stat ( "./.ext_hash", &s ) != -1 )
        system("rm -rf ./.ext_hash");

    mkdir ( "./.ext_hash", 0700 );

    directory->global_depth_d = 0;
    directory->bucket_count = 1;
    uint32_t table_n = (uint32_t)(1 << directory->global_depth_d);
    directory->table  = ( uint32_t * ) malloc ( table_n * sizeof ( uint32_t ) );
    for ( int i = 0; i < table_n; directory->table[ i++ ] = 0 );

    struct Bucket * bucket = (struct Bucket *) malloc ( sizeof(struct Bucket) );
    bucket->local_depth_k = 0;
    bucket->n_entries = 0;
    bucket->id = 0;
    write_Bucket ( bucket);
    free(bucket);
}


int search ( char * value )
{
    fprintf (stderr, "Searching for value %s\n", value);

    uint32_t hash = hashd ( value, directory->global_depth_d );

    fprintf (stderr, "Hash_d for global depth %d: %d\n", directory->global_depth_d, hash);

    struct Bucket * bucket = ( struct Bucket * ) malloc ( sizeof ( struct Bucket ) );
    read_Bucket ( bucket, directory->table[ hash ] );

    for (int i = 0; i < bucket->n_entries; i++)
        if(strcmp ((char*)bucket->values[i], value) == 0)
            return 1;

    return 0;
}

void put_value ( char * value )
{

    fprintf (stderr, "Adding value %s\n", value);

    uint32_t hash = hashd ( value, directory->global_depth_d );

    fprintf (stderr, "Hash_d for global depth %d: %d\n", directory->global_depth_d, hash);

    struct Bucket * bucket = ( struct Bucket * ) malloc ( sizeof ( struct Bucket ) );
    read_Bucket ( bucket, directory->table[ hash ] );

    if ( bucket->n_entries < MAX_ENTRIES )
    {

        fprintf (stderr, "Enough place left, adding to bucket %d.\n", bucket->id);

        // check if value already exists
        for (int i = 0; i < bucket->n_entries; i++)
            if(strcmp ((char*)bucket->values[i], value) == 0)
                return;

        strcpy ( ( char * ) bucket->values[ bucket->n_entries ], value );
        bucket->n_entries++;
        write_Bucket ( bucket );
        free ( bucket );
        return;
    }

    /*
     * Else, we need to split the bucket.
     *
     * There's two possible cases:
     *  1. local_depth + 1 <= global_depth: only need to split the block
     *  2. local_depth + 1 > global_depth: first need to double directory size, then split.
     *
     */

    fprintf (stderr, "NOT Enough place left, splitting.\n");

    if ( bucket->local_depth_k < directory->global_depth_d )
    {
        simple_split ( bucket );
        free (bucket);
        put_value ( value );
    }
    else
    {
        double_directory (bucket->local_depth_k + 1);
        simple_split (bucket);
        free (bucket);
        put_value ( value );
    }
}

void simple_split ( struct Bucket * bucket )
{

    fprintf (stderr, "Simple split.\n");

    directory->bucket_count++;
    struct Bucket * split = ( struct Bucket * ) malloc ( sizeof ( struct Bucket ) );
    split->id = directory->bucket_count - 1;
    bucket->local_depth_k++;
    split->local_depth_k = bucket->local_depth_k;
    split->n_entries = 0;

    char temp[MAX_ENTRIES][16];
    for ( int i = 0; i < bucket->n_entries; i++ )
    {
        strcpy (temp[i], (char*)bucket->values[i]);
        for ( int j = 0; j < VALUE_LEN; j++ )
            bucket->values[i][j] = 0;
    }

    bucket->n_entries=0;
    uint8_t bitk;
    int x = 0, y = 0;

    fprintf (stderr, "Distributing values...\n");
    for( int i = 0; i < MAX_ENTRIES; i++)
    {
        bitk = bit_at_k ( hash_sequence (temp[i]), bucket->local_depth_k );
        fprintf (stderr, "Value %s - Bit at Local Depth %d: %d.\n", temp[i], bucket->local_depth_k, bitk);
        if (bitk == 0)
        {
            //goes back into original bucket
            fprintf (stderr, "Goes back into bucket %d.\n", bucket->id);
            strcpy ((char*)bucket->values[x], temp[i]);
            bucket->n_entries++;
            x++;
        }
        else
        {
            //goes into split
            fprintf (stderr, "Goes into new bucket %d.\n", split->id);
            strcpy ((char*)split->values[y], temp[i]);
            split->n_entries++;
            y++;
        }
    }

    //finally, determine splits position in the directory
    if ( split-> n_entries != 0 )
    {
        uint32_t hash = hashd ( (char*)split->values[0], split->local_depth_k );
        directory->table[hash] = split->id;
        fprintf (stderr, "Table position of new bucket %d.\n", hash);
    }
    else
    {
        uint32_t hash = hashd ( (char*)bucket->values[0], bucket->local_depth_k );
        hash = hash | (0x01 << (bucket->local_depth_k - 1));
        directory->table[hash] = split->id;
        fprintf (stderr, "Table position of new bucket %d.\n", hash);
    }

    write_Bucket (split);
    write_Bucket (bucket);
    free (split);
}

void double_directory ( u_int8_t local_depth )
{
    fprintf (stderr, "Doubling directory size.\n");

    uint8_t old_d = directory->global_depth_d;
    uint32_t table_n = (uint32_t)(1 << old_d);
    uint32_t * temp_table = ( uint32_t * ) malloc ( table_n * sizeof ( uint32_t ) );

    // temporarily store the values of the table before expanding it
    for (int i = 0; i < table_n; i++)
        temp_table[i] = directory->table[i];

    while (directory->global_depth_d < local_depth )
    {
        if ( directory->global_depth_d == 0 )
        {
            directory->global_depth_d += 1;
            continue;
        }
        directory->global_depth_d = directory->global_depth_d << 1;
    }

    free (directory->table);
    directory->table = ( uint32_t * ) malloc ( (1 << directory->global_depth_d) * sizeof ( uint32_t ) );

    // copy back the old values to the bigger table
    for (int i = 0; i < table_n; i++)
        directory->table[i] = temp_table[i];

    free (temp_table);

    // map the new slots
    for ( int i = table_n; i < ( 1 << directory->global_depth_d); i++ )
    {
        directory->table[i] = directory->table[i % table_n];
    }

    fprintf (stderr, "New size: %d (Global Depth: %d)\n", (1 << directory->global_depth_d), directory->global_depth_d );
}

void read_Bucket ( struct Bucket * des, int k )
{
    char path[50];
    sprintf ( path, "./.ext_hash/%d.bucket", k );
    FILE * f = fopen ( path, "rb" );
    if ( f != NULL )
    {
        fread ( des, sizeof ( struct Bucket ), 1, f );
        fclose ( f );
    }
}

void write_Bucket ( struct Bucket * src )
{
    char path[50];
    sprintf ( path, "./.ext_hash/%d.bucket", src->id );
    FILE * f = fopen ( path, "wb" );
    if ( f != NULL )
    {
        fwrite ( src, sizeof ( struct Bucket ), 1, f );
        fclose ( f );
    }
}