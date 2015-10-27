/*
 * World.h
 *
 *  Created on: 18 okt. 2015
 *      Author: Laurens
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>//Want NULL

#include "../include/Camera.h"

#define ARRAY_EXPANSION 70

typedef struct renderable{

	GLuint vao;
	int ibo;//Can be negative if no ibo is used.
	GLuint textureID;
	GLuint size;
} renderable;

void renderWorld(float elapsedTime);

void worldInit(void);

void worldLogic(float elapsedTime);

int firstEmptySpot(void** array, int sizeOfElement, int* arraySize);

#endif /* WORLD_H_ */
