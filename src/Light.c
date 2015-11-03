/*
 * Light.c
 *
 *  Created on: 3 nov. 2015
 *      Author: Laurens
 */


#include "../include/Light.h"

vec3* position;
vec3* colour;

void initLight(void){
	position = malloc(sizeof(vec3));
	position->x = 0;
	position->y = -30;
	position->z = 0;
	colour = malloc(sizeof(vec3));
	colour->x = 1;
	colour->y = 1;
	colour->z = 1;
}

vec3* getLightPosition(void){
	return position;
}

vec3* getLightColour(void){
	return colour;
}

