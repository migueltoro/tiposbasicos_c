/*
 * hashtable.c

 *
 *  Created on: Apr 27, 2015
 *      Author: Miguel Toro
 */


#include "tipos.h"
#include "list.h"
#include "iterator.h"
#include "hashtable.h"

#define RATIO 1.5
#define INITIAL_SIZE 7

/* Rehash a hash table to a new size*/
void ht_rehash(hashtable_t  hashtable, int size);

/* Insert a key-value pair into a hash table. */
void * ht_set( hashtable_t  hashtable, const void *key, const void *value );

/* Retrieve a key-value pair from a hash table. */
void * ht_get( hashtable_t  hashtable, const void *key);

int findIndexEntryWithKeyInList(hashtable_t ht, list_t lis, const char * key);

void * findEntryWithKeyInList(hashtable_t ht, list_t lis, const char * key);

/*  Index for a key in a particular hash table. */
int ht_index(hashtable_t ht, const void * key) {
	long hc = ht->hashcode(key);
	int r = hc % ht->size;
	return r;
}

pair_t createEntry(const void *key, const void *value){
	pair_t et = (pair_t) malloc(sizeof(pair_s));
	et->key = key;
	et->value = value;
	return et;
}

hashtable_t  ht_create_d(hashcode_function(hash), bipredicate(test)){
	return ht_create(INITIAL_SIZE, RATIO, hash, test);
}

/* Create a new hashtable. */
hashtable_t  ht_create(int size, double ratio, hashcode_function(hash), bipredicate(test)) {
	int i;
	hashtable_t ht = (hashtable_t) malloc(sizeof(hashtable_s));
	ht->size = size;
	ht->numKey = 0;
	ht->ratio = ratio;
	ht->equals = test;
	ht->hashcode = hash;
	ht->table = (list_t *) malloc(size*sizeof(list_t));
	for(i=0;i<size;i++){
		ht->table[i] = ls_create(3,false,0);
	}
	return ht;
}

hashtable_t  ht_copy(hashtable_t hashtable) {
	int i;
	hashtable_t ht = (hashtable_t) malloc(sizeof(hashtable_s));
	ht->size = hashtable->size;
	ht->numKey = hashtable->numKey;
	ht->ratio = hashtable->ratio;
	ht->equals = hashtable->equals;
	ht->hashcode = hashtable->hashcode;
	ht->table = (list_t *) malloc(ht->size*sizeof(list_t));
	for(i=0;i<hashtable->size;i++){
		ht->table[i] = ls_copy(ls_copy(hashtable->table[i]));
	}
	return ht;
}

void * findEntryWithKeyInList(hashtable_t ht, list_t lis, const char * key){
	int i;
	pair_t e;
	pair_t r = NULL;
	void * kf;
	for(i=0;i<lis->size;i++){
		e = ls_get(lis,i);
		kf = e->key;
		if(ht->equals(kf,key)){
			r = e;
			break;
		}
	}
	return r;
}

int findIndexEntryWithKeyInList(hashtable_t ht, list_t lis, const char * key){
	int i;
	pair_t e;
	int r = -1;
	void * kf;
	for(i=0;i<lis->size;i++){
		e = ls_get(lis,i);
		kf = e->key;
		if(ht->equals(kf,key)){
			r = i;
			break;
		}
	}
	return r;
}

/* Find a key into a hash table. */
pair_t ht_find_key( hashtable_t  hashtable,const void *key) {
	pair_t e;
	int index = ht_index(hashtable,key);
	e = findEntryWithKeyInList(hashtable,hashtable->table[index],key);
	return e;
}

void * ht_remove_key( hashtable_t  hashtable, const void *key) {
	pair_t e;
	void * r = NULL;
	int pos;
	int index = ht_index(hashtable,key);
	pos = findIndexEntryWithKeyInList(hashtable,hashtable->table[index],key);
	if(pos>=0){
		e = ls_get(hashtable->table[index],pos);
		r = e->value;
		ls_remove_index(hashtable->table[index],pos);
		hashtable->numKey = hashtable->numKey -1;
		free(e);
	}
	return r;
}


/* Insert a key-value pair into a hash table. */
void *  ht_set( hashtable_t  hashtable, const void *key, const void *value ) {
	pair_t e;
	void * r = NULL;
	int index = ht_index(hashtable,key);
	double ratio;
	e = findEntryWithKeyInList(hashtable,hashtable->table[index],key);
	if(e != NULL){
		r = e->value;
		e->value = value;
	} else {
		e = createEntry(key,value);
		ls_add(hashtable->table[index],e);
		hashtable->numKey = hashtable->numKey +1;
	}
	ratio = ((double)hashtable->numKey)/hashtable->size;
	if(ratio > hashtable->ratio){
		ht_rehash(hashtable, 2*hashtable->size);
	}
	return r;
}

/* Insert a entry of key-value pair into a hash table. */
void ht_setEntry( hashtable_t  hashtable, pair_t e){
	ht_set(hashtable,e->key,e->value);
}

