/*
 * iterator.c

 *
 *  Created on: Apr 29, 2015
 *      Author: Miguel Toro
 */


#include "iterator.h"

boolean ls_add_all(list_t lista, const iterator_t it);

iterator_t it_create(int sizeDato,
		boolean ( * hasNext) (iterator_t),
		void * ( * next) (iterator_t),
		void * ( * peek) (iterator_t),
		void ( * free_mem) (void *),
		void * info) {
	iterator_t it = (iterator_t) malloc (sizeof(struct iterator_s));
	it->size_dato = sizeDato;
	it->aditional_info = info;
	if (sizeDato > 0) {
		it->next_value = malloc(sizeDato);
		it->old_next_value = malloc(sizeDato);
	}
	it->next = next;
	it->hasNext = hasNext;
	it->peek = peek;
	it->free_aditional_mem = free_mem;
	it->list = NULL;
	return it;
}

void free_info(void * aditional_info) {
	if(aditional_info != NULL) free(aditional_info);
	aditional_info = NULL;
}

typedef struct {
	int a;
	int b;
	int c;
	boolean inc;
}info_range_int_s;

typedef info_range_int_s * info_range_int_t;

info_range_int_t create_info_range_int(int a, int b, int c){
	info_range_int_t info = NULL;
	int r = (b-a)*c;
	if(r > 0){
		info = malloc(sizeof(info_range_int_s));
		info->a = a;
		info->b = b;
		info->c = c;
		info->inc = b-a >0 ? true: false;
	}
	return info;
}

boolean hasNext_range_int(iterator_t it){
	info_range_int_t info = it->aditional_info;
	return (info->inc && (*(int *)it->next_value < info->b)) || (!info->inc && (*(int *)it->next_value > info->b));
}

void * peek_range_int(iterator_t it){
	if(!it->hasNext(it)) return NULL;
	return it->next_value;
}

void * next_range_int(iterator_t it){
	info_range_int_t info = it->aditional_info;
	if(!it->hasNext(it)) return NULL;
	memcpy(it->old_next_value,it->next_value,it->size_dato);
	* (int *) it->next_value = * (int *) it->next_value + info->c;
	return it->old_next_value;
}

iterator_t it_range_int(int a, int b, int c){
	info_range_int_t info = create_info_range_int(a,b,c);
	iterator_t it = NULL;
	if (info!=NULL) {
		it = it_create(sizeof(int), hasNext_range_int, next_range_int, peek_range_int, free_info, info);
		* (int *) it->next_value = info->a;
	}
	return it;
}

typedef struct {
	long a;
	long b;
	long c;
	boolean inc;
}info_range_long_s;

typedef info_range_long_s * info_range_long_t;

info_range_long_t create_info_range_long(long a, long b, long c){
	info_range_long_t info = NULL;
	long r = (b-a)*c;
	if(r > 0){
		info = malloc(sizeof(info_range_long_s));
		info->a = a;
		info->b = b;
		info->c = c;
		info->inc = b-a >0 ? true: false;
	}
	return info;
}

boolean hasNext_range_long(iterator_t it){
	info_range_long_t info = it->aditional_info;
	return (info->inc && (*(long *) it->next_value < info->b)) || (!info->inc && (*(long *)it->next_value > info->b));
}

void * peek_range_long(iterator_t it){
	if(!it->hasNext(it)) return NULL;
	return it->next_value;
}

void * next_range_long(iterator_t it){
	info_range_int_t info = it->aditional_info;
	if(!it->hasNext(it)) return NULL;
	memcpy(it->old_next_value,it->next_value,it->size_dato);
	* (long *) it->next_value = * (long *) it->next_value + info->c;
	return it->old_next_value;
}

iterator_t it_range_long(long a, long b, long c){
	info_range_long_t info = create_info_range_long(a,b,c);
	iterator_t it = NULL;
	if (info!=NULL) {
		it = it_create(sizeof(long), hasNext_range_long, next_range_long, peek_range_long, free_info, info);
		* (long *) it->next_value = info->a;
	}
	return it;
}

typedef struct {
	double a;
	double b;
	double c;
	boolean inc;
}info_range_double_s;

typedef info_range_double_s * info_range_double_t;

