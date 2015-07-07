
/*
 * lista.c
 *
 *  Created on: 01/05/2011
 *      Author: mtoro
 */

#include "list.h"


#define INITIAL_TAM 10

void doubleSizeMax(list_t lis){
		int tm = lis->sizeMax;
		int sd = sizeof(void *);
		void * oldPointers = lis->pointers;
		void * oldData;
		mem_t mem;
		int i;
		char * p;
		lis->pointers = (void **) malloc(2*tm*sizeof(void *));
		memcpy(lis->pointers,oldPointers,tm*sd);
		free(oldPointers);
		if(lis->withMem){
			mem = lis->mem;
			oldData = mem->data;
			mem->data = (char *) malloc(2*tm*mem->sizeType);
			memcpy(mem->data, oldData, tm*mem->sizeType);
			for(i=0; i < 2*tm; i++){
						p = mem->data + i*mem->sizeType;
						lis->pointers[i] = p;
			}
			free(oldData);
		}
		lis->sizeMax = 2*tm;
}

void * getPuntero(list_t lis, int index){
		return lis->pointers[index];
}

mem_t copyMem(list_t lis, mem_t mem){
	mem_t r = (mem_t) malloc(sizeof(mem_s));
	r->data = (char *) malloc(lis->sizeMax*mem->sizeType);
	memcpy(r->data,mem->data,lis->sizeMax*mem->sizeType);
	return r;
}

list_t ls_create_d(){
	return ls_create(INITIAL_TAM, false, 0);
}

list_t ls_create(int sizeMax, boolean withMem, int sizeType) {
	int i;
	char * p;
	list_t lis = (list_t) malloc(sizeof(list_s));
	mem_t mem;
	lis->sizeMax = sizeMax;
	lis->size =0;
	lis->pointers = (void **) malloc(sizeMax*sizeof(void *));
	lis->mem = NULL;
	lis->ts_element = NULL;
	lis->withMem = withMem;
	if (lis->withMem) {
		mem = (mem_t) malloc(sizeof(mem_s));
		mem->sizeType = sizeType;
		mem->data = (char *) malloc(lis->sizeMax*sizeType);
		for(i=0; i < lis->sizeMax; i++){
			p = mem->data + i*sizeType;
			lis->pointers[i] = p;
		}
		lis->mem = mem;
	}
	return lis;
}

void ls_aditional_info(list_t lis, tostring_function(ts_element)) {
	lis->ts_element = ts_element;
}

list_t ls_copy(list_t lis){
	int sd = sizeof(void *);
	list_t r = (list_t) malloc(sizeof(list_s));
	r->sizeMax = lis->sizeMax;
	r->size = lis->size;
	if(lis->withMem){
		r->withMem = lis->withMem;
		r->mem = copyMem(lis,lis->mem);
	}
	r->pointers = (void **) malloc(lis->sizeMax*sd);
	return r;
}

list_t ls_create_var_int(const int numArgs,...) {
	int i;
	int p;
	va_list args;
	list_t lis = ls_create(numArgs, true, sizeof(int));
	va_start(args, numArgs);
	for(i = 0; i < numArgs; i++){
		p =  va_arg(args,int);
		ls_add(lis,&p);
	}
	va_end(args);
	lis->size = numArgs;
	return lis;
}

list_t ls_create_var_long(const int numArgs,...) {
	int i;
	long p;
	va_list args;
	list_t lis = ls_create(numArgs, true, sizeof(long));
	va_start(args, numArgs);
	for(i = 0; i < numArgs; i++){
		p =  va_arg(args,long);
		ls_add(lis,&p);
	}
	va_end(args);
	return lis;
}

list_t ls_create_var_double(const int numArgs,...) {
	int i;
	double p;
	va_list args;
	list_t lis = ls_create(numArgs, true, sizeof(int));
	va_start(args, numArgs);
	for(i = 0; i < numArgs; i++){
		p =  va_arg(args,double);
		ls_add(lis,&p);
	}
	va_end(args);
	return lis;
}

