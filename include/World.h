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


typedef struct renderable{

	GLuint vao;
	int ibo;//Can be negative if no ibo is used.
	GLuint textureID;
	GLuint size;
} renderable;

void renderWorld(float elapsedTime);

#endif /* WORLD_H_ */