info_range_double_t create_info_range_double(double a, double b, double c){
	info_range_double_t info = NULL;
	double r = (b-a)*c;
	if(r > 0){
		info = malloc(sizeof(info_range_long_s));
		info->a = a;
		info->b = b;
		info->c = c;
		info->inc = b-a >0 ? true: false;
	}
	return info;
}

boolean hasNext_range_double(iterator_t it){
	info_range_double_t info = it->aditional_info;
	return (info->inc && ( *(double *)it->next_value< info->b)) || (!info->inc && (*(double *)it->next_value > info->b));
}

void * peek_range_double(iterator_t it){
	if(!it->hasNext(it)) return NULL;
	return it->next_value;
}

void * next_range_double(iterator_t it){
	info_range_int_t info = it->aditional_info;
	if(!it->hasNext(it)) return NULL;
	memcpy(it->old_next_value,it->next_value,it->size_dato);
	* (double *) it->next_value = * (double *) it->next_value + info->c;
	return it->old_next_value;
}

iterator_t it_range_double(double a, double b, double c){
	info_range_double_t info = create_info_range_double(a,b,c);
	iterator_t it = NULL;
	if (info!=NULL) {
		it = it_create(sizeof(int), hasNext_range_double, next_range_double, peek_range_double, free_info, info);
		* (double *) it->next_value = info->a;
	}
	return it;
}

typedef struct {
	supplier(get);
	function(apply);
} infoSequence_s;

typedef infoSequence_s * infoSequence_t;

infoSequence_t createInfoSec(supplier(get),function(apply)){
	infoSequence_t inft = (infoSequence_t) malloc(sizeof(infoSequence_s));
	inft->get = get;
	inft->apply = apply;
	return inft;
}

boolean hasNextSequence(iterator_t it){
	return true;
}

void * peekSequence(iterator_t it){
	if(!it->hasNext(it)) return NULL;
	return it->next_value;
}

void * nextSequence(iterator_t it){
	infoSequence_t info = it->aditional_info;
	if(!it->hasNext(it)) return NULL;
	memcpy(it->old_next_value,it->next_value,it->size_dato);
	it->next_value = info->apply(it->next_value,it->next_value);
	return it->old_next_value;
}

iterator_t it_sequence(supplier(get),function(apply), int sizeDato){
	infoSequence_t info = createInfoSec(get,apply);
	iterator_t it = it_create(sizeDato, hasNextSequence, nextSequence, peekSequence, free_info, info);
	it->next_value = get(it->next_value);
	return it;
}

typedef struct {
	iterator_t ib;
	predicate(test);
} infoWhile_s;

typedef infoWhile_s * infoWhile_t;

infoWhile_t createInfoWhile(iterator_t ib,predicate(test)){
	infoWhile_t inft = (infoWhile_t) malloc(sizeof(infoWhile_s));
	inft->test = test;
	inft->ib = ib;
	return inft;
}

boolean hasNextWhile(iterator_t it){
	infoWhile_t info = it->aditional_info;
	iterator_t ib = info->ib;
	return ib->hasNext(ib) && info->test(ib->peek(ib));
}

void * peekWhile(iterator_t it) {
	infoWhile_t info = it->aditional_info;
	iterator_t ib = info->ib;
	if(!it->hasNext(it)) return NULL;
	return ib->peek(ib);
}

void * nextWhile(iterator_t it){
	infoWhile_t info = it->aditional_info;
	iterator_t ib = info->ib;
	if(!it->hasNext(it)) return NULL;
	return ib->next(ib);
}

iterator_t it_while(iterator_t ib, predicate(test)){
	infoWhile_t info = createInfoWhile(ib,test);
	iterator_t r = it_create(0, hasNextWhile, nextWhile, peekWhile, free_info, info);
	return r;
}


typedef struct {
	predicate(test);
	iterator_t ib;
} infoFilter_s;

typedef infoFilter_s * infoFilter_t;

infoFilter_t createInfoFilter(predicate(test), iterator_t it){
	infoFilter_t inft = (infoFilter_t) malloc(sizeof(infoFilter_s));
	inft->test = test;
	inft->ib = it;
	return inft;
}

boolean hasNextFilter(iterator_t it){
	return it->peek(it) != NULL;
}

