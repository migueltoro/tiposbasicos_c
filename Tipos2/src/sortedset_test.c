/*
 * sortedset_test.c

 *
 *  Created on: May 24, 2015
 *      Author: Miguel Toro
 */


#include "sortedset_test.h"


long a1 = 1;
long b1 = 1000;
double c1 = 7;

void * initial1(void * mem){
	 *(long * ) mem = getEnteroAleatorio(-1000, 1000);;
	 return mem;
}

void * inc1(const void * e, void * rs){
	*(long *) rs = getEnteroAleatorio(-1000, 1000);
	return rs;
}

void * cuadrado1(const void * e, void * mem){
	double r = *(double *)e;
	*(double *) mem = r*r;
	return mem;
}

void sortedset_test1(){
	char r[1000];
	char * s = r;
	iterator_t it1 = it_sequence(initial1,inc1,sizeof(long));
	iterator_t	it2 = it_limit(it1,50);
	iterator_t it3 = it_withmem(it2,sizeof(long));
	sset_t ss1 = sortedset_create(long_natural_order);
	sortedset_aditional_info(ss1,long_tostring);
	sortedset_add_all(ss1,it3);
	s = sortedset_tostring(ss1,s);
	printf("sortedset_test1   = \n\n %s\n\n", s);
}
