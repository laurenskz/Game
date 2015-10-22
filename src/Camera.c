#include <stdio.h>
#include <stdlib.h>
#include <glew.h>
#include <glfw3.h>
#include "../include/Camera.h"
#include "../include/mmath.h"
#include <math.h>
#include "../include/main.h"

#define RAD 0.01745329251
#define DIFFERENCE_TO_ANGLE 0.03f
#define SPEED 6.0

vec3* position;
vec3* lookat;
vec3* upVector;
char * keys;
float xAngle, yAngle = 0;

void cameraInit(void){
	position = malloc(sizeof(vec3));
	lookat = malloc(sizeof(vec3));
	upVector = malloc(sizeof(vec3));
	(*position) = (vec3) {0,0,0};
	(*lookat) = (vec3) {0,0,-1};
	(*upVector) = (vec3) {0,1,0};
}

void cameraLogic(float elapsedTime){
	float speed = elapsedTime*SPEED;
	vec3* direction = normalizeVec3Free(subVec3(lookat,position));
	vec3* timed = scalarTimesVec3(direction,speed);
	vec3* negative = scalarTimesVec3(timed, -1);

	if(keys[GLFW_KEY_W]){
		vec3PlusIs(position,timed);
		vec3PlusIs(lookat,timed);
	}
	if(keys[GLFW_KEY_S]){
		vec3PlusIs(position,negative);
		vec3PlusIs(lookat,negative);
	}
	lookAtRecalculator();
	free(direction);
	free(timed);
	free(negative);
}

void lookAtRecalculator(void){
	if(!mouseMoved())return;
	double xDiff = mainGetMouseDiffX();
	double yDiff = mainGetMouseDiffY();
	if(xDiff==0&&yDiff==0)return;
	incrementxAngle(xDiff*DIFFERENCE_TO_ANGLE);
	incrementyAngle(yDiff*DIFFERENCE_TO_ANGLE);
	calculateLookat();
}

void calculateLookat(void){
	float y = sin(RAD*yAngle);
	float x = sin(RAD*xAngle);
	float z = sin((xAngle+90)*RAD);
	vec3 toAdd = (vec3){x,y,z};
	free(lookat);
	lookat = addVec3(position,&toAdd);
}

float calculateNegativeOrPositive(float angle){
	if(angle<0)angle = -angle;
	if(angle>360)angle = fmod(angle,360.0);
	if(angle>=0&&angle<=90)return -1.0;
	if(angle>=90&&angle<=180)return 1.0;
	if(angle>=180&&angle<=270)return 1.0;
	if(angle>=270&&angle<=360)return -1.0;
	return 1;
}


void incrementxAngle(float toAdd){
	xAngle-=toAdd;
}

void incrementyAngle(float toAdd){
	yAngle-=toAdd;
	if(yAngle>=90)yAngle = 89.9999;
	if(yAngle<=-90)yAngle = -89.9999;
}



mat4* cameraGetViewMatrix(){
	vec3* z = normalizeVec3Free(subVec3(position,lookat));
	vec3* x = normalizeVec3Free(crossProduct(upVector,z));
	vec3* y = crossProduct(z,x);
	mat4* lookatHalf = calloc(1,sizeof(mat4));
	lookatHalf->data[0] = x->x;
	lookatHalf->data[1] = y->x;
	lookatHalf->data[2] = z->x;
	lookatHalf->data[4] = x->y;
	lookatHalf->data[5] = y->y;
	lookatHalf->data[6] = z->y;
	lookatHalf->data[8] = x->z;
	lookatHalf->data[9] = y->z;
	lookatHalf->data[10] = z->z;
	lookatHalf->data[12] = -dotProduct(x,position);
	lookatHalf->data[13] = -dotProduct(y,position);
	lookatHalf->data[14] = -dotProduct(z,position);
	lookatHalf->data[15] = 1;
	return lookatHalf;
}

void cameraSetLookatX(float x){
	lookat->x = x;
}

void cameraSetLookatY(float y){
	lookat->y = y;
}

void cameraSetLookatZ(float z){
	lookat->z = z;
}