void * peekFilter(iterator_t it) {
	infoFilter_t info = it->aditional_info;
	iterator_t ib = info->ib;
	if(!ib->hasNext(ib)) return NULL;
	while (ib->hasNext(ib)) {
		if(info->test(ib->peek(ib))){
			break;
		}
		ib->next(ib);
	}
	if(ib->hasNext(ib)){
		return ib->peek(ib);
	} else {
		return NULL;
	}
}

void * nextFilter(iterator_t it){
	infoFilter_t info = it->aditional_info;
	iterator_t ib = info->ib;
	if(!it->hasNext(it)) return NULL;
	while (ib->hasNext(ib)) {
		if(info->test(ib->peek(ib))){
			break;
		}
		ib->next(ib);
	}
	return ib->next(ib);;
}

iterator_t it_filter(iterator_t ib, predicate(test)){
	infoFilter_t info = createInfoFilter(test,ib);
	iterator_t it = it_create(0, hasNextFilter, nextFilter, peekFilter, free_info, info);
	return it;
}

typedef struct {
	function(apply);
	iterator_t ib;
} infoTransform_s;

typedef infoTransform_s * infoTransform_t;

infoTransform_t createInfoTransform(function(apply), iterator_t ib){
	infoTransform_t inft = (infoTransform_t) malloc(sizeof(infoTransform_s));
	inft->apply = apply;
	inft->ib = ib;
	return inft;
}


boolean hasNextTransform(iterator_t it){
	infoTransform_t info = it->aditional_info;
	iterator_t ib = info->ib;
	return ib->hasNext(ib);
}

void * peekTransform(iterator_t it){
	infoTransform_t info = it->aditional_info;
	iterator_t ib = info->ib;
	if(!it->hasNext(it)) return NULL;
	it->next_value = info->apply(ib->peek(ib),it->next_value);
	return it->next_value;
}

void * nextTransform(iterator_t it){
	infoTransform_t info = it->aditional_info;
	iterator_t ib = info->ib;
	if(!it->hasNext(it)) return NULL;
	return info->apply(ib->next(ib),it->next_value);
}

iterator_t it_transform(iterator_t ib, function(apply), int sizeDato){
	infoTransform_t info = createInfoTransform(apply,ib);
	iterator_t it = it_create(sizeDato, hasNextTransform, nextTransform, peekTransform, free_info, info);
	it->next_value = info->apply(ib->peek(ib),it->next_value);
	return it;
}

typedef struct {
	iterator_t it_seq;
	iterator_t it_base;
} infoFlat;

typedef infoFlat * infoFlat_t;

infoFlat_t createInfoFlat(iterator_t seq){
	infoFlat_t info = (infoFlat_t) malloc(sizeof(infoFlat));
	info->it_seq = seq;
	return info;
}

boolean hasNextFlat(iterator_t it){
	infoFlat_t info = it->aditional_info;
	iterator_t it_seq = info->it_seq;
	iterator_t it_base = info->it_base;
	return   it_base->hasNext(it_base) || it_seq->hasNext(it_seq);
}

void * peekFlat(iterator_t it) {
	if(!it->hasNext(it)) return NULL;
	void * r;
	iterator_t nextIt;
	infoFlat_t info = it->aditional_info;
	iterator_t it_seq = info->it_seq;
	iterator_t it_base = info->it_base;
	if (it_base->hasNext(it_base))
		r = it_base->peek(it_base);
	else {
		nextIt =  it_seq->peek(it_seq);
		r = nextIt->peek(nextIt);
	}
	return r;
}

void * nextFlat(iterator_t it){
	infoFlat_t info = it->aditional_info;
	iterator_t it_base = info->it_base;
	iterator_t it_seq = info->it_seq;
	if(!it->hasNext(it)) return NULL;
	if(!it_base->hasNext(it_base)){
			info->it_base = it_seq->next(it_seq);
	}
	return info->it_base->next(info->it_base);
}

iterator_t it_flat(const iterator_t seq) {
	char r[1000];
	char * s = r;
	infoFlat_t info = createInfoFlat(seq);
	iterator_t it = it_create(0, hasNextFlat, nextFlat, peekFlat, free_info, info);
	info->it_base = seq->next(seq);
	strcpy(s,info->it_base->peek(info->it_base)) ;
	return it;
}


