/*
 * main.c

 *
 *  Created on: Apr 27, 2015
 *      Author: Miguel Toro
 */

#include "tipos.h"
#include "list.h"
#include "hashtable.h"
#include "iterator.h"
#include "avltree.h"
#include "integers.h"
#include "punto.h"
#include "set.h"
#include "set_test.h"
#include "sortedset_test.h"
#include "iterator_test.h"



int main(){

	time_t t;
	srand(time(&t));

	iterator_test1();
	iterator_test2();
	iterator_test3();
	iterator_test4();
	iterator_test5();
	iterator_test6();
	iterator_test7();
	iterator_test8();
	iterator_test9();
	iterator_test10();

	set_test1();

	sortedset_test1();

	accumulator_test1();
	accumulator_test2();
	accumulator_test3();
	accumulator_test4();
	accumulator_test5();
	accumulator_test6();


	return 0;

 }