/* Insert a iterator of key-value pairs into a hash table. */
void ht_set_all( hashtable_t  hashtable, iterator_t it) {
	while(it->hasNext(it)){
			ht_setEntry(hashtable,it->next(it));
	}
}


/* Retrieve a key-value pair from a hash table. */
void * ht_get( hashtable_t  hashtable, const void *key) {
	pair_t e;
	int index = ht_index(hashtable,key);
	e = findEntryWithKeyInList(hashtable,hashtable->table[index],key);
	return e;
}

/* Retrieve a list of key-value pairs of a hash table. */
list_t ht_tolist(hashtable_t  hashtable) {
	list_t r = ls_create(hashtable->size*3,false,0);
	list_t lt;
	pair_t e;
	int i,j;
	for(i=0;i<hashtable->size;i++){
		lt = hashtable->table[i];
		for (j = 0; j < lt->size; j++) {
			e = ls_get(lt,j);
			ls_add(r,e);
		}
	}
	return r;
}



/* Add a new entry, if key not found, to a hash table. */
void ht_addEntry(hashtable_t  hashtable, pair_t entry) {
	int index = ht_index(hashtable,entry->key);
	ls_add(hashtable->table[index],entry);
	hashtable->numKey = hashtable->numKey +1;
}

/* Rehash a hash table. */
void ht_rehash(hashtable_t  hashtable, int size){
	int i;
	list_t lis = ht_tolist(hashtable);
	for(i=0;i<hashtable->size;i++){
			free(hashtable->table[i]);
	}
	free(hashtable->table);
	hashtable->size = size;
	hashtable->numKey = 0;
	hashtable->table = (list_t *) malloc(size*sizeof(list_t));
	for(i=0;i<size;i++){
		hashtable->table[i] = ls_create(3,false,0);
	}
	for(i=0;i<lis->size;i++){
		pair_t e = (pair_t) ls_get(lis,i);
		ht_addEntry(hashtable,e);
	}
	ls_free(lis);
}

char * ht_tostring(hashtable_t  hashtable, tostring_function(ts), char* s){
	char temp[256];
	char * sr = temp;
	int i;
	sprintf(temp,"NumKey = %d Size = %d\n",hashtable->numKey, hashtable->size);
	strcpy(s,temp);
	strcat(s,"[");
	for(i=0;i<hashtable->size;i++){
		if(i!=0) strcat(s,"\n");
		hashtable->table[i]->ts_element = ts;
		sr = ls_tostring(hashtable->table[i],sr);
		strcat(s,sr);
	}
	strcat(s,"]");
	return s;
}

typedef struct {
	int i;
	int j;
	hashtable_t  ht;
} infoHashIt_s;

typedef infoHashIt_s * infoHashIt_t;

infoHashIt_t createInfoHashIt(hashtable_t  ht){
	infoHashIt_t inft = (infoHashIt_t) malloc(sizeof(infoHashIt_s));
	inft->i = 0;
	inft->j = 0;
	inft->ht = ht;
	return inft;
}

void free_info_ht(iterator_t it){
	if(it->aditional_info !=NULL) free(it->aditional_info);
	it->aditional_info = NULL;
}

boolean hasNextHashIt(iterator_t it){
	infoHashIt_t inft = it->aditional_info;
	int i = inft->i;
	int j = inft->j;
	hashtable_t ht = inft->ht;
	return i < ht->size && j < ls_size(ht->table[i]);
}

void * peekHashIt(iterator_t it) {
	infoHashIt_t inft = it->aditional_info;
	int i = inft->i;
	int j = inft->j;
	hashtable_t ht = inft->ht;
	return ls_get(ht->table[i],j);
}

void * nextHashIt(iterator_t it){
	infoHashIt_t inft = it->aditional_info;
	int olDi = inft->i;
	int olDj = inft->j;
	hashtable_t ht = inft->ht;
	int i = olDi;
	int j = olDj+1;
	while(true){
		if (i == ht->size ||  (i < ht->size && j < ls_size(ht->table[i])) ) {
			break;
		}
		if(j==ls_size(ht->table[i])){
			j = 0;
			i++;
		}else {
			j++;
		}
	}
	inft->i = i;
	inft->j = j;
	return ls_get(ht->table[olDi],olDj);
}

iterator_t ht_toiterator(hashtable_t  ht){
	infoHashIt_t info = createInfoHashIt(ht);
	iterator_t it = it_create(sizeof(pair_s), hasNextHashIt, nextHashIt, peekHashIt, free_info_ht, info);
	int i = 0;
	int j = 0;
	while(true){
		if (i < ht->size && j < ls_size(ht->table[i])) {
				break;
		}
		if(j==ls_size(ht->table[i])){
			j = 0;
			i++;
		}else {
			j++;
		}
	}
	info->i = i;
	info->j = j;
	return it;
}

void ht_free(hashtable_t  hashtable){
	int i,j;
	for(i=0;i<hashtable->size;i++){
		for (j = 0; j < hashtable->table[i]->size; j++) {
			free(ls_get(hashtable->table[i],j));
		}
		free(hashtable->table[i]);
	}
	free(hashtable->table);
	free(hashtable);
}