typedef struct {
	long i;
	long max;
	iterator_t ib;
} infoLimit;

typedef infoLimit * infoLimit_t;

infoLimit_t createInfoLimit(iterator_t it, long max){
	infoLimit_t inft = (infoLimit_t) malloc(sizeof(infoLimit));
	inft->ib = it;
	inft->i = 0;
	inft->i = max;
	return inft;
}

boolean hasNextLimit(iterator_t it){
	infoLimit * info = it->aditional_info;
	iterator_t ib = info->ib;
	long i = info->i;
	long max = info->max;
	return ib->hasNext(ib) && i<max;
}

void * peekLimit(iterator_t it) {
	infoLimit * info = it->aditional_info;
	iterator_t ib = info->ib;
	if(!it->hasNext(it)) return NULL;
	return ib->peek(ib);
}

void * nextLimit(iterator_t it){
	infoLimit * info = it->aditional_info;
	iterator_t ib = info->ib;
	if(!it->hasNext(it)) return NULL;
	info->i = info->i +1;
	return ib->next(ib);
}

iterator_t it_limit(const iterator_t ib, long max) {
	infoLimit_t info = createInfoLimit(ib,max);
	info->i = 0;
	info->max = max;
	iterator_t it = it_create(0, hasNextLimit, nextLimit, peekLimit, free_info, info);
	return it;
}

typedef struct {
	long i;
	long n;
	void * d;
} infoArray;

typedef infoArray * infoArray_t;

infoArray_t createInfoArray(void * d, long n){
	infoArray_t info = (infoArray_t) malloc(sizeof(infoArray));
	info->d = d;
	info->n = n;
	return info;
}

boolean hasNextArray(iterator_t it){
	infoArray_t info = it->aditional_info;
	long i = info->i;
	long n = info->n;
	return i<n;
}

void * peekArray(iterator_t it) {
	infoArray_t info = it->aditional_info;
	long i = info->i;
	char * d = info->d;
	int size_dato = it->size_dato;
	if(!it->hasNext(it)) return NULL;
	return d+i*size_dato;
}

void * nextArray(iterator_t it){
	infoArray_t info = it->aditional_info;
	if(!it->hasNext(it)) return NULL;
	int olDi = info->i;
	char * d = info->d;
	int size_dato = it->size_dato;
	info->i = info->i +1;
	return d+olDi*size_dato;
}

iterator_t it_from_array(const void * d, int n, int size_dato){
	infoArray_t info = createInfoArray(d,n);
	info->i = 0;
	iterator_t it = it_create(size_dato, hasNextArray, nextArray, peekArray, free_info,info);
	return it;
}

typedef struct {
	list_t lis;
	int index;
} infoList_s;

typedef infoList_s * infoList_t;

infoList_t createInfoList(list_t lis){
	infoList_t inft = (infoList_t) malloc(sizeof(infoList_s));
	inft->lis = lis;
	inft->index = 0;
	return inft;
}

boolean hasNextList(iterator_t it){
	infoList_t inft = it->aditional_info;
	list_t lis = inft->lis;
	int index = inft->index;
	return index < lis->size;
}

void * peekList(iterator_t it){
	infoList_t inft = it->aditional_info;
	list_t lis = inft->lis;
	int index = inft->index;
	return ls_get(lis,index);
}

void * nextList(iterator_t it){
	infoList_t inft = it->aditional_info;
	list_t lis = inft->lis;
	int index = inft->index;
	void * r= ls_get(lis,index);
	inft->index = inft->index +1;
	return r;
}

iterator_t it_from_list(list_t lis) {
	infoList_t info = createInfoList(lis);
	iterator_t it = it_create(0, hasNextList, nextList, peekList, free_info, info);
	info->index = 0;
	return it;
}

typedef struct {
	char file[TAM_STRING];
	FILE * f;
} infoFile_s;

typedef infoFile_s * infoFile_t;

infoFile_t createInfoFile(char * file){
	infoFile_t inft = (infoFile_t) malloc(sizeof(infoFile_s));
	strcpy(inft->file,file);
	return inft;
}

