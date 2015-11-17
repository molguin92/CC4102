// Created by Manuel Olguin on 14-11-15.
// lin_hashing is part of Tarea2, for the course CC4102.
// This submission is developed together with Camila Romero.

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "lin_hashing.h"
#include "hash.h"


void     read_BucketLin ( struct BucketLin * des, int k );

void     write_BucketLin ( struct BucketLin * src );

void     delete_BucketLin ( struct BucketLin * src );

uint32_t address_value ( char * value );

int      put_value_bucket ( char * value, struct BucketLin * des );

void     add_overflow_bucket ( struct BucketLin * bucket );

void     delete_overflow_bucket ( struct BucketLin * bucket );

void     split ();

void     collapse();

void     get_elements_bucket ( struct BucketLin * bucket, char *** des, size_t * len );

void     free_bucket ( struct BucketLin * bucket );

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
        free_bucket ( bucket );
    }

}


uint32_t address_value ( char * value )
{
    uint32_t H     = hash_sequence ( value );
    uint32_t index = H % ( INIT_M * ( 1 << L ) );

    if ( index < S )
        index = H % ( INIT_M * ( 1 << ( L + 1 ) ) );

    return index;
}

void put_value_linhashing ( char * value )
{


    uint32_t a = address_value ( value );


    struct BucketLin * bucket = ( struct BucketLin * ) malloc ( sizeof ( struct BucketLin ) );
    read_BucketLin ( bucket, a );

    int of = put_value_bucket ( value, bucket );
    write_BucketLin (bucket);
    free_bucket ( bucket );
    if ( of ) // overflow
        split ();
}

int put_value_bucket ( char * value, struct BucketLin * des )
{

    size_t len;
    char ** elements;
    get_elements_bucket ( des, &elements, &len );
    for ( int i = 0; i < len; i++ )
        if ( strcmp ( elements[i], value ) == 0 )
            return 0;

    int first_overflow = 0;

    if ( des->primary->overflow > 0 )
    {


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


    struct OverflowBucket ** temp = ( struct OverflowBucket ** ) malloc (
            sizeof ( struct OverflowBucket ) * ( bucket->primary->overflow + 1 ));

    for ( int i = 0; i < bucket->primary->overflow + 1; i++ )
        temp[i] = ( struct OverflowBucket * ) malloc (sizeof ( struct OverflowBucket ));

    if ( bucket->primary->overflow > 0 )
    {
        memcpy ( temp, bucket->overflow, sizeof ( struct OverflowBucket ) * bucket->primary->overflow );
        temp[bucket->primary->overflow] = ( struct OverflowBucket * ) malloc (sizeof ( struct OverflowBucket ));
        free ( bucket->overflow );
    }

    (temp[ bucket->primary->overflow ])->n_entries = 0;
    bucket->overflow                             = ( struct OverflowBucket ** ) malloc (
            sizeof ( struct OverflowBucket ) * ( bucket->primary->overflow + 1 ));

    memcpy ( bucket->overflow, temp, sizeof ( struct OverflowBucket ) * ( bucket->primary->overflow + 1 ) );
    bucket->primary->overflow++;
    for ( int i = 0; i < bucket->primary->overflow; i++ )
        free(temp[i]);
    free ( temp );

}

void     delete_overflow_bucket ( struct BucketLin * bucket )
{


    struct OverflowBucket ** temp = ( struct OverflowBucket ** ) malloc (
            sizeof ( struct OverflowBucket ) * ( bucket->primary->overflow - 1 ));

    for ( int i = 0; i < bucket->primary->overflow - 1; i++ )
    {
        temp[i] = ( struct OverflowBucket * ) malloc (sizeof ( struct OverflowBucket ));
        memcpy ( temp[i], bucket->overflow[i], sizeof(struct OverflowBucket) );
    }

    free(bucket->overflow);
    bucket->overflow = ( struct OverflowBucket ** ) malloc (
            sizeof ( struct OverflowBucket ) * ( bucket->primary->overflow - 1 ));
    memcpy ( bucket->overflow, temp, sizeof(struct OverflowBucket) * (bucket->primary->overflow - 1));
    bucket->primary->overflow--;
    free ( temp );
}

void get_elements_bucket ( struct BucketLin * bucket, char *** des, size_t * len )
{

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
    free_bucket (bucket);
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

        free (elements[i]);
    }

    write_BucketLin ( bucket );
    write_BucketLin ( split );
    free_bucket (bucket);
    free_bucket (split);
    free (elements);

}

