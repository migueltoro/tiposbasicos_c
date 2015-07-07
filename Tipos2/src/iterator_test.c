/*
 * iterator_test.c

 *
 *  Created on: May 24, 2015
 *      Author: Miguel Toro
 */

#include "iterator_test.h"


long * initial_value(long * m){
	 * m = 1;
	 return m;
}

boolean es_menor_que(const long * e){
	long r = * e;
	return r < 11;
}

boolean es_mayor_que(const long * e){
	long r = * e;
	return r > 1000;
}

long * next_value(const long * e, long * rs){
	long r = * e;
	* rs = siguientePrimo(r);
	return rs;
}

long * cuadrado(const long * e, long * mem){
	long r = * e;
	* mem = r*r;
	return mem;
}

boolean en_primer_cuadrante(const punto_t p){
	return p->x >=0. && p->y>=0.;
}



void iterator_test1() {
	char r[TAM_STRING];
	char * s = r;
	iterator_t it1 = it_sequence(initial_value,next_value,sizeof(long));
	iterator_t	it2 = it_limit(it1,50);
	iterator_t	it3 = it_transform(it2,long_tostring, TAM_STRING);
	s = it_joining(it3, "{", "}", ",", s);
	printf("En iterator_test1\n\n");
	printf("%s\n\n",s);
	it_free(it1);
	it_free(it2);
	it_free(it3);
}

void iterator_test2() {
	char r[TAM_STRING];
	char * s = r;
	iterator_t it1 = it_sequence(initial_value,next_value,sizeof(long));
	iterator_t it2 = it_transform(it1,cuadrado,sizeof(long));
	iterator_t it3 = it_while(it2,es_menor_que);
	iterator_t it4 = it_transform(it3,long_tostring,TAM_STRING);
	s = it_joining(it4, "{", "}", ",", s);
	printf("En iterator_test2\n\n");
	printf("%s\n\n",s);
	it_free(it1);
	it_free(it2);
	it_free(it3);
	it_free(it4);
}

void iterator_test3() {
	char r[TAM_STRING];
	char * s = r;
	iterator_t it1 = it_sequence(initial_value,next_value,sizeof(long));
	iterator_t	it3 = it_filter(it1,es_mayor_que);
	long r2 = *(long *)it_first(it3);
	printf("En iterator_test3\n\n");
	printf("%ld\n\n",r2);
	it_free(it1);
	it_free(it3);
}

void iterator_test4() {
	char r[TAM_STRING];
	char * s = r;
	iterator_t it1 = it_from_file("puntos.txt");
	iterator_t it2 = it_transform(it1,pt_create_s,sizeof(punto_s));
	iterator_t it3 = it_filter(it2,en_primer_cuadrante);
	iterator_t	it4 = it_transform(it3,pt_tostring,TAM_STRING);
	s = it_joining(it4, "{", "}", ",", s);
	printf("En iterator_test4\n\n");
	printf("%s\n\n",s);
	it_free(it1);
	it_free(it2);
	it_free(it3);
	it_free(it4);
}

void iterator_test5() {
	char r[TAM_STRING];
	char * s = r;
	iterator_t it1 = it_from_file("puntos.txt");
	iterator_t it2 = it_transform(it1,pt_create_s,sizeof(punto_s));
	punto_t p = it_min(it2,pt_ord_distancia_al_origen);
	s = pt_tostring(p,s);
	printf("En iterator_test5\n\n");
	printf("El punto más cercano al origen = %s\n\n",s);
	it_free(it1);
	it_free(it2);
}

void iterator_test6() {
	char r[1000];
	char * s = r;
	iterator_t it1 = it_from_file("puntos.txt");
	iterator_t it2 = it_transform(it1,pt_create_s,sizeof(punto_s));
	iterator_t it3 = it_sort(it2,pt_ord_distancia_al_origen_2);
	iterator_t	it4 = it_transform(it3,pt_tostring,TAM_STRING);
	s = it_joining(it4, "{", "}", ",", s);
	printf("En iterator_test6\n\n");
	printf("Lista ordenada = %s\n\n",s);
	it_free(it1);
	it_free(it2);
	it_free(it3);
	it_free(it4);
}

void iterator_test7() {
	char r[1000];
	char * s = r;
	iterator_t it1 = it_from_file("puntos.txt");
	iterator_t it2 = it_transform(it1,pt_create_s,sizeof(punto_s));
	list_t lis = it_tolist(it2);
	ls_aditional_info(lis,pt_tostring);
	s = ls_tostring(lis, s);
	printf("En iterator_test7\n\n");
	printf("La lista = %s\n\n",s);
	ls_sort(lis,pt_ord_distancia_al_origen_2);
	s = ls_tostring(lis, s);
	printf("En iterator_test7\n\n");
	printf("La lista = %s\n\n",s);
	it_free(it1);
	it_free(it2);
}

void iterator_test8() {
	long sum;
	char r[1000];
	char * s = r;
	long m1[] = {1,2,3,4};
	long m2[] = {5,6,7,8};
	iterator_t it1, it2, it3, it4, it5, it6, it7, it8;
	it1 = it_from_array(m1,4,sizeof(long));
	it2 = it_from_array(m2,4,sizeof(long));
	it3 = it_transform(it1,long_tostring, TAM_STRING);
	it4 = it_transform(it2,long_tostring, TAM_STRING);
	it7 = it_from_file("nnn.txt");
	list_t lis = ls_create_d();
	ls_add(lis,it3);
	ls_add(lis,it4);
	ls_add(lis,it7);
    it5 = it_from_list(lis);
	it6 = it_flat(it5);
	it8 = it_transform(it6,long_create_s,sizeof(long));
	sum = it_long_sum(it8);
	printf("En iterator_test8\n\n");
	printf("Suma = %ld\n\n", sum);
	it_free(it1);
	it_free(it2);
	it_free(it3);
	it_free(it4);
	it_free(it5);
	it_free(it6);
	it_free(it7);
}

void iterator_test9() {
	long sum;
	char r[1000];
	char * s = r;
	long m1[] = {1,2,3,4};
	long m2[] = {5,6,7,8};
	iterator_t it1, it2, it3, it4, it5, it6, it7, it8;
	it1 = it_from_array(m1,4,sizeof(long));
	it2 = it_from_array(m2,4,sizeof(long));
	it3 = it_transform(it1,long_tostring, TAM_STRING);
	it4 = it_transform(it2,long_tostring, TAM_STRING);
	it5 = it_from_file("nnn.txt");
	it6 = it_concat_3(it3,it4,it5);
	s = it_joining(it6, "{", "}", ",", s);
	printf("En iterator_test9\n\n");
	printf("Lista = %s\n\n",s);
}

boolean esmultiplode4(long * n){
	long m = * n;
	return m%4 ==0;
}

void iterator_test10() {
	long sum;
	char r[1000];
	char * s = r;
	long e1, e2;
	iterator_t it1, it2, it3, it4, it5, it6, it7, it8;
	it1 = it_range_long(1, 1000, 3);
	it2 = it_filter(it1,esmultiplode4);
	it3 = it_transform(it2,cuadrado,sizeof(long));
	it4 = it_transform(it3,long_tostring, TAM_STRING);
	s = it_joining(it4, "{", "}", ",", s);
	printf("En iterator_test10\n\n");
	printf("Iterator = %s\n\n",s);
}