boolean hasNextFile(iterator_t it){
	infoFile_t inft = it->aditional_info;
	return !feof(inft->f);
}

void * peekFile(iterator_t it){
	return  it->next_value;
}

void * nextFile(iterator_t it){
	infoFile_t inft = it->aditional_info;
	strcpy(it->old_next_value,it->next_value);
	fgets(it->next_value,TAM_STRING,inft->f);
	it->next_value = remove_eol(it->next_value);
	return it->old_next_value;
}

iterator_t it_from_file(char * file) {
	infoFile_t info = createInfoFile(file);
	iterator_t it = it_create(TAM_STRING, hasNextFile, nextFile, peekFile, free_info, info);
	info->f = fopen(file,"r");
	if(info->f!=NULL){
		fgets(it->next_value,TAM_STRING,info->f);
		it->next_value = remove_eol(it->next_value);
	} else {
		it_free(it);
		it = NULL;
	}
	return it;
}

typedef struct {
	iterator_t last;
	iterator_t t1;
	list_t lis;
}info_concat_2_s;

typedef info_concat_2_s * info_concat_2_t;

info_concat_2_t createInfoConcat2(iterator_t last, iterator_t t1, list_t lis){
	info_concat_2_t inft = (info_concat_2_t) malloc(sizeof(info_concat_2_s));
	inft->lis = lis;
	inft->last = last;
	inft->t1 = t1;
	return inft;
}

void free_concat_2(void * infot){
	info_concat_2_t info = infot;
	ls_free(info->lis);
	it_free(info->t1);
	it_free(info->last);
	free(info);
	info = NULL;
}

boolean hasNextConcat(iterator_t it){
	info_concat_2_t inft = it->aditional_info;
	iterator_t last = inft->last;
	return last->hasNext(last);
}

void * peekConcat(iterator_t it){
	info_concat_2_t inft = it->aditional_info;
	iterator_t last = inft->last;
	return last->peek(last);
}

void * nextConcat(iterator_t it){
	info_concat_2_t inft = it->aditional_info;
	iterator_t last = inft->last;
	return last->next(last);
}

iterator_t it_concat_2(iterator_t i1, iterator_t i2) {
	iterator_t i3,i4, i5;
	list_t lis = ls_create_d();
	ls_add(lis,i1);
	ls_add(lis,i2);
	i3 = it_from_list(lis);
	i4 = it_flat(i3);
	info_concat_2_t info = createInfoConcat2(i4, i3, lis);
	i5 = it_create(0, hasNextConcat, nextConcat, peekConcat, free_concat_2, info);
	return i5;
}


iterator_t it_concat_3(iterator_t i1, iterator_t i2, iterator_t i3) {
	iterator_t i4,i5,i6;
	list_t lis = ls_create_d();
	ls_add(lis,i1);
	ls_add(lis,i2);
	ls_add(lis,i3);
	i4 = it_from_list(lis);
	i5 = it_flat(i4);
	info_concat_2_t info = createInfoConcat2(i5, i4, lis);
	i6 = it_create(0, hasNextConcat, nextConcat, peekConcat, free_concat_2, info);
	return i6;
}


iterator_t it_sort(const iterator_t it, comparator(compare)) {
	if(it->list ==NULL) {
			it->list = ls_create_d();
			ls_add_all(it->list,it);
	}
	ls_sort(it->list, compare);
	return it_from_list(it->list);
}

iterator_t it_withmem(iterator_t i1, int size_dato){
	if(i1->list ==NULL) {
		i1->list = ls_create(10, true, size_dato);
		ls_add_all(i1->list,i1);
	}
	return it_from_list(i1->list);
}

boolean ls_add_all(list_t lis, const iterator_t it) {
	assert(lis != NULL);
	boolean r = false, r0;
	while(it->hasNext(it)){
		r0 = ls_add(lis,it->next(it));
		r = r || r0;
	}
	return r;
}

void it_free(iterator_t it){
		if (it != NULL) {
			it->free_aditional_mem(it->aditional_info);
			if (it->size_dato >0) {
				free(it->next_value);
				free(it->old_next_value);
			}
			if(it->list !=NULL) {
				ls_free(it->list);
			}
			free(it);
		}
		it = NULL;
}
