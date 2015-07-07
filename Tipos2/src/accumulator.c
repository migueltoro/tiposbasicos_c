/*
 * accumulator.c

 *
 *  Created on: Jun 1, 2015
 *      Author: Miguel Toro
 */

#include "accumulator.h"



statistic_long_t statistic_long_create() {
	statistic_long_t st = malloc(sizeof(statistic_long_s));
	st->count = 0;
	st->max = 0;
	st->min = 0;
	st->sum = 0;
	st->squares_sum = 0;
	return st;
}

char * statistic_long_tostring(statistic_long_t st, char * mem) {
	sprintf(mem,"[count=%ld, max=%ld, min=%ld, sum=%ld, squares_sum=%ld, average=%.2lf, standard_deviation=%.2lf, variance=%.2lf]",
			st->count,st->max,st->min,st->sum,st->squares_sum,st->average,st->standard_deviation,st->variance);
	return mem;
}

statistic_long_t it_statistic_long(const iterator_t it) {
	statistic_long_t st = statistic_long_create();
	long present_value;
	while(it->hasNext(it)){
		present_value = * (long *) it->next(it);
		if(st->count == 0){
			st->min = present_value;
			st->max = present_value;
		} else {
			if (present_value < st->min) st->min = present_value;
			if (present_value > st->max) st->max = present_value;
		}
		st->count = st->count +1;
		st->sum = st->sum +present_value;
		st->squares_sum = st->squares_sum + present_value*present_value;
	}
	st->average = ((double)st->sum) / st->count;
	st->variance = ((double)st->squares_sum) / st->count - st->average*st->average;
	st->standard_deviation = sqrt(st->variance);
	return st;
}



void * it_reduce(const iterator_t it, accumulator_t a) {
	a->acum = a->get(a->acum);
	while(it->hasNext(it)){
		a->acum = a->apply(a->acum,it->next(it), a->acum);
	}
	a->result = a->f_result(a->acum,a->result);
	return a->result;
}

grouping_t gr_create(int size_key, hashcode_function(hash_key), bipredicate(eq_key),
		supplier(groups_create), add_element_to_group_function(add)) {
	grouping_t gr = malloc(sizeof(grouping_s));
	gr->mem_key = malloc(size_key);
	gr->list_key = ls_create(10, true, size_key);
	gr->list_values = NULL;
	gr->eq_key = eq_key;
	gr->hash_key = hash_key;
	gr->size_key = size_key;
	gr->add = add;
	gr->groups_create = groups_create;
	gr->map = map_create(hash_key,eq_key);
	return gr;
}

void gr_aditional_info(grouping_t gr, tostring_function(ts_key), tostring_function(ts_groups)){
	gr->ts_key = ts_key;
	gr->ts_groups = ts_groups;
	gr->list_key->ts_element = ts_key;
	gr->map->ts_key = ts_key;
	gr->map->ts_value = ts_groups;
}

boolean gr_add_all(grouping_t gr, iterator_t it, function(f_key)) {
	void * e;
	void * key;
	void * last_key;
	pair_t p;
	void * values;
	int pos;
	while(it->hasNext(it)){
		e = it->next(it);
		key = f_key(e,gr->mem_key);
		pos = ls_index(gr->list_key, key, gr->eq_key);
		if (pos < 0) {
			ls_add(gr->list_key,key);
			pos = gr->list_key->size-1;
		}
		last_key = ls_get(gr->list_key, pos);
		p = (pair_t) map_get_entry(gr->map,last_key);
		if(p!=NULL) {
			values = p->value;
		} else {
			values = gr->groups_create(NULL);
			map_put(gr->map,last_key,values);
		}
		gr->add(values,e);
	}
	return true;
}

char * gr_tostring(const grouping_t gr, char * s) {
	char temp[1000];
	char * r = temp;
	strcpy(s,"keys = ");
	r = ls_tostring(gr->list_key,r);
	strcat(s,r);
	strcat(s,"\ngroups = ");
	r = map_tostring(gr->map,r);
	strcat(s,r);
	return s;
}


map_t gr_acum(grouping_t gr, iterator_from_function(it_from), acum_function(ac), int size_acum) {
	map_t map = map_create(gr->hash_key,gr->eq_key);
	int i;
	void * key;
	void * values;
	void * acum = malloc(size_acum);
	void * last_acum;
	gr->list_values = ls_create(10, true, size_acum);
	iterator_t it;
	for(i=0; i < gr->list_key->size; i++){
		key = ls_get(gr->list_key, i);
		values = map_get_value(gr->map,key);
		it = it_from(values);
		acum = ac(it, acum);
		ls_add(gr->list_values,acum);
		last_acum = ls_get_last(gr->list_values);
		map_put(map,key,last_acum);
	}
	return map;
}

