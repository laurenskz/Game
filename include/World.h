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

#include "Types.h"
#include "../include/Camera.h"
#include "../include/mmath.h"
#include "../include/Shaders.h"//Yeah we do things with shaders here
#include "../include/Projection.h"
#include "OBJLoader.h"
#include "textureLoader.h"
#include "WorldPopulater.h"
#include "Light.h"
#include "Terrain.h"

#define ARRAY_EXPANSION 30
#define INITIAL_ARRAY_SIZE 70



void renderWorld(float elapsedTime);

void worldInit(void);

void worldLogic(float elapsedTime);

int firstEmptySpot(void** array, int sizeOfElement, int* arraySize);

void addRenderable(Renderable r);

void worldDefaultRender(Renderable* r);

mat4* createModelMatrix(Renderable* r);

mat4* createMVP(Renderable* r);

void setShaderUploadMVP(Renderable* r);

void drawCall(RenderableMold* r);

void setShaderuploadVP(RenderableMold* r);

void uploadMVP(Renderable* r);

char isDifferent(vec3 v);

RenderableMold* loadRenderableMold(char* objFilePath, char* texture);

void moldDefaultRenderer(RenderableMold* r);

#endif /* WORLD_H_ */
