/*
 * set_test.c

 *
 *  Created on: May 24, 2015
 *      Author: Miguel Toro
 */
#include "tipos.h"
#include "set_test.h"
#include "punto.h"
#include "iterator.h"


char * pf(pair_t e, char * mem){
	mem = pt_tostring(e->key,mem);
	return mem;
}

void set_test1(){
	char r[1000];
	char * s = r;
	iterator_t it3;
	punto_s p;
	punto_t pp;
	set_t st1 = st_create(pt_hashcode,pt_equals);
	st_aditional_info(st1, pt_tostring);
	iterator_t it1 = it_from_file("puntos.txt");
	iterator_t it2 = it_transform(it1,pt_create_s,sizeof(punto_s));
	it3 = it_withmem(it2,sizeof(punto_s));
	st_add_all(st1,it3);
	pp = pt_create_2(&p,-21.,30.);
	st_remove(st1,&p);
	st_tostring(st1,s);
	printf("set_test2   =  \n\n %d  %s\n\n",st_size(st1), s);
}
