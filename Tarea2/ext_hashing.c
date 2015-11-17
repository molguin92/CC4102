// Created by Manuel Olguin on 12-11-15.
// ext_hashing is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "ext_hashing.h"

void    read_Bucket ( struct BucketExt * des, int k );
void    write_Bucket ( struct BucketExt * src );
void    delete_Bucket ( struct BucketExt * src );
void    simple_split ( struct BucketExt * bucket );
void    double_directory ( u_int8_t local_depth );
uint8_t bit_at_k(uint32_t hash, uint8_t k);
void    collapse_buckets ( uint32_t b_index, struct BucketExt * bucket );


struct stat s = { 0 };
struct Directory * directory;

uint32_t t_reads  = 0;
uint32_t t_writes = 0;

uint8_t  bit_at_k(uint32_t hash, uint8_t k)
{
    return (uint8_t)((hash >> (k - 1)) & 0x01);
}

uint32_t hashd ( char * value, uint8_t d )
{
    return hash_sequence ( value ) % ( 0x01 << d );
}

void init_exthashing ()
{
    directory = (struct Directory *) malloc (sizeof(struct Directory));

    if ( stat ( "./.ext_hash", &s ) != -1 )
        system("rm -rf ./.ext_hash");

    mkdir ( "./.ext_hash", 0700 );

    directory->global_depth_d = 0;
    directory->bucket_count = 1;
    directory->n_buckets = 1;
    uint32_t table_n = (uint32_t)(1 << directory->global_depth_d);
    directory->table  = ( uint32_t * ) malloc ( table_n * sizeof ( uint32_t ) );
    for ( int i = 0; i < table_n; directory->table[ i++ ] = 0 );

    struct BucketExt * bucket = (struct BucketExt *) malloc ( sizeof(struct BucketExt ) );
    bucket->local_depth_k = 0;
    bucket->n_entries = 0;
    bucket->id = 0;
    write_Bucket ( bucket);
    free(bucket);
}


int search_exthashing ( char * value )
{

    uint32_t hash = hashd ( value, directory->global_depth_d );

    struct BucketExt * bucket = ( struct BucketExt * ) malloc ( sizeof ( struct BucketExt ) );
    read_Bucket ( bucket, directory->table[ hash ] );

    for (int i = 0; i < bucket->n_entries; i++)
        if(strcmp ((char*)bucket->values[i], value) == 0)
            return 1;

    return 0;
}


void pop_random_value_exthashing ( char * pop )
{
    srand ( time(NULL) );

    struct BucketExt * bucket = ( struct BucketExt * ) malloc ( sizeof ( struct BucketExt ) );
    uint32_t b_index, index;
    bucket->n_entries = 0;

    while (bucket->n_entries == 0)
    {
        b_index = ( uint32_t ) ( rand () / ( RAND_MAX / ( ( 1 << (directory->global_depth_d - 1)) + 1) ));
        read_Bucket ( bucket, directory->table[ b_index ] ); // random bucket
    }

    index = ( uint32_t ) ( rand () / ( RAND_MAX / ( bucket->n_entries + 1) )); // random value
    strcpy (pop, (char*)bucket->values[index]);
    strcpy ((char*)bucket->values[index], (char*)bucket->values[bucket->n_entries - 1]);
    bucket->n_entries--;

    for ( int i = 0; i < VALUE_LEN; i++ )
        bucket->values[bucket->n_entries][i] = 0;

    write_Bucket (bucket);

    collapse_buckets ( b_index, bucket ); // collapse two buckets into one if possible.
}

int put_value_exthashing ( char * value )
{

    //printf ( "Putting value %s in hash.\n", value );
    uint32_t hash = hashd ( value, directory->global_depth_d );

    struct BucketExt * bucket = ( struct BucketExt * ) malloc ( sizeof ( struct BucketExt ) );
    read_Bucket ( bucket, directory->table[ hash ] );

    if ( bucket->n_entries < MAX_ENTRIES )
    {

        // check if value already exists
        for (int i = 0; i < bucket->n_entries; i++)
            if(strcmp ((char*)bucket->values[i], value) == 0)
                return 0;

        strcpy ( ( char * ) bucket->values[ bucket->n_entries ], value );
        bucket->n_entries++;
        write_Bucket ( bucket );
        free ( bucket );
        return 1;
    }

    /*
     * Else, we need to split the bucket.
     *
     * There's two possible cases:
     *  1. local_depth + 1 <= global_depth: only need to split the block
     *  2. local_depth + 1 > global_depth: first need to double directory size, then split.
     *
     */


    if ( bucket->local_depth_k < directory->global_depth_d )
    {
        simple_split ( bucket );
        free (bucket);
        return put_value_exthashing ( value );
    }
    else
    {
        double_directory (bucket->local_depth_k + 1);
        simple_split (bucket);
        free (bucket);
        return put_value_exthashing ( value );
    }
}

