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
#include "../include/mmath.h"
#include "../include/Shaders.h"//Yeah we do things with shaders here
#include "../include/Projection.h"

#define ARRAY_EXPANSION 30
#define INITIAL_RENDERABLES 70

typedef struct Renderable{
	char inUse;
	vec3 position, rotation, scale;
	GLuint vao;
	int ibo;//Can be negative if no ibo is used.
	GLuint textureID;
	GLuint size;//The amount of vertices to draw
	Shader* shaderProgram;
} Renderable;

void renderWorld(float elapsedTime);

void worldInit(void);

void worldLogic(float elapsedTime);

int firstEmptySpot(void** array, int sizeOfElement, int* arraySize);

void addRenderable(Renderable r);

void worldDefaultRender(Renderable* r);

mat4* createModelMatrix(Renderable* r);

mat4* createMVP(Renderable* r);

void uploadMVP(Renderable* r);

char isDifferent(vec3 v);

#endif /* WORLD_H_ */
