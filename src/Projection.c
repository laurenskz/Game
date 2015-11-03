/*
 * Projection.c
 *
 *  Created on: 22 okt. 2015
 *      Author: Laurens
 */
#include "../include/Projection.h"

char activated = 0;
mat4* projection;


mat4* getProjectionMatrix(void){
	if(activated)return projection;
	mat4* matrix = calloc(1,sizeof(mat4));
	float aspecRatio = WIDTH/HEIGHT;
	matrix->data[0] = 1/(tan((FOV*RAD)/2))/aspecRatio;
	matrix->data[5] = 1/(tan((FOV*RAD)/2));
	matrix->data[10] = (-(NEAR_Z+FAR_Z))/(FAR_Z-NEAR_Z);
	matrix->data[11] = -(2*FAR_Z*NEAR_Z)/(FAR_Z-NEAR_Z);
	matrix->data[14] = -1;
	activated = 1;
	projection = matrix;
	return matrix;
}

