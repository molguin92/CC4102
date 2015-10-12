//
// Created by arachnid92 on 24-09-15.
//

#include <stddef.h>
#include <stdint.h>
#define MB 1048576 //base 2, 1024^1024

#ifndef TAREA1_GENERATOR_H
#define TAREA1_GENERATOR_H

#endif //TAREA1_GENERATOR_H

void generateRandomString( size_t len_alphabet,
                           char * alphabet,
                           size_t len_string,
                           char *  string );

int charInAlphabet( char c, char * alphabet, size_t len_alphabet );
void extractStringFromFile( const char * filename, char * string, size_t len, char * alphabet );
void extractStringFromFile_convertSeparators( const char * filename, char * string, size_t len, char * alphabet, char separator );
void extractRandomSubstring ( size_t len_substring, char * substring, size_t len_string, char * string );