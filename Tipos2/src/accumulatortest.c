/*
 * accumulatortest.c

 *
 *  Created on: Jun 3, 2015
 *      Author: Miguel Toro
 */


#include "accumulatortest.h"

void * initial3(void * mem){
	 *(long * ) mem = getEnteroAleatorio(1000, 2000);;
	 return mem;
}

void * inc3(const void * e, void * rs){
	*(long *) rs = getEnteroAleatorio(1000, 2000);
	return rs;
}

void * key_f(const void * e, void * rs){
	long r = *(long *)e;
	*(long *) rs = r%7;
	return rs;
}

void * create_list_test1(void * mem){
	list_t lis = ls_create_d();
	lis->ts_element = long_tostring;
	return lis;
}

void accumulator_test1() {
	char r[1000];
	char * s = r;
	iterator_t it1 = it_sequence(initial3,inc3,sizeof(long));
	iterator_t it2 = it_limit(it1,50);
	iterator_t it3 = it_withmem(it2,sizeof(long));
	grouping_t gr = gr_create(sizeof(long), long_hashcode, long_equals, create_list_test1, ls_add);
	gr_aditional_info(gr, long_tostring, ls_tostring);
	gr_add_all(gr,it3, key_f);
	s = gr_tostring(gr, s);
	printf("accumulator_test1   = \n\n%s\n\n", s);
	void gr_free(gr);
}

void * create_set_test2(void * mem){
	set_t st = st_create(long_hashcode,long_equals);
	st->ts_element = long_tostring;
	return st;
}

void accumulator_test2() {
	char r[1000];
	char * s = r;
	iterator_t it1 = it_sequence(initial3,inc3,sizeof(long));
	iterator_t	it2 = it_limit(it1,50);
	iterator_t it3 = it_withmem(it2,sizeof(long));
	grouping_t gr = gr_create(sizeof(long), long_hashcode, long_equals, create_set_test2, st_add);
	gr_aditional_info(gr, long_tostring, st_tostring);
	gr_add_all(gr, it3, key_f);
	s = gr_tostring(gr, s);
	printf("accumulator_test2   = \n\n%s\n\n", s);
	void gr_free(gr);
}

void * create_sortedset_test3(void * mem){
	sset_t st = sortedset_create(long_natural_order);
	st->ts_element = long_tostring;
	return st;
}

void accumulator_test3() {
	char r[1000];
	char * s = r;
	iterator_t it1 = it_sequence(initial3,inc3,sizeof(long));
	iterator_t	it2 = it_limit(it1,50);
	iterator_t it3 = it_withmem(it2,sizeof(long));
	grouping_t gr = gr_create(sizeof(long), long_hashcode, long_equals, create_sortedset_test3, sortedset_add);
	gr_aditional_info(gr, long_tostring, sortedset_tostring);
	gr_add_all(gr,it3,key_f);
	s = gr_tostring(gr, s);
	printf("accumulator_test3   = \n\n%s\n\n", s);
	void gr_free(gr);
}

void * acum_test4(iterator_t it, void * acum){
	return it_min(it,long_natural_order);
}

void accumulator_test4() {
	char r[1000];
	char * s = r;
	map_t map;
	iterator_t it1 = it_sequence(initial3,inc3,sizeof(long));
	iterator_t	it2 = it_limit(it1,50);
	iterator_t it3 = it_withmem(it2,sizeof(long));
	grouping_t gr = gr_create(sizeof(long), long_hashcode, long_equals, create_sortedset_test3, sortedset_add);
	gr_aditional_info(gr, long_tostring, sortedset_tostring);
	gr_add_all(gr,it3,key_f);
	s = gr_tostring(gr,s);
	printf("accumulator_test4   = \n\n%s\n\n", s);
	map = gr_acum(gr,it_from_sortedset,acum_test4, sizeof(long));
	map_aditional_info(map, long_tostring, long_tostring);
	s = map_tostring(map, s);
	printf("map en accumulator_test4   = \n\n%s\n\n", s);
	void gr_free(gr);
}

void * acum_test5(iterator_t it, void * acum){
	*(long *) acum = it_long_sum(it);
	return acum;
}

void accumulator_test5() {
	char r[1000];
	char * s = r;
	map_t map;
	iterator_t it1 = it_sequence(initial3,inc3,sizeof(long));
	iterator_t	it2 = it_limit(it1,50);
	iterator_t it3 = it_withmem(it2,sizeof(long));
	grouping_t gr = gr_create(sizeof(long), long_hashcode, long_equals, create_sortedset_test3, sortedset_add);
	gr_aditional_info(gr, long_tostring, sortedset_tostring);
	gr_add_all(gr,it3,key_f);
	s = gr_tostring(gr,s);
	printf("accumulator_test5   = \n\n%s\n\n", s);
	map = gr_acum(gr,it_from_sortedset,acum_test5, sizeof(long));
	map_aditional_info(map, long_tostring, long_tostring);
	s = map_tostring(map, s);
	printf("map en accumulator_test5   = \n\n%s\n\n", s);
	void gr_free(gr);
}

void * acum_test6(iterator_t it, void * acum){
	return it_statistic_long(it);
}

void accumulator_test6() {
	char r[1000];
	char * s = r;
	map_t map;
	iterator_t it1 = it_sequence(initial3,inc3,sizeof(long));
	iterator_t	it2 = it_limit(it1,50);
	iterator_t it3 = it_withmem(it2,sizeof(long));
	grouping_t gr = gr_create(sizeof(long), long_hashcode, long_equals, create_sortedset_test3, sortedset_add);
	gr_aditional_info(gr, long_tostring, sortedset_tostring);
	gr_add_all(gr,it3,key_f);
	s = gr_tostring(gr,s);
	printf("accumulator_test6   = \n\n%s\n\n", s);
	map = gr_acum(gr,it_from_sortedset,acum_test6, sizeof(statistic_long_s));
	map_aditional_info(map, long_tostring, statistic_long_tostring);
	s = map_tostring(map, s);
	printf("map en accumulator_test6   = \n\n%s\n\n", s);
	void gr_free(gr);
}
