/*
 * punto.c

 *
 *  Created on: May 21, 2015
 *      Author: Miguel Toro
 */


#include "punto.h"

punto_t pt_create_s(char * m, punto_t p){
	sscanf(m,"%lf,%lf",&p->x,&p->y);
	return p;
}
punto_t pt_create_2(punto_t p, double x, double y){
	p->x=x;
	p->y=y;
	return p;
}

double pt_getx(const punto_t p){
	return p->x;
}
void pt_setx(punto_t p, double x){
	p->x=x;
}
double pt_gety(const punto_t p){
	return p->y;
}
void pt_sety(punto_t p, double y){
	p->y=y;
}
double pt_distancia_al_origen(const punto_t p){
	double x2 = p->x*p->x;
	double y2 = p->y*p->y;
	return sqrt(x2+y2);
}
char * pt_tostring(const punto_t p, char * m){
	sprintf(m,"(%lf,%lf)",p->x,p->y);
	return m;
}

int pt_ord_distancia_al_origen(const  punto_t p1, const punto_t p2){
	double r1 = pt_distancia_al_origen(p1);
	double r2 = pt_distancia_al_origen(p2);
	int r;
	if(r1 < r2) r = -1;
	if(r1 > r2) r = 1;
	if( r1 == r2) r = 0;
	return r;
}

int pt_ord_distancia_al_origen_2(const  punto_t * e1, const punto_t * e2){
	punto_t p1 = * e1;
	punto_t p2 = * e2;
	double r1 = pt_distancia_al_origen(p1);
	double r2 = pt_distancia_al_origen(p2);
	int r;
	if(r1 < r2) r = -1;
	if(r1 > r2) r = 1;
	if( r1 == r2) r = 0;
	return r;
}

boolean pt_equals(const punto_t p1, const punto_t p2){
	return p1->x == p2->x && p1->y == p2->y;
}

long pt_hashcode(const punto_t p){
	char mem[TAM_STRING];
	char * s = pt_tostring(p,mem);
	return hash(s);
}

Cuadrante pt_cuadrante(const punto_t p) {
	Cuadrante r;
	if(p->x >=0 && p->y>=0){
		r = PRIMERO;
	} else if(p->x < 0 && p->y>=0) {
		r = SEGUNDO;
	} else if(p->x < 0 && p->y<0) {
		r = TERCERO;
	} else {
		r = CUARTO;
	}
	return r;
}
