/*
 * set.c

 *
 *  Created on: May 21, 2015
 *      Author: Miguel Toro
 */

#include "set.h"

set_t st_create(hashcode_function(h),bipredicate(test)) {
	set_t ss = malloc(sizeof(set_s));
	ss->ht = ht_create_d(h, test);
	ss->changed = true;
	ss->lis = NULL;
	ss->it = NULL;
	ss->ts_element = NULL;
	return ss;
}

set_t st_copy(set_t st){
	set_t ss = malloc(sizeof(set_s));
	ss->ht = ht_copy(st->ht);
	ss->changed = true;
	ss->lis = NULL;
	ss->it = NULL;
	ss->ts_element = st->ts_element;
	return ss;
}

void st_aditional_info(set_t st, tostring_function(ts_element)) {
	st->ts_element = ts_element;
}

boolean st_add(set_t st, const void * e){
	int r = st->ht->numKey;
	ht_set(st->ht,e,NULL);
	st->changed = r != st->ht->numKey;
	return st->changed;
}

boolean st_remove(set_t st, const void * e){
	int r = st->ht->numKey;
	ht_remove_key(st->ht,e);
	st->changed = r != st->ht->numKey;
	return st->changed;
}

void st_add_all(set_t st, iterator_t it) {
	while(it->hasNext(it)){
		void * p = it->next(it);
		st_add(st,p);
	}
}

void st_remove_all(set_t st, iterator_t it) {
	while(it->hasNext(it)){
		void * p = it->next(it);
		st_remove(st,p);
	}
}

void st_retain_all(set_t st, iterator_t it) {
	set_t r = st_create(st->ht->hashcode,st->ht->equals);
	while(it->hasNext(it)){
		void * p = it->next(it);
		if(st_contains(st,p)){
			st_add(r,p);
		}
	}
	st->ht = r->ht;
	st->changed = true;
}

boolean st_contains_all(set_t st, iterator_t it) {
	boolean r = true;
	while(it->hasNext(it)){
		void * p = it->next(it);
		if(!st_contains(st,p)){
			r = false;
			break;
		}
	}
	return r;
}


boolean st_contains(set_t st, const void * e) {
	return ht_get(st->ht,e)!=NULL;
}

int st_size(set_t st){
	return st->ht->numKey;
}

iterator_t it_from_set(set_t st) {
	it_free(st->it);
	st->it = ht_toiterator(st->ht);
	return st->it;
}

list_t st_tolist(set_t st){
	if(st->changed || st->lis == NULL) {
		it_free(st->it);
		st->it = ht_toiterator(st->ht);
		ls_free(st->lis);
		st->lis = ls_create_d();
		st->lis->ts_element = st->ts_element;
		while(st->it->hasNext(st->it)){
			pair_t p = st->it->next(st->it);
			void * key = p->key;
			ls_add(st->lis,key);
		}
		st->changed = false;
	}
	return st->lis;
}

char * st_tostring(set_t st, char * s){
	assert(st != NULL);
	list_t lis = st_tolist(st);
	assert(lis != NULL);
	return ls_tostring(lis,s);
}


void st_free(set_t s){
	if (s != NULL) {
		ht_free(s->ht);
		it_free(s->it);
		ls_free(s->lis);
		free(s);
	}
}
