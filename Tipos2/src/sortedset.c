/*
 * sortedset.c

 *
 *  Created on: May 22, 2015
 *      Author: Miguel Toro
 */


#include "sortedset.h"

sset_t sortedset_create(comparator(compare)){
	sset_t ss = malloc(sizeof(sset_s));
	ss->tree = tr_create(compare);
	ss->lis = NULL;
	ss->changed = true;
	ss->ts_element = NULL;
	return ss;
}

sset_t sortedset_copy(sset_t st){
	sset_t ss = malloc(sizeof(sset_s));
	ss->tree = tr_create(st->tree->compare);
	ss->lis = NULL;
	ss->changed = true;
	ss->ts_element = st->ts_element;
	return ss;
}

void sortedset_aditional_info(sset_t st, tostring_function(ts_element)) {
	st->ts_element = ts_element;
}

boolean sortedset_add(sset_t st, const void * e){
	boolean r = tr_insert(st->tree, e);
	st->changed = r;
	return r;
}

boolean sortedset_add_all(sset_t st, const iterator_t it){
	boolean r = tr_insert_all(st->tree, it);
	st->changed = r;
	return r;
}

boolean sortedset_remove(sset_t st, const void * e) {
	boolean r = tr_remove_key(st->tree, e);
	st->changed = r;
	return r;
}

boolean sortedset_remove_all(sset_t st, const iterator_t it) {
	void * e;
	boolean acum = false, r;
	while(it->hasNext(it)){
		e = it->next(it);
		r = tr_remove_key(st->tree, e);
		if(r) acum = true;
	}
	st->changed = acum;
	return acum;
}

boolean sortedset_contains(sset_t st, const void * e){
	return tr_contains(st->tree,e);
}

void * sortedset_min(sset_t st) {
	return tr_findmin(st->tree);
}

void * sortedset_max(sset_t st) {
	return tr_findmax(st->tree);
}

int sortedset_size(sset_t st){
	return tr_size(st->tree);
}

list_t sortedset_tolist(sset_t st) {
	if (st->changed || st->lis == NULL) {
		ls_free(st->lis);
		st->lis = ls_create_d();
		ls_aditional_info(st->lis,st->ts_element);
		st->lis = tr_in_order_traversal(st->tree, st->lis);
		st->changed = false;
	}
	return st->lis;
}

char * sortedset_tostring(sset_t st, char * mem) {
	assert(st != NULL);
	list_t lis = sortedset_tolist(st);
	assert(st->lis != NULL);
	return ls_tostring(st->lis,mem);
}

iterator_t it_from_sortedset(sset_t st) {
	assert(st != NULL);
	list_t lis = sortedset_tolist(st);
	assert(st->lis != NULL);
	return it_from_list(st->lis);
}

void sortedset_free(sset_t st) {
	if (st != NULL) {
		ls_free(st->lis);
		tr_free(st->tree);
		free(st);
	}
	st = NULL;
}


