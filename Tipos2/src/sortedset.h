/*
 * sortedset.h
 *
 *  Created on: May 21, 2015
 *      Author: Boss
 */

#ifndef SRC_SORTEDSET_H_
#define SRC_SORTEDSET_H_

#include "tipos.h"
#include "avltree.h"

typedef struct {
	avl_tree_t tree;
	list_t lis;
	boolean changed;
	tostring_function(ts_element);
} sset_s;

typedef sset_s *  sset_t;

sset_t sortedset_create(comparator(c));
sset_t sortedset_copy(sset_t set);
void sortedset_aditional_info(sset_t set, tostring_function(ts_element));
boolean sortedset_add(sset_t set, const void * e);
boolean sortedset_remove(sset_t set, const void * e);
boolean sortedset_add_all(sset_t set, const iterator_t it);
boolean sortedset_remove_all(sset_t set, const iterator_t it);
void * sortedset_min(sset_t set);
void * sortedset_max(sset_t set);
boolean sortedset_contains(sset_t set, const void * e);
int sortedset_size(sset_t set);
list_t sortedset_tolist(sset_t set);
iterator_t it_from_sortedset(sset_t st);
char * sortedset_tostring(sset_t set, char * mem);
void sortedset_free(sset_t set);

#endif /* SRC_SORTEDSET_H_ */
