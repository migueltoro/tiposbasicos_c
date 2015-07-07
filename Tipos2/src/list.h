/*
 * list.h
 *
 *  Created on: May 5, 2015
 *      Author: Boss
 */

#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include "tipos.h"

typedef struct {
	int sizeType;
	char * data;
}mem_s;

typedef mem_s * mem_t;

typedef struct {
	int size;
	int sizeMax;
	void ** pointers;
	void * mem;
	tostring_function(ts_element);
	boolean withMem;
}list_s;

typedef list_s * list_t;

/*
 * A new list is created
*/
list_t ls_create_d();
/*
 * A new list is created. This list will make a copy of each item to be added
*/
list_t ls_create(int sizeMax, boolean withMem, int sizeDatum);
list_t ls_copy(list_t lis);
void ls_aditional_info(list_t lis, tostring_function(ts_element));
list_t ls_create_var_int(const int numArgs,...);
list_t ls_create_var_long(const int numArgs,...);
list_t ls_create_var_double(const int numArgs,...);
list_t ls_create_from_array(const void * datos, const int num, int sizeDatum);
int ls_size(const list_t lis);
boolean ls_isEmpty(const list_t lis);
boolean ls_add(list_t lis, const void * e);
boolean ls_add_index(list_t lis, const void * e, int index);
boolean ls_remove_index(list_t lis, int index);
void * ls_get(const list_t lis, const int index);
void * ls_get_last(const list_t lis);
void * ls_get_first(const list_t lis);
void * ls_find(const list_t lis, predicate(p));
int ls_index(list_t lis, const void * e, bipredicate(equals));
boolean ls_contains(list_t lis, void * e, bipredicate(equals));
void ls_sort(list_t lis, comparator(c));
char * ls_tostring(list_t lis, char * mem);

void ls_free(list_t lis);



#endif /* SRC_LIST_H_ */
