/*
 * tipos.h
 *
 *  Created on: Apr 27, 2015
 *      Author: Boss
 */

#ifndef SRC_TIPOS_H_
#define SRC_TIPOS_H_

/*
 * A set of basic types and functions
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <limits.h>
#include <assert.h>

#define TAM_STRING 256

/*
 * boolean type definition
*/
#define false 0
#define true 1
#define boolean int

#define supplier(s) void * (* s)(void * mem)
#define consumer(c) void (* c)(const void * e)
#define biconsumer(b) void (* b)(const void * e1, const void * e2)

#define predicate(p) boolean (* p)(const void * e)
#define bipredicate(p) boolean (* p)(const void * e1, const void * e2)
/*
 * A function that computes f(e) using the memory in mem to store the result
*/
#define function(f) void * (* f)(const void * e, void * mem)
#define bifunction(f) void * (* f)(const void * e1, const void * e2, void * mem)

#define hashcode_function(h) long (* h)(const void * e)
#define add_element_to_group_function(add)  boolean (* add)(void * group, void * e)


#define int_function(h) int (* h)(const void * e)
#define long_function(h) int (* h)(const void * e)
#define double_function(h) double (* h)(const void * e)

#define tostring_function(h) char * (* h)(const void * e, const char * mem)

#define comparator(c) int (* c)(const void * e1, const void * e2)

typedef struct {
	void *key;
	void *value;
}pair_s;

typedef pair_s * pair_t;

/* Hash a string */
unsigned long int hash(const char *key );

/*
 *
*/
char * string_tostring(const char * e, char * mem);
/*
 * Natural order on string
*/
int string_natural_order(const char * e1, const char * e2);
/*
 * Natural order on string
*/
int string_natural_order_2(const char ** e1, const char ** e2);
/*
 * Equality of two strings
*/
boolean string_equals(const char * e1, const char * e2);
/*
 * Hascode of a string
*/
long string_hashcode(const char * e2);
/*  */
char * boolean_tostring(const boolean * e, char * mem);
/*  */
char * double_tostring(const double * e, char * mem);
/*  */
int double_natural_order(const double * e1, const double * e2);
/*  */
int double_natural_order_2(const double ** e1, const double ** e2);
/*  */
boolean double_equals(const double * e1, const double * e2);
/*  */
long double_hashcode(const double * e2);
/*  */
double * double_create_s(const char * s, double * m);
/*  */
char * int_tostring(const int * e, char * mem);
/*  */
int int_natural_order(const int * e1, const int * e2);
/*  */
int int_natural_order_2(const int ** e1, const int ** e2);
/*  */
boolean int_equals(const int * e1, const int * e2);
/*  */
long int_hashcode(const int * e2);
/*  */
int * int_create_s(const char * s, int * m);
/*  */
char * long_tostring(const long * e, char * mem);
/*  */
int long_natural_order(const long * e1, const long * e2);
/*  */
int long_natural_order_2(const long ** e1, const long ** e2);
/*  */
boolean long_equals(const long * e1, const long * e2);
/*  */
long long_hashcode(const long * e2);
/*  */
long * long_create_s(const char * s, long * m);
/*  */
void * pair_get_key(pair_t e, void * mem);
/*  */
void * pair_get_value(pair_t e, void * mem);
/*  */
pair_t pair_create(const void * key, const void * value);
/*  */
boolean pair_equals(pair_t e1, pair_t e2, bipredicate(equalskey),bipredicate(equalsvalue));
/*  */
boolean pair_equals_by_key(pair_t e1, pair_t e2, bipredicate(equalskey));
/*  */
long pair_hashcode(const pair_t e, hashcode_function(h1), hashcode_function(h2));
/*  */
char * pair_tostring(pair_t e, tostring_function(ts1), tostring_function(ts2), char * mem);
/*  */
int pair_natural_order_key_value(pair_t e1, pair_t e2, comparator(key), comparator(value));
/*  */
int pair_natural_order_key_value_2(pair_t * e1, pair_t * e2, comparator(key), comparator(value));
/*  */
char * remove_eol(char * m);
#endif /* SRC_TIPOS_H_ */
