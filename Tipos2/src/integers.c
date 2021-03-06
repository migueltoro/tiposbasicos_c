/*
 * integers.c

 *
 *  Created on: May 17, 2015
 *      Author: Miguel Toro
 */

#include "integers.h"


	/**
	 * @param a Un entero
	 * @return Si es par
	 */
	boolean esPar(int a){
		return a%2 == 0;
	}

	/**
	 * @param a Un entero
	 * @return Si es impar
	 */
	boolean esImpar(int a){
		return !esPar(a);
	}

	/**
	 * @param a Un entero
	 * @param b Un segundo entero
	 * @return Si a es divisible por b
	 */

	boolean esDivisible_int(int a, int b){
		return (a%b) == 0;
	}

	boolean esDivisible_long(long a, long b){
		return (a%b) == 0;
	}
	/**
	 * @param a Un entero
	 * @return Si a es primo
	 */

	boolean esPrimo(long a){
		long sq = (long) sqrt((double)a);
		long i;
		boolean r = false;
		for (i = 2; i <= sq; i++) {
				r = esDivisible_long(a, i);
				if(r) break;
		}
		return !r;
	}

	/**
	 * @param a Un entero
	 * @return Siguiente primo
	 */

	long siguientePrimo(long a){
		long x;
		for(x=a+1;true;x=x+1){
			if(esPrimo(x)) break;
		}
		return x;
	}

	/**
	 * @pre b &gt; a
	 * @param a L�mite inferior
	 * @param b L�mite Superior
	 * @return Un entero aleatorio r tal que a &le; = r &lt; b
	 */

	int getEnteroAleatorio(int a, int b){
	    	long valor;
	    	if(b-a == 1){
	    		valor = a;
	    	}else{
	    		valor = a+rand()%(b-a);
	    	}
	    	return valor;
	}

	/**
	 * @pre b &gt; a
	 * @param a L�mite inferior
	 * @param b L�mte Superior
	 * @return Un double aleatorio que  est� en el intervalo  a &le; = r &lt; b
	 */
	double getDoubleAleatorio(double a, double b){
	    double r = ((double)getEnteroAleatorio(0,1000))/1000.;
		r = a+(b-a)*r;
	    return r;
	}

	/**
		 * @param a Un entero
		 * @param b Un segundo entero
		 * @return Calcula el m�ximo com�n divisor de los valores ablsolutos de los par�metros
		 */
		int mcd(int a, int b){
		       int u = abs(a);
		       int v = abs(b);
		       int r;
		       while (v != 0) {
		            r = u % v;
		            u = v;
		            v = r;
		       }
			    return u;
		}