int it_int_sum(const iterator_t it) {
	assert(it != NULL);
	int a = 0;
	while(it->hasNext(it)){
		a = a + * (int *) it->next(it);
	}
	return a;
}

long it_long_sum(const iterator_t it){
	assert(it != NULL);
	long a = 0;
	while(it->hasNext(it)){
		a = a + * (long *) it->next(it);
	}
	return a;
}

float it_float_sum(const iterator_t it){
	assert(it != NULL);
	float a = 0;
	while(it->hasNext(it)){
		a = a + * (float *) it->next(it);
	}
	return a;
}

double it_double_sum(const iterator_t it) {
	assert(it != NULL);
	double a = 0;
	while(it->hasNext(it)){
		a = a + * (double *) it->next(it);
	}
	return a;
}

boolean it_all(const iterator_t it, predicate(test)){
	assert(it != NULL);
	boolean a = true;
	while(it->hasNext(it)){
		if(!test(it->next(it))){
			a = false;
			break;
		}
	}
	return a;
}

boolean it_any(const iterator_t it, predicate(test)){
	assert(it != NULL);
	boolean a = false;
	while(it->hasNext(it)){
			if(test(it->next(it))){
				a = true;
				break;
			}
	}
	return a;
}

void * it_get(const iterator_t it, const int index){
	assert(it != NULL);
	int i;
	void * r = NULL;
	void * a;
	for(i  =0 ;it->hasNext(it); i++){
		a = it->next(it);
		if(i == index) {
			r = a;
			break;
		}
	}
	return r;
}

void * it_find(const iterator_t it, predicate(test)){
	assert(it != NULL);
	void * r = NULL;
	void * a;
	while(it->hasNext(it)){
		a = it->next(it);
		if(test(a)) {
			r = a;
			break;
		}
	}
	return r;
}

boolean it_contains(iterator_t it, void * e, bipredicate(test)){
	assert(it != NULL);
	boolean r = false;
	void * p;
	while(it->hasNext(it)){
		p = it->next(it);
		if(test(p,e)) {
			r = true;
			break;
		}
	}
	return r;
}

int it_count(const iterator_t it) {
	assert(it != NULL);
	int a = 0;
	while(it->hasNext(it)){
		it->hasNext(it);
		a = a + 1;
	}
	return a;
}

boolean it_isEmpty(const iterator_t it) {
	assert(it != NULL);
	return it_count(it) == 0;
}

void * it_first(iterator_t it){
	assert(it != NULL);
	void * r = NULL;
	if(it->hasNext(it))
		r = it->next(it);
	return r;
}

void * it_min(iterator_t it,comparator(compare)){
	assert(it != NULL);
	void * r = NULL;
	void * min = NULL;
	while(it->hasNext(it)){
		r = it->next(it);
		if(min==NULL || compare(r,min) < 0)  min = r;
	}
	return min;
}

void * it_max(iterator_t it,comparator(compare)){
	assert(it != NULL);
	void * r = NULL;
	void * max = NULL;
	while(it->hasNext(it)){
		r = it->next(it);
		if(max==NULL || compare(r,max) > 0)  max = r;
	}
	return max;
}

char * it_joining(iterator_t it, char * pr, char * sf, char * dl, char *s) {
	assert(it != NULL);
	boolean isFirst = true;
	strcpy(s,pr);
	while(it->hasNext(it)){
		if(isFirst) {
			isFirst = false;
		} else {
			strcat(s,dl);
		}
		strcat(s,it->next(it));
	}
	strcat(s,sf);
	return s;
}

char * it_tostring(iterator_t it, tostring_function(ts), char *s) {
	assert(it != NULL);
	char temp[1000];
	char * r = temp;
	boolean isFirst = true;
	void *e;
	strcpy(s,"{");
	while(it->hasNext(it)){
		if(isFirst) {
			isFirst = false;
		} else {
			strcat(s,",");
		}
		e = it->next(it);
		r = ts(e,r);
		strcat(s,r);
	}
	strcat(s,"}");
	return s;
}

list_t it_tolist(const iterator_t it) {
	assert(it != NULL);
	list_t lis = ls_create(10,true,it->size_dato);
	ls_add_all(lis,it);
	return lis;
}


set_t it_toset(const iterator_t it, hashcode_function(h), bipredicate(eq)) {
	assert(it != NULL);
	set_t s = st_create(h,eq);
	st_add_all(s,it);
	return s;
}

sset_t it_tosortedset(const iterator_t it, comparator(cmp)) {
	assert(it != NULL);
	sset_t s = sortedset_create(cmp);
	sortedset_add_all(s,it);
	return s;
}

void gr_free(grouping_t gr) {
	if (gr) {
		free(gr->mem_key);
		ls_free(gr->list_key);
		ls_free(gr->list_values);
		map_free(gr->map);
	}
}
