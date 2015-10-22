/*
 * Terrain.h
 *
 *  Created on: 18 okt. 2015
 *      Author: Laurens
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#define VERTICES_PER_SIDE 64
#define VERTEX_LENGTH 8;

#include <glew.h>
#include <stdio.h>
#include <stdlib.h>

void renderTerrain(float elapsedTime);
void initTerrain(void);
void generateTerrain(void);

#endif /* TERRAIN_H_ */
