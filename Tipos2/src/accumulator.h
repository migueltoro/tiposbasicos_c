/*
 * accumulator.h
 *
 *  Created on: May 4, 2015
 *      Author: Boss
 */

#ifndef SRC_ACCUMULATOR_H_
#define SRC_ACCUMULATOR_H_

#include "tipos.h"
#include "map.h"
#include "list.h"
#include "set.h"
#include "sortedset.h"
#include "iterator.h"

typedef struct {
	int size_acum;
	void * acum;
	int size_result;
	void * result;
	supplier(get);
	bifunction(apply);
	function(f_result);
} accumulator_s;

typedef accumulator_s * accumulator_t;

typedef struct {
	long min;
	long max;
	long count;
	long sum;
	long squares_sum;
	double average;
	double variance;
	double standard_deviation;
} statistic_long_s;

typedef statistic_long_s * statistic_long_t;


statistic_long_t it_statistic_long(const iterator_t it);
char * statistic_long_tostring(statistic_long_t st, char * mem);

accumulator_t ac_create(int size_acum, int size_result,
		supplier(get), bifunction(apply), function(result));
void * it_reduce(const iterator_t it, accumulator_t a);

void ac_free(accumulator_t a);

typedef struct {
	int size_key;
	hashcode_function(hash_key);
	bipredicate(eq_key);
	void * mem_key;
	list_t list_key;
	list_t list_values;
	map_t map;
	supplier(groups_create);
	add_element_to_group_function(add);
	tostring_function(ts_key);
	tostring_function(ts_groups);
} grouping_s;

typedef grouping_s * grouping_t;

#define acum_function(ac) void * ( * ac)(iterator_t it, void * mem)

grouping_t gr_create(int size_key, hashcode_function(hash_key), bipredicate(eq_key),
		supplier(groups_create), add_element_to_group_function(ad));
void gr_aditional_info(grouping_t gr, tostring_function(ts_key), tostring_function(ts_groups));
boolean gr_add_all(grouping_t gr, iterator_t it, function(f_key));
char * gr_tostring(const grouping_t gr, char * s);
map_t gr_acum(grouping_t gr, iterator_from_function(it_from), acum_function(ac), int size_acum);

int it_int_sum(const iterator_t it);
long it_long_sum(const iterator_t it);
float it_float_sum(const iterator_t it);
double it_double_sum(const iterator_t it);
boolean it_all(const iterator_t it, predicate(p));
boolean it_any(const iterator_t it, predicate(p));
void * it_get(const iterator_t it, const int index);
void * it_find(const iterator_t it, predicate(p));
boolean it_contains(iterator_t it, void * e, bipredicate(p));
void * it_first(iterator_t it);
void * it_min(iterator_t it,comparator(c));
void * it_max(iterator_t it,comparator(c));
int it_size(const iterator_t it);
boolean it_isEmpty(const iterator_t it);
char * it_joining(iterator_t it, char * pr, char * sf, char * dl, char *s);
char * it_tostring(iterator_t it, tostring_function(ts), char *s);
statistic_long_t it_statistic_long(const iterator_t it);

list_t it_tolist(const iterator_t it);


set_t it_toset(const iterator_t it, hashcode_function(h), bipredicate(eq));


sset_t it_tosortedset(const iterator_t it, comparator(cmp));


void gr_free(grouping_t gr);

#endif /* SRC_ACCUMULATOR_H_ */
