/*
 * map.c

 *
 *  Created on: May 24, 2015
 *      Author: Miguel Toro
 */

#include "map.h"

void st_free(set_t st);
iterator_t it_transform(const iterator_t it, function(f), int sizeDato);
boolean ls_add_all(list_t lista, const iterator_t it);

map_t map_create(hashcode_function(hash), bipredicate(test)){
	map_t mt = malloc(sizeof(map_s));
	mt->ht = ht_create_d(hash, test);
	return mt;
}

void map_aditional_info(map_t map, tostring_function(ts_key), tostring_function(ts_value)) {
	map->ts_key = ts_key;
	map->ts_value = ts_value;
}

void * map_put(map_t map, const void * ts_key, const void * ts_value){
	void * r = ht_get(map->ht,ts_key);
	ht_set(map->ht,ts_key,ts_value);
	return r;
}

void * map_get_entry(map_t map, const void * ts_key) {
	return ht_get(map->ht,ts_key);
}

void * map_get_value(map_t map, const void * ts_key) {
	void * r = NULL;
	pair_t entry = ht_get(map->ht,ts_key);
	if(entry) r = entry->value;
	return r;
}

boolean map_contains_key(map_t map, const void * ts_key) {
	return ht_get(map->ht,ts_key)!= NULL;
}

void * map_remove_key(map_t map, const void * ts_key){
	return ht_remove_key(map->ht,ts_key);
}

boolean map_isempty(const map_t map) {
	return map->ht->numKey == 0;
}

void map_get_derived(map_t map){
	if (map->changed) {
			st_free(map->set_key);
			map->set_key = st_create(map->ht->hashcode,map->ht->equals);
			it_free(map->it_entries);
			map->it_entries = ht_toiterator(map->ht);
			it_free(map->it_keys);
			map->it_keys = it_transform(map->it_entries,pair_get_key,0);
			st_add_all(map->set_key, map->it_keys);

			ls_free(map->list_entries);
			map->list_entries = ls_create_d();
			it_free(map->it_entries);
			map->it_entries = ht_toiterator(map->ht);
			ls_add_all(map->list_entries, map->it_entries);

			map->changed = false;
	}
}

set_t map_keyset(const map_t map) {
	map_get_derived(map);
	return map->set_key;
}

list_t map_entries(const map_t map) {
	map_get_derived(map);
	return map->list_entries;
}

iterator_t it_from_map_keys(const map_t map) {
	it_free(map->it_entries);
	map->it_entries = ht_toiterator(map->ht);
	it_free(map->it_keys);
	map->it_keys = it_transform(map->it_entries,pair_get_key,0);
	return map->it_keys;
}

iterator_t it_from_map_entries(const map_t map) {
	it_free(map->it_entries);
	map->it_entries = ht_toiterator(map->ht);
	return map->it_entries;
}

int map_size(const map_t map) {
	return map->ht->numKey;
}

char * map_tostring(const map_t map, char * s){
	assert(map != NULL);
	char temp[TAM_STRING];
	char * r = temp;
	pair_t pp;
	iterator_t it = ht_toiterator(map->ht);
	boolean isFirst = true;
	strcpy(s,"{");
	while(it->hasNext(it)){
		if(isFirst) {
			isFirst = false;
		} else {
			strcat(s,",");
		}
		pp = it->next(it);
		strcat(s,"(");
		r = map->ts_key(pp->key,r);
		strcat(s,r);
		strcat(s,",");
		r = map->ts_value(pp->value,r);
		strcat(s,r);
		strcat(s,")");
	}
	strcat(s,"}");
	return s;
}

void map_free(map_t map) {
	if(map != NULL) {
		it_free(map->it_entries);
		it_free(map->it_keys);
		ls_free(map->list_entries);
	}
}
