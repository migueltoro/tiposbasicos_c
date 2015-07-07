/*
 * tipos.c

 *
 *  Created on: Apr 29, 2015
 *      Author: Miguel Toro
 */

#include "tipos.h"

/* Hash a string */
unsigned long int hash(const char *key ) {

	unsigned long int hashval = 0 ;
	int i = 0;
	/* Convert our string to an integer */
	while( hashval < ULONG_MAX && i < strlen( key ) ) {
//		hashval = hashval << 5;
		hashval += key[ i ];
		i++;
	}
	return hashval;
}

char * string_tostring(const char * e, char * mem){
	strcpy(mem,e);
	return mem;
}

int string_natural_order(const char * e1, const char * e2){
	return strcmp(e1,e2);
}

int string_natural_order_2(const char ** e1, const char ** e2){
	char * r1 = * e1;
	char * r2 = * e2;
	return strcmp(r1,r2);
}

boolean string_equals(const char * e1, const char * e2) {
	return strcmp(e1,e2) == 0;
}

long string_hashcode(const char * e){
	return hash(e);
}

char * boolean_tostring(const boolean * e, char * mem){
	boolean a = * e;
	if(a) strcpy(mem,"true");
	else strcpy(mem,"false");
	return mem;
}

char * double_tostring(const double * e, char * mem){
	double a = * e;
	sprintf(mem,"%lf",a);
	return mem;
}

int double_natural_order(const double * e1, const double * e2){
	int r;
	double r1 = *  e1;
	double r2 = *  e2;
	if(r1 < r2) r = -1;
	if(r1 > r2) r = 1;
	if( r1 == r2) r = 0;
	return r;
}

int double_natural_order_2(const double ** e1, const double ** e2){
	int r;
	double r1 = **  e1;
	double r2 = **  e2;
	if(r1 < r2) r = -1;
	if(r1 > r2) r = 1;
	if( r1 == r2) r = 0;
	return r;
}

boolean double_equals(const double * e1, const double * e2){
	double r1 = *  e1;
	double r2 = *  e2;
	return r1 == r2;
}

long double_hashcode(const double * e) {
	char mem[TAM_STRING];
	char * s = double_tostring(e,mem);
	return hash(s);
}

double * double_create_s(const char * s, double * m){
	* m = atof(s);
	return m;
}

char * int_tostring(const int * e, char * mem){
	int a = * e;
	sprintf(mem,"%d",a);
	return mem;
}

int int_natural_order(const int * e1, const int * e2){
	int r;
	int r1 = *  e1;
	int r2 = *  e2;
	if(r1 < r2) r = -1;
	if(r1 > r2) r = 1;
	if( r1 == r2) r = 0;
	return r;
}

int int_natural_order_2(const int ** e1, const int ** e2){
	int r;
	int r1 = **  e1;
	int r2 = **  e2;
	if(r1 < r2) r = -1;
	if(r1 > r2) r = 1;
	if( r1 == r2) r = 0;
	return r;
}

boolean int_equals(const int * e1, const int * e2){
	int r1 = *  e1;
	int r2 = *  e2;
	return r1 == r2;
}

long int_hashcode(const int * e){
	return *e;
}

int * int_create_s(const char * s, int * m){
	* m = atoi(s);
	return m;
}

char * long_tostring(const long * e, char * mem){
	long a = * e;
	sprintf(mem,"%ld",a);
	return mem;
}

int long_natural_order(const long * e1, const long * e2){
	int r;
	long r1 = *  e1;
	long r2 = *  e2;
	if(r1 < r2) r = -1;
	if(r1 > r2) r = 1;
	if( r1 == r2) r = 0;
	return r;
}

int long_natural_order_2(const long ** e1, const long ** e2){
	int r;
	long r1 = **  e1;
	long r2 = **  e2;
	if(r1 < r2) r = -1;
	if(r1 > r2) r = 1;
	if( r1 == r2) r = 0;
	return r;
}
boolean long_equals(const long * e1, const long * e2){
	long r1 = *  e1;
	long r2 = *  e2;
	return r1 == r2;
}

long long_hashcode(const long * e){
	return *e;
}

long * long_create_s(const char * s, long * m){
	* m = atoll(s);
	return m;
}

void * pair_get_key(pair_t e, void * mem) {
	return e->key;
}

void * pair_get_value(pair_t e, void * mem) {
	return e->value;
}

pair_t pair_create(const void * key, const void * value) {
	pair_t p = malloc(sizeof(pair_s));
	p->key = key;
	p->value = value;
	return p;
}

boolean pair_equals(pair_t e1, pair_t e2, bipredicate(p1),bipredicate(p2)) {
	return p1(e1->key,e2->key) && p2(e1->value,e2->value);
}

boolean pair_equals_by_key(pair_t e1, pair_t e2, bipredicate(p1)) {
	return p1(e1->key,e2->key);
}

long pair_hashcode(const pair_t e, hashcode_function(h1), hashcode_function(h2)) {
	return h1(e->key)+27*h2(e->value);
}

char * pair_tostring(pair_t e, tostring_function(tskey), tostring_function(tsvalue), char * mem) {
	char m[TAM_STRING];
	char * s;
	strcpy(mem,"(");
	s = tskey(e->key,m);
	strcat(mem,s);
	strcat(mem,",");
	s = tsvalue(e->value,m);
	strcat(mem,s);
	strcat(mem,")");
	return mem;
}

int pair_natural_order_key_value(pair_t e1, pair_t e2, comparator(key), comparator(value)) {
	int r = key(e1->key,e2->key);
	if(r==0) r = value(e1->value,e2->value);
	return r;
}

int pair_natural_order_key_value_2(pair_t * p1, pair_t * p2, comparator(key), comparator(value)) {
	pair_t e1 = * p1;
	pair_t e2 = * p2;
	int r = key(e1->key,e2->key);
	if(r==0) r = value(e1->value,e2->value);
	return r;
}

char * remove_eol(char * m){
	int len = strlen(m);
	if (len>0) {
		m[len-1] = '\0';
	}
	return m;
}