void collapse()
{
    N--;
    struct BucketLin * bucket = ( struct BucketLin * ) malloc ( sizeof ( struct BucketLin ) );
    struct BucketLin * split  = ( struct BucketLin * ) malloc ( sizeof ( struct BucketLin ) );
    uint32_t old_s = S;
    read_BucketLin ( bucket, S - 1 );
    read_BucketLin ( split, N );

    if ( S > 0 )
        S--;
    else
    {
        L--;
        S = (uint32_t)(( INIT_M * ( 1 << L ) ) - 1);
    }

    // join elements
    size_t len1;
    size_t len2;
    char ** elements1;
    char ** elements2;
    get_elements_bucket ( bucket, &elements1, &len1 );
    get_elements_bucket ( split, &elements2, &len2 );
    delete_BucketLin ( bucket );
    delete_BucketLin ( split );
    free_bucket ( bucket );
    free_bucket ( split );
    bucket = ( struct BucketLin * ) malloc ( sizeof ( struct BucketLin ) );
    bucket->primary = ( struct PrimaryBucket * ) malloc ( sizeof(struct PrimaryBucket) );
    bucket->primary->n_entries = 0;
    bucket->primary->overflow = 0;
    bucket->primary->id = old_s;

    for ( int i = 0; i < len1; i++ )
    {
        uint32_t a = address_value ( elements1[i] );
        if ( a == old_s )
            put_value_bucket ( elements1[i], bucket);

        free (elements1[i]);
    }

    for ( int i = 0; i < len2; i++ )
    {
        uint32_t a = address_value ( elements2[i] );
        if ( a == old_s )
            put_value_bucket ( elements2[i], bucket);

        free (elements2[i]);
    }

    write_BucketLin ( bucket );
    free_bucket (bucket);
    free(elements1);
    free (elements2);
}

int search_linhashing ( char * value )
{
    uint32_t address = address_value ( value );
    struct BucketLin * bucket = (struct BucketLin *) malloc ( sizeof (struct BucketLin));
    read_BucketLin ( bucket, address );

    size_t len;
    char ** elements;
    get_elements_bucket ( bucket, &elements, &len );

    for ( int i = 0; i < len; i++ )
        if ( strcmp ( value, elements[i] ) == 0 )
            return 1;

    return 0;
}

void pop_random_value_linhashing ( char * pop )
{
    srand ( time(NULL) );

    struct BucketLin * bucket = ( struct BucketLin * ) malloc ( sizeof ( struct BucketLin ) );
    bucket->primary = (struct PrimaryBucket *) malloc (sizeof(struct PrimaryBucket));
    uint32_t b_index;

    do
    {
        b_index = ( uint32_t ) ( rand () % N );
        read_BucketLin ( bucket, b_index ); // random bucket
    }
    while (bucket->primary->n_entries == 0);

    if ( bucket->primary->overflow > 0 )
    {
        uint32_t iover = (uint32_t)(bucket->primary->overflow - 1);
        uint32_t ientry = bucket->overflow[iover]->n_entries;

        strcpy ( pop, (char *)bucket->overflow[iover]->entries[ientry] );

        for ( int i = 0; i < VALUE_LEN; i++ )
            bucket->overflow[iover]->entries[ientry][i] = 0;

        bucket->overflow[iover]->n_entries--;
        if ( bucket->overflow[iover]->n_entries == 0 )
            delete_overflow_bucket (bucket);

        write_BucketLin (bucket);
    }
    else
    {
        strcpy ( pop, (char *)bucket->primary->entries[bucket->primary->n_entries - 1] );
        for ( int i = 0; i < VALUE_LEN; i++ )
            bucket->primary->entries[bucket->primary->n_entries - 1][i] = 0;

        bucket->primary->n_entries--;
        write_BucketLin (bucket);

        if ( bucket->primary->n_entries == 0)
            collapse ();
    }

    free_bucket (bucket);
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

void free_bucket ( struct BucketLin * bucket )
{

    for ( int i = 0; i < bucket->primary->overflow; i++ )
        free (bucket->overflow[i]);

    free (bucket->primary);
    //free (bucket->overflow);
    free (bucket);
}