/*
 * integers.h
 *
 *  Created on: May 17, 2015
 *      Author: Boss
 */

#ifndef SRC_INTEGERS_H_
#define SRC_INTEGERS_H_

#include "tipos.h"
	/**
	 * @param a Un entero
	 * @return Si es par
	 */
	boolean esPar(int a);
	/**
	 * @param a Un entero
	 * @return Si es impar
	 */
	boolean esImpar(int a);
	/**
	* @param a Un entero
	* @param b Un segundo entero
	* @return Si a es divisible por b
	*/
	boolean esDivisible_int(int a, int b);
	boolean esDivisible_long(long a, long b);
	/**
	* @param a Un entero
	* @return Si a es primo
	*/
	boolean esPrimo(long a);
	/**
	* @param a Un entero
	* @return Siguiente primo
	*/
	long siguientePrimo(long a);
	/**
	* @pre b &gt; a
	* @param a L�mite inferior
	* @param b L�mite Superior
	* @return Un entero aleatorio r tal que a &le; = r &lt; b
	*/
	int getEnteroAleatorio(int a, int b);
	/**
	* @pre b &gt; a
	* @param a L�mite inferior
	* @param b L�mte Superior
	* @return Un double aleatorio que  est� en el intervalo  a &le; = r &lt; b
	*/
	double getDoubleAleatorio(double a, double b);
	/**
	* @param a Un entero
	* @param b Un segundo entero
	* @return Calcula el m�ximo com�n divisor de los valores ablsolutos de los par�metros
	*/
	int mcd(int a, int b);


#endif /* SRC_INTEGERS_H_ */
