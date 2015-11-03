/*
 * Terrain.h
 *
 *  Created on: 18 okt. 2015
 *      Author: Laurens
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#define VERTICES_PER_SIDE 4
#define VERTEX_LENGTH 10;


#include <glew.h>
#include <stdio.h>
#include <stdlib.h>
#include "World.h"

typedef struct TerrainTile{
	char inUse;
	RenderableMold mold;//There basically is just one instance for each mold of terrain.
	vec3 position;//This is here to determine if we can get rid of it already
}TerrainTile;


void renderTerrain(float elapsedTime);
void initTerrain(void);
TerrainTile generateTerrainTile(GLfloat xTranslation, GLfloat zTranslation, GLuint textureID);
void addTerrainTile(TerrainTile tile);


#endif /* TERRAIN_H_ */
