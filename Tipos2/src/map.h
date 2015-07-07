/*
 * map.h
 *
 *  Created on: May 24, 2015
 *      Author: Boss
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "hashtable.h"
#include "set.h"
#include "list.h"
#include "iterator.h"


typedef struct {
	hashtable_t ht;
	boolean changed;
	set_t set_key;
	iterator_t it_entries;
	iterator_t it_keys;
	list_t list_entries;
	tostring_function(ts_key);
	tostring_function(ts_value);
}map_s;

typedef map_s * map_t;

map_t map_create(hashcode_function(hash_key), bipredicate(eq_key));
void map_aditional_info(map_t map, tostring_function(ts_key), tostring_function(ts_value));
void * map_put(map_t map, const void * key, const void * value);
void * map_get_entry(map_t map, const void * key);
void * map_get_value(map_t map, const void * key);
void * map_remove_key(map_t map, const void * key);
boolean map_isempty(const map_t map);
set_t map_keyset(const map_t map);
list_t map_entries(const map_t map);
iterator_t it_from_map_keys(const map_t map);
iterator_t it_from_map_entries(const map_t map);
int map_size(const map_t map);
char * map_tostring(const map_t map,char * s);
void map_free(map_t map);

#endif /* SRC_MAP_H_ */
