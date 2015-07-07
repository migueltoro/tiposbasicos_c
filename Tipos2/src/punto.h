/*
 * punto.h
 *
 *  Created on: May 21, 2015
 *      Author: Boss
 */

#ifndef SRC_PUNTO_H_
#define SRC_PUNTO_H_

#include "tipos.h"

typedef struct {
	double x;
	double y;
} punto_s;

typedef punto_s * punto_t;

typedef enum {PRIMERO,SEGUNDO,TERCERO,CUARTO} Cuadrante;

punto_t pt_create_s(char * s, punto_t p);
punto_t pt_create_2(punto_t p, double x, double y);
double pt_getx(const punto_t p);
void pt_setx(punto_t p, double x);
double pt_gety(const punto_t p);
void pt_sety(punto_t p, double y);
double pt_distancia_al_origen(const punto_t p);
char * pt_tostring(const punto_t p, char * m);
int pt_ord_distancia_al_origen(const punto_t p1, const punto_t p2);
int pt_ord_distancia_al_origen_2(const  punto_t * e1, const punto_t * e2);
boolean pt_equals(const punto_t p1, const punto_t p2);
long pt_hashcode(const punto_t p);
Cuadrante pt_cuadrante(const punto_t p);

#endif /* SRC_PUNTO_H_ */
