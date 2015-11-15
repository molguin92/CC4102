// Created by Manuel Olguin on 14-11-15.
// lin_hashing is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "lin_hashing.h"
#include "hash.h"


void     read_BucketLin ( struct BucketLin * des, int k );

void     write_BucketLin ( struct BucketLin * src );

void     delete_BucketLin ( struct BucketLin * src );

uint32_t address_value ( char * value );

int      put_value_bucket ( char * value, struct BucketLin * des );

void     add_overflow_bucket ( struct BucketLin * bucket );

void     split ();

void     get_elements_bucket ( struct BucketLin * bucket, char *** des, size_t * len );

uint32_t N;
uint32_t S;
uint32_t L;

struct stat stt = {0};

void init_linhashing ()
{

    if ( stat ( "./.lin_hash", &stt ) != -1 )
        system("rm -rf ./.lin_hash");

    mkdir ( "./.lin_hash", 0700 );

    N = INIT_M;
    S = 0;
    L = 0;

    struct BucketLin * bucket;

    for ( uint32_t i = 0; i < N; i++ )
    {
        bucket = ( struct BucketLin * ) malloc ( sizeof ( struct BucketLin ) );
        bucket->primary            = ( struct PrimaryBucket * ) malloc ( sizeof ( struct PrimaryBucket ) );
        bucket->primary->id        = i;
        bucket->primary->n_entries = 0;
        bucket->primary->overflow  = 0;
        write_BucketLin ( bucket );
        free ( bucket );
    }

}


uint32_t address_value ( char * value )
{
    uint32_t H     = hash_sequence ( value );
    fprintf ( stderr, "Hash of %s: %u\n", value, H);
    uint32_t index = H % ( INIT_M * ( 1 << L ) );
    fprintf (stderr, "Index: %d\n", index);

    if ( index < S )
        index = H % ( INIT_M * ( 1 << ( L + 1 ) ) );

    return index;
}

void put_value_linhashing ( char * value )
{

    fprintf ( stderr, "Putting value '%s' into hash table.\n", value );

    uint32_t a = address_value ( value );

    fprintf ( stderr, "Address of value: %d\n", a);

    struct BucketLin * bucket = ( struct BucketLin * ) malloc ( sizeof ( struct BucketLin ) );
    read_BucketLin ( bucket, a );

    int of = put_value_bucket ( value, bucket );
    write_BucketLin (bucket);
    free ( bucket );
    if ( of ) // overflow
        split ();
}

int put_value_bucket ( char * value, struct BucketLin * des )
{
    fprintf ( stderr, "Putting value '%s' into bucket %d.\n", value, des->primary->id );

    int first_overflow = 0;

    if ( des->primary->overflow > 0 )
    {

        fprintf ( stderr, "Bucket has overflow pages.\n" );

        if ( des->overflow[ des->primary->overflow - 1 ]->n_entries == MAX_ENTRIES )
            add_overflow_bucket ( des );

        uint32_t index = des->overflow[ des->primary->overflow - 1 ]->n_entries;
        des->overflow[ des->primary->overflow - 1 ]->n_entries++;
        strcpy ( ( char * ) des->overflow[ des->primary->overflow - 1 ]->entries[ index ], value );
    }
    else
    {
        if ( des->primary->n_entries == MAX_ENTRIES )
        {
            fprintf ( stderr, "Bucket is full, first overflow!\n");

            // first overflow
            first_overflow++;
            add_overflow_bucket ( des );

            des->overflow[ 0 ]->n_entries = 1;
            strcpy ( ( char * ) des->overflow[ 0 ]->entries[ 0 ], value );
        }
        else
        {
            uint32_t index = des->primary->n_entries;
            des->primary->n_entries++;
            strcpy ( ( char * ) des->primary->entries[ index ], value );
        }
    }

    return first_overflow;
}

void add_overflow_bucket ( struct BucketLin * bucket )
{

    fprintf ( stderr, "Adding overflow bucket to bucket %d\n", bucket->primary->id );

    struct OverflowBucket ** temp = ( struct OverflowBucket ** ) malloc (
            sizeof ( struct OverflowBucket ) * ( bucket->primary->overflow + 1 ));

    for ( int i = 0; i < bucket->primary->overflow + 1; i++ )
        temp[i] = ( struct OverflowBucket * ) malloc (sizeof ( struct OverflowBucket ));

    if ( bucket->primary->overflow > 0 )
    {
        memcpy ( temp, bucket->overflow, sizeof ( struct OverflowBucket ) * bucket->primary->overflow );
        free ( bucket->overflow );
    }

    temp[ bucket->primary->overflow ]->n_entries = 0;
    bucket->overflow                             = ( struct OverflowBucket ** ) malloc (
            sizeof ( struct OverflowBucket ) * ( bucket->primary->overflow + 1 ));

    memcpy ( bucket->overflow, temp, sizeof ( struct OverflowBucket ) * ( bucket->primary->overflow + 1 ) );
    bucket->primary->overflow++;
    free ( temp );

    fprintf ( stderr, "Succesfully added overflow bucket. \n");
}