list_t ls_create_from_array(const void * datos, const int num, int sizeDatum) {
	int i;
	void * p;
	list_t lis = ls_create(num,false,0);
	for(i=0; i < num;i++){
		p = ((char *)datos)+i*sizeDatum;
		ls_add(lis,p);
	}
	return lis;
}

int ls_size(const list_t lis){
	return lis->size;
}

boolean ls_isEmpty(const list_t lis) {
	return lis->size == 0;
}

boolean ls_add(list_t lis, const void * e){
	mem_t mem;
	if(lis->size == lis->sizeMax){
		doubleSizeMax(lis);
	}
	if(lis->mem!=NULL){
		mem = lis->mem;
		memcpy(lis->pointers[lis->size],e,mem->sizeType);
	} else {
		lis->pointers[lis->size] = e;
	}
	lis->size = lis->size +1;
	return true;
}

boolean ls_add_index(list_t lis, const void * e, int index) {
	boolean r = false;
	int i;
	if(lis->size == lis->sizeMax){
			doubleSizeMax(lis);
	}
	if(index >=0 && index <= lis->size) {
		r = true;
		for(i=index;i<lis->size;i++){
			lis->pointers[i+1] =  lis->pointers[i];
		}
		lis->pointers[index] = e;
		lis->size = lis->size +1;
	}
	return r;
}

boolean ls_remove_index(list_t lis, int index) {
	boolean r = false;
	int i;
	if(index >=0 && index < lis->size) {
		r = true;
		for(i=index;i<lis->size-1;i++){
			lis->pointers[i] =  lis->pointers[i+1];
		}
		lis->size = lis->size - 1;
	}
	return r;
}

void * ls_get(const list_t lis, const int index){
	void * pos = NULL;
	if(index >=0 && index < lis->size) {
		pos = lis->pointers[index];
	}
	return pos;
}

void * ls_get_last(const list_t lis){
	return ls_get(lis,ls_size(lis)-1);
}

void * ls_get_first(const list_t lis) {
	return ls_get(lis,0);
}

void * ls_find(const list_t lis, predicate(test)) {
	int i;
	void * r = NULL;
	void * a;
	for(i=0;i<lis->size;i++){
			a = lis->pointers[i];
			if(test(a)) {
				r = a;
				break;
			}
		}
	return r;
}

int ls_index(list_t lis, const void * e, bipredicate(test)){
	int i;
	int r = -1;
	void * a;
	for(i=0;i<lis->size;i++){
		a = lis->pointers[i];
		if(test(a,e)) {
			r = i;
			break;
		}
	}
	return r;
}

boolean ls_contains(list_t lis, void * e, bipredicate(test)) {
	int i;
	boolean r = false;
	void * p;
	for(i=0;i<lis->size;i++){
		p = lis->pointers[i];
		if(test(p,e)) {
			r = true;
			break;
		}
	}
	return r;
}

char * ls_tostring(list_t lis, char * s) {
	int i;
	char temp[256];
	char * r = temp;
	assert(lis != NULL);
	strcpy(s, "{");
	for(i=0;i<lis->size;i++) {
		if(i!=0) strcat(s, ",");
		r = lis->ts_element(ls_get(lis,i),r);
		strcat(s, r);
	}
	strcat(s, "}");
	return s;
}

void ls_sort(list_t lis, comparator(compare)){
	qsort(lis->pointers,lis->size,sizeof(void *),compare);
}

void freeMem(mem_t m) {
	if (m != NULL) {
		free(m->data);
		free(m);
	}
}

void ls_free(list_t lis){
	if (lis != NULL) {
		if (lis->withMem) {
			freeMem(lis->mem);
		}
		free(lis->pointers);
		free(lis);
	}
	lis = NULL;
}



