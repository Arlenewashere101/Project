
#ifndef BLOOM_FILTER_H_   /* Include guard */
#define BLOOM_FILTER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <string>
#include "murmur3.h"

void set_num_hashf (int k1);	//will set num hash functions
int Hash(string obj_name, uint32_t seed); // hash strings using mrmurhash
int hash_k[] (string obj_name);	// creates k num of has functions
void transform_hash();	// since vector size 0-99 need only 2 values: first and last digit (combined)
void fill_Bloom();
void insert (string obj_name); //insert hash to bloom
bool query (string obj_name); // check if hash is in bloom 1=true 0 =false

#endif