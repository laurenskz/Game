/*
 * Terrain.c
 *
 *  Created on: 18 okt. 2015
 *      Author: Laurens
 */

#include "../include/Terrain.h"



void initTerrain(void){

}



void renderTerrain(float elapsedTime){

}

void generateTerrain(GLfloat xTranslation, GLfloat zTranslation){
	int count = VERTICES_PER_SIDE*VERTICES_PER_SIDE;
	GLfloat* vertices = malloc(sizeof(GLfloat)*count*3);
	GLfloat* normals = malloc(sizeof(GLfloat)*count*3);
	GLfloat* textureCoords = malloc(sizeof(GLfloat)*count*2);
	GLuint* indices = malloc(sizeof(GLuint)*6*(VERTICES_PER_SIDE-1)*(VERTICES_PER_SIDE-1));
	int x = 0, y = 0, vertexPointer = 0;
	for(;x<VERTICES_PER_SIDE;x++)
		for(;y<VERTICES_PER_SIDE;y++){
			vertices[vertexPointer*3] = (float)y/((float)VERTICES_PER_SIDE - 1) * VERTEX_LENGTH;
			vertices[vertexPointer*3] += xTranslation;
			vertices[vertexPointer*3+1] = 0;
			vertices[vertexPointer*3+2] = (float)x/((float)VERTICES_PER_SIDE - 1) * VERTEX_LENGTH;
			vertices[vertexPointer*3+2] += zTranslation;
			normals[vertexPointer*3] = 0;
			normals[vertexPointer*3+1] = 1;
			normals[vertexPointer*3+2] = 0;
			textureCoords[vertexPointer*2] = (float)y/((float)VERTICES_PER_SIDE - 1);
			textureCoords[vertexPointer*2+1] = (float)x/((float)VERTICES_PER_SIDE - 1);
			vertexPointer++;
		}
}



