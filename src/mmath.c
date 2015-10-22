#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define RAD 0.01745329251
#include "../include/mmath.h"

mat4* identityMat4(void){
	mat4* ret = calloc(1,sizeof(mat4));
	ret->data[0] = 1;
	ret->data[5] = 1;
	ret->data[10] = 1;
	ret->data[15] = 1;
	return ret;
}

mat4* multiplyMat4Mat4(mat4* matrix1,mat4* matrix2){
	mat4* newMat = calloc(1,sizeof(mat4));
	int row = 0;
	for(;row<16;row+=4){
		int column = 0;
		for(;column<4;column++){
			int counter = 0;
			float sum = 0;
			for(;counter<4;counter++){
				float product = matrix1->data[row+counter] * matrix2->data[column + counter*4];
				sum+=product;
			}
			newMat->data[row+column] = sum;
		}
	}
	return newMat;
}

mat4* rotate(float x,float y,float z){
	mat4 * xRot = calloc(1,sizeof(mat4));
	mat4 * yRot = calloc(1,sizeof(mat4));
	mat4 * zRot = calloc(1,sizeof(mat4));
	xRot->data[0] = 1;
	xRot->data[5] = (GLfloat)cos((x*RAD));
	xRot->data[6] = (GLfloat)-sin((x*RAD));
	xRot->data[9] = (GLfloat)sin((x*RAD));
	xRot->data[10] = (GLfloat)cos((x*RAD));
	xRot->data[15] = 1;
	yRot->data[0] = (GLfloat)cos((y*RAD));
	yRot->data[2] = (GLfloat)sin((y*RAD));
	yRot->data[5] = 1;
	yRot->data[8] = (GLfloat)-sin((y*RAD));
	yRot->data[10] = (GLfloat)cos((y*RAD));
	yRot->data[15] = 1;
	zRot->data[0] = (GLfloat)cos((z*RAD));
	zRot->data[1] = (GLfloat)-sin((z*RAD));
	zRot->data[4] = (GLfloat)sin((z*RAD));
	zRot->data[5] = (GLfloat)cos((z*RAD));
	zRot->data[10] = 1;
	zRot->data[15] = 1;
	mat4* xTimesY = multiplyMat4Mat4(xRot,yRot);
	mat4* final = multiplyMat4Mat4(xTimesY,zRot);
	free(xRot);
	free(yRot);
	free(zRot);
	free(xTimesY);
	return final;
}

mat4* translate(float x, float y, float z){
	mat4 *translationMatrix = identityMat4();
	translationMatrix->data[12] = x;
	translationMatrix->data[13] = y;
	translationMatrix->data[14] = z;
	return translationMatrix;
}

mat4* scale(float x, float y, float z){
	mat4 *translationMatrix = identityMat4();
	translationMatrix->data[0] = x;
	translationMatrix->data[5] = y;
	translationMatrix->data[10] = z;
	translationMatrix->data[15] = 1;
	return translationMatrix;
}

vec4* vec3ToVec4(vec3* vector3, float w){
	vec4* vector4 = malloc(sizeof(vector4));
	vector4->x = vector3->x;
	vector4->y = vector3->y;
	vector4->z = vector3->z;
	vector4->z = 1;
	return vector4;
}

vec4* multiplyMat4Vec4(mat4* matrix, vec4* vector){
	vec4* newVector = malloc(sizeof(vec4));
	int i = 0;
	for(;i<16;i+=4){
		float sum = 0;
		sum+=matrix->data[i]*vector->x;
		sum+=matrix->data[i+1]*vector->y;
		sum+=matrix->data[i+2]*vector->z;
		sum+=matrix->data[i+3]*vector->w;
		if(i==0)newVector->x=sum;
		if(i==4)newVector->y=sum;
		if(i==8)newVector->z=sum;
		if(i==12)newVector->w=sum;
	}
	return newVector;
}

void vec3PlusIs(vec3* toAdd, vec3* adding){
	toAdd->x+=adding->x;
	toAdd->y+=adding->y;
	toAdd->z+=adding->z;
}

mat4* multiplyAllMat4Free(mat4** array,int length){
	mat4* initial = multiplyMat4Mat4(array[0],array[1]);
	free(array[0]);
	free(array[1]);
	int i = 2;
	for(;i<length;i++){
		mat4* secondary = multiplyMat4Mat4(initial,array[i]);
		free(initial);
		initial = secondary;
	}
	free(array);
	return initial;
}

vec3* normalizeVec3(vec3* vector){
	vec3* toRet = malloc(sizeof(vec3));
	double length = sqrt((vector->x*vector->x)+(vector->y*vector->y)+(vector->z*vector->z));
	toRet->x = vector->x/length;
	toRet->y = vector->y/length;
	toRet->z = vector->z/length;
	return toRet;
}

vec3* addVec3(vec3* vector1,vec3* vector2){
	vec3* toReturn = malloc(sizeof(vec3));
	toReturn->x = vector1->x+vector2->x;
	toReturn->y = vector1->y+vector2->y;
	toReturn->z = vector1->z+vector2->z;
	return toReturn;
}

vec3* subVec3(vec3* vector1,vec3* vector2){
	vec3* toReturn = malloc(sizeof(vec3));
	toReturn->x = vector1->x-vector2->x;
	toReturn->y = vector1->y-vector2->y;
	toReturn->z = vector1->z-vector2->z;
	return toReturn;
}

vec3* normalizeVec3Free(vec3* vector){
	vec3* toReturn = normalizeVec3(vector);
	free(vector);
	return toReturn;
}

double dotProduct(vec3* vector1, vec3* vector2){
	return vector1->x*vector2->x+vector1->y*vector2->y+vector1->z*vector2->z;
}

vec3* crossProduct(vec3* vector1,vec3* vector2){
	vec3* toReturn = malloc(sizeof(vec3));
	toReturn->x = (vector1->y*vector2->z)-(vector1->z*vector2->y);
	toReturn->y = (vector1->z*vector2->x)-(vector1->x*vector2->z);
	toReturn->z = (vector1->x*vector2->y)-(vector1->y*vector2->x);
	return toReturn;
}

vec3* scalarTimesVec3(vec3* vector, float scalar){
	vec3* toRet = malloc(sizeof(vec3));
	toRet->x = vector->x*scalar;
	toRet->y = vector->y*scalar;
	toRet->z = vector->z*scalar;
	return toRet;
}
