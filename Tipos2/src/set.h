/*
 * set.h
 *
 *  Created on: Apr 29, 2015
 *      Author: Boss
 */

#ifndef SRC_SET_H_
#define SRC_SET_H_

#include "tipos.h"
#include "hashtable.h"

typedef struct {
	hashtable_t ht;
	boolean changed;
	list_t lis;
	iterator_t it;
	tostring_function(ts_element);
}set_s;

typedef set_s * set_t;
/*
 * A new set is created giving a hash function and equality on the elements
*/
set_t st_create(hashcode_function(h), bipredicate(equals));
/*
 * A copy of a set is made
*/
set_t st_copy(set_t set);
/*
 * Adds a function to convert an element of a set in string
*/
void st_aditional_info(set_t set, tostring_function(ts_element));
/*
 * Adds an element to a set
*/
boolean st_add(set_t set, const void * e);
/*
 * Remove an element to a set
*/
boolean st_remove(set_t set, const void * e);
void st_add_all(set_t set, const iterator_t it);
void st_remove_all(set_t set, const iterator_t it);
void st_retain_all(set_t set, const iterator_t it);
boolean st_contains_all(set_t st, iterator_t it);
boolean st_contains(set_t set, const void * e);
int st_size(set_t set);
list_t st_tolist(set_t set);
char * st_tostring(set_t set, char * mem);
iterator_t it_from_set(set_t st);
void st_free(set_t st);

#endif /* SRC_SET_H_ */
