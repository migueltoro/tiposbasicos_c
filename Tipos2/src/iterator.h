/*
 * iterator.h

 *
 *  Created on: Apr 29, 2015
 *      Author: Miguel Toro
 */

#ifndef SRC_ITERATOR_H_
#define SRC_ITERATOR_H_

#include "tipos.h"
#include "list.h"


struct iterator_s {
	int size_dato;
	void * next_value;
	void * old_next_value;
	boolean ( * hasNext) (struct iterator_s *);
	void * ( * next) (struct iterator_s *);
	void * ( * peek) (struct iterator_s *);
	void ( * free_aditional_mem ) (void *);
	void * aditional_info;
	list_t list;
};

typedef struct iterator_s * iterator_t;

iterator_t it_create(int sizeDato,
		boolean ( * hasNext) (iterator_t),
		void * ( * next) (iterator_t),
		void * ( * peek) (iterator_t),
		void ( * free_aditional_mem) (void *),
		void * info);

/*
 * @return Abstract definition of a function that returns a iterator from an aggregate
*/
#define iterator_from_function(it_from)   iterator_t ( * it_from) (void * aggregate)
/*
 * @pre c != 0
 * @return An iterator with int values a, a+c, a+2c, ... while a+ic < b (if c > 0) or a+ic > b (if c<0)
*/
iterator_t it_range_int(int a, int b, int c);
/*
 * @pre c != 0
 * @return An iterator with long values a, a+c, a+2c, ... while a+ic < b (if c > 0) or a+ic > b (if c<0)
*/
iterator_t it_range_long(long a, long b, long c);
/*
 * @pre c != 0
 * @return An iterator with double values a, a+c, a+2c, ... while a+ic < b (if c > 0) or a+ic > b (if c<0)
*/
iterator_t it_range_double(double a, double b, double c);
/*
 * @return An iterator over an infinite sequence of values e0, e1, ... with e0 = s() and ei+1 = f(ei) and size of each data size_dato
*/
iterator_t it_sequence(supplier(s),function(f),int size_dato);
/*
 * @return An iterator over an array d of size n and size of each data size_dato
*/
iterator_t it_from_array(const void * d, int n, int size_dato);
/*
 * @return An iterator over a list values
*/
iterator_t it_from_list(list_t lis);
/*
 * @return An iterator over a file. Each data is a string
*/
iterator_t it_from_file(char * file);
/*
 * @return An iterator over data in ib verifying p
*/
iterator_t it_filter(const iterator_t ib, predicate(p));
/*
 * @return An iterator over ib values transformed by f
*/
iterator_t it_transform(const iterator_t ib, function(f), int sizeDato);
/*
 * @return An iterator over the first numvalues of ib
*/
iterator_t it_limit(const iterator_t ib, long numvalues);
/*
 * @return An iterator over the ib values until one that does not verify p
*/
iterator_t it_while(const iterator_t it, predicate(p));
/*
 * @return An iterator over the values in ib sorted by c
*/
iterator_t it_sort(const iterator_t it, comparator(c));
/*
 * @return An iterator over the values in the sequence of iterators seq
*/
iterator_t it_flat(const iterator_t seq);
/*
 * @return An iterator over the values in i1 and then i2
*/
iterator_t it_concat_2(iterator_t i1, iterator_t i2);
/*
 * @return An iterator over the values in i1, then i2 and then i3
*/
iterator_t it_concat_3(iterator_t i1, iterator_t i2, iterator_t i3);
/*
 * @return An iterator over the ib values and getting new memory for all of them
*/
iterator_t it_withmem(iterator_t ib, int size_dato);
/*
 * Add the iterator values on the list and return true if the list has been modified
*/
boolean ls_add_all(list_t lista, const iterator_t it);
/*
 * Free the iterator memory
*/
void it_free(iterator_t it);

#endif /* SRC_ITERATOR_H_ */