void simple_split ( struct BucketExt * bucket )
{

    directory->bucket_count++;
    directory->n_buckets++;
    struct BucketExt * split = ( struct BucketExt * ) malloc ( sizeof ( struct BucketExt ) );
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

    for( int i = 0; i < MAX_ENTRIES; i++)
    {
        bitk = bit_at_k ( hash_sequence (temp[i]), bucket->local_depth_k );
        if (bitk == 0)
        {
            //goes back into original bucket
            strcpy ((char*)bucket->values[x], temp[i]);
            bucket->n_entries++;
            x++;
        }
        else
        {
            //goes into split
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
    }
    else
    {
        uint32_t hash = hashd ( (char*)bucket->values[0], bucket->local_depth_k );
        hash = hash | (0x01 << (bucket->local_depth_k - 1));
        directory->table[hash] = split->id;
    }

    write_Bucket (split);
    write_Bucket (bucket);
    free (split);
}

void double_directory ( u_int8_t local_depth )
{

    while (directory->global_depth_d < local_depth )
    {

        uint8_t old_d = directory->global_depth_d;
        uint32_t table_n = (uint32_t)(1 << old_d);

        if ( directory->global_depth_d == 0 )
            directory->global_depth_d += 1;
        else
            directory->global_depth_d = directory->global_depth_d << 1;

        uint32_t * new_table = ( uint32_t * ) malloc ( ( 1 << directory->global_depth_d) * sizeof ( uint32_t ) );

        // store the values of the table
        memcpy ( new_table, directory->table, table_n * sizeof (uint32_t) );
        memcpy ( &new_table[table_n], directory->table, table_n * sizeof (uint32_t) );

        free (directory->table);
        directory->table = new_table;
    }
}

void read_Bucket ( struct BucketExt * des, int k )
{
    t_reads++;
    char path[50];
    sprintf ( path, "./.ext_hash/%d.bucket", k );
    FILE * f = fopen ( path, "rb" );
    if ( f != NULL )
    {
        fread ( des, sizeof ( struct BucketExt ), 1, f );
        fclose ( f );
    }
}

void write_Bucket ( struct BucketExt * src )
{
    t_writes++;
    char path[50];
    sprintf ( path, "./.ext_hash/%d.bucket", src->id );
    FILE * f = fopen ( path, "wb" );
    if ( f != NULL )
    {
        fwrite ( src, sizeof ( struct BucketExt ), 1, f );
        fclose ( f );
    }
}

void delete_Bucket ( struct BucketExt * src )
{
    t_writes++;
    char path[50];
    sprintf ( path, "./.ext_hash/%d.bucket", src->id );
    unlink (path);
}

void collapse_buckets ( uint32_t b_index, struct BucketExt * bucket )
{
    // open "sister" bucket:
    uint8_t bitk = bit_at_k (b_index, bucket->local_depth_k);
    struct BucketExt * sister = ( struct BucketExt * ) malloc ( sizeof ( struct BucketExt ) );

    if ( bitk == 0 )
    {
        b_index = b_index | (0x01 << (bucket->local_depth_k - 1));

        if ( directory->table[b_index] == bucket->id )
            return; // no sister bucket

        read_Bucket (sister, directory->table[b_index]);
    }
    else
    {
        b_index = b_index / 2;

        if ( directory->table[b_index] == bucket->id )
            return; // no sister bucket

        read_Bucket (sister, directory->table[b_index]);
        struct BucketExt * temp = sister;
        sister = bucket;
        bucket = temp;
    }



    if ( (sister->n_entries + bucket->n_entries) > MAX_ENTRIES )
        return;


    for ( int i = 0; i < sister->n_entries; i ++ )
    {
        strcpy ( (char *)bucket->values[bucket->n_entries], (char *)sister->values[i]);
        bucket->n_entries++;
    }

    bucket->local_depth_k--;
    write_Bucket (bucket);

    directory->table[b_index] = bucket->id;
    directory->n_buckets--;
    free (bucket);
    delete_Bucket (sister);
    free (sister);
}

void get_read_writes_exthashing ( uint32_t * reads, uint32_t * writes )
{
    *reads = t_reads;
    *writes = t_writes;
}


uint32_t get_blocks_exthashing ()
{
    return directory->n_buckets;
}