void get_elements_bucket ( struct BucketLin * bucket, char *** des, size_t * len )
{
    fprintf ( stderr, "Getting all elements from bucket %d\n", bucket->primary->id );

    *len = bucket->primary->n_entries;
    for ( int i = 0; i < bucket->primary->overflow; i++ )
        *len += bucket->overflow[i]->n_entries;

    *des = (char **) malloc ( VALUE_LEN * (*len) );

    for ( int i = 0; i < bucket->primary->n_entries; i++ )
    {
        (*des)[i] = (char *) malloc ( VALUE_LEN );
        strcpy ( (*des)[i], (char *)bucket->primary->entries[i]);
    }


    int counter = bucket->primary->n_entries;
    for ( int i = 0; i < bucket->primary->overflow; i++ )
    {
        fprintf ( stderr, "Getting all elements from overflow %d\n", i );
        for( int j = 0; j < bucket->overflow[i]->n_entries; j++ )
        {
            (*des)[counter] = (char *) malloc ( VALUE_LEN );
            strcpy ( (*des)[counter], (char *)bucket->overflow[i]->entries[j]);
            counter++;
        }
    }
}

void split ()
{
    fprintf ( stderr, "Splitting\n" );
    struct BucketLin * bucket = ( struct BucketLin * ) malloc ( sizeof ( struct BucketLin ) );
    struct BucketLin * split  = ( struct BucketLin * ) malloc ( sizeof ( struct BucketLin ) );
    split->primary = ( struct PrimaryBucket * ) malloc ( sizeof (struct PrimaryBucket));
    read_BucketLin ( bucket, S );

    split->primary->n_entries = 0;
    split->primary->id = N;
    N++;
    split->primary->overflow = 0;
    uint32_t old_s = S;

    S++;
    if ( S == ( INIT_M * ( 1 << L ) ) )
    {
        S = 0;
        L++;
    }


    // redistribute elements
    size_t len;
    char ** elements;
    get_elements_bucket ( bucket, &elements, &len );
    delete_BucketLin ( bucket );
    free(bucket);
    bucket = ( struct BucketLin * ) malloc ( sizeof ( struct BucketLin ) );
    bucket->primary = ( struct PrimaryBucket * ) malloc ( sizeof(struct PrimaryBucket) );

    bucket->primary->n_entries = 0;
    bucket->primary->overflow = 0;
    bucket->primary->id = old_s;

    for ( int i = 0; i < len; i++ )
    {

        uint32_t a = address_value ( elements[i] );
        if ( a == old_s )
            put_value_bucket ( elements[i], bucket);
        else if ( a == split->primary->id)
            put_value_bucket ( elements[i], split );
        else
            fprintf (stderr, "Wrong bucket, wtf.");

    }

    write_BucketLin ( bucket );
    write_BucketLin ( split );
    free (bucket);
    free (split);
}

int search_linhashing ( char * value )
{
    return 0;
}

void pop_random_value_linhashing ( char * pop )
{

}


void read_BucketLin ( struct BucketLin * des, int k )
{
    char path[50];
    sprintf ( path, "./.lin_hash/%d.bucket", k );
    FILE                 * f       = fopen ( path, "rb" );
    des->primary = ( struct PrimaryBucket * ) malloc ( sizeof ( struct PrimaryBucket ) );
    if ( f != NULL )
    {
        fread ( des->primary, sizeof ( struct PrimaryBucket ), 1, f );
        fclose ( f );
    }


    if ( des->primary->overflow > 0 )
    {
        des->overflow = ( struct OverflowBucket ** ) malloc ( sizeof ( struct OverflowBucket ) * des->primary->overflow );

        for ( int i = 0; i < des->primary->overflow; i++ )
        {
            des->overflow[ i ] = (struct OverflowBucket * ) malloc ( sizeof (struct OverflowBucket ));
            sprintf ( path, "./.lin_hash/%d.overflow.%d", k, i );
            f = fopen ( path, "rb" );
            if ( f != NULL )
            {
                fread ( des->overflow[ i ], sizeof ( struct OverflowBucket ), 1, f );
                fclose ( f );
            }
        }
    }

    fprintf ( stderr, "Done\n");
}

void write_BucketLin ( struct BucketLin * src )
{
    char path[50];
    sprintf ( path, "./.lin_hash/%d.bucket", src->primary->id );
    FILE * f = fopen ( path, "wb" );
    if ( f != NULL )
    {
        fwrite ( src->primary, sizeof ( struct PrimaryBucket ), 1, f );
        fclose ( f );
    }

    if ( src->primary->overflow > 0 )
    {
        for ( int i = 0; i < src->primary->overflow; i++ )
        {
            sprintf ( path, "./.lin_hash/%d.overflow.%d", src->primary->id, i );
            f = fopen ( path, "wb" );
            if ( f != NULL )
            {
                fwrite ( src->overflow[ i ], sizeof ( struct OverflowBucket ), 1, f );
                fclose ( f );
            }

        }
    }
}

void delete_BucketLin ( struct BucketLin * src )
{
    char path[50];
    sprintf ( path, "./.lin_hash/%d.bucket", src->primary->id );
    unlink ( path );

    if ( src->primary->overflow > 0 )
    {
        for ( int i = 0; i < src->primary->overflow; i++ )
        {
            sprintf ( path, "./.lin_hash/%d.overflow.%d", src->primary->id, i );
            unlink ( path );
        }

    }
}