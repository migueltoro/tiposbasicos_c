/*
 * hashtable.h
 *
 *  Created on: Apr 27, 2015
 *      Author: Boss
 */

#ifndef SRC_HASHTABLE_H_
#define SRC_HASHTABLE_H_

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#include "tipos.h"
#include "list.h"
#include "iterator.h"



typedef struct{
	int size;
	int numKey;
	double ratio;
	hashcode_function(hashcode);
	bipredicate(equals);
	list_t * table;
} hashtable_s;

typedef hashtable_s * hashtable_t;

/* Create a new hashtable. */
hashtable_t  ht_create(int size, double ratio, hashcode_function(h), bipredicate(p));
/* Create a new hashtable. */
hashtable_t  ht_create_d(hashcode_function(h), bipredicate(p));
/* Copy to a new hashtable. */
hashtable_t  ht_copy(const hashtable_t hashtable);
/* Insert a key-value pair into a hash table. */
void * ht_set( hashtable_t  hashtable, const void *key, const void *value );
/* Remove a key-value pair into a hash table. */
void * ht_remove_key( hashtable_t  hashtable, const void *key);
/* Insert a entry of key-value pair into a hash table. */
void ht_setEntry( hashtable_t  hashtable, const pair_t e);
/* Insert a iterator of key-value pairs into a hash table. */
void ht_set_all( hashtable_t  hashtable, iterator_t it);
/* Retrieve a key-value pair from a hash table. */
void * ht_get(const hashtable_t  hashtable, const void *key);
/* Retrieve a list of key-value pairs of a hash table. */
list_t ht_tolist(const hashtable_t  hashtable);
/* Retrieve a iterator of key-value pairs of a hash table. */
iterator_t ht_toiterator(const hashtable_t  ht);
char * ht_tostring(const hashtable_t  hashtable, tostring_function(f), char * mem);
void ht_free(hashtable_t  hashtable);


#endif /* SRC_HASHTABLE_H_ */
