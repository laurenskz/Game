/*
 * Terrain.c
 *
 *  Created on: 18 okt. 2015
 *      Author: Laurens
 */

#include "../include/Terrain.h"

TerrainTile* tiles;
int tilesSize;

void initTerrain(void){
	tilesSize = INITIAL_ARRAY_SIZE;
	tiles = calloc(sizeof(TerrainTile),INITIAL_ARRAY_SIZE);
	GLuint floor = textureToID("Path.jpg");
	GLuint wood = textureToID("wood.jpg");
	int i,j;
	for(i=-39;i<100;i++)
		for(j=-39;j<100;j++){
			int x = i*VERTEX_LENGTH;
			int z = -j*VERTEX_LENGTH;
			TerrainTile tile = generateTerrainTile(x,z,(i+j)%2==0?floor:wood);
			addTerrainTile(tile);
		}
}

void addTerrainTile(TerrainTile tile){
	int place = firstEmptySpot((void**)&tiles,sizeof(TerrainTile),&tilesSize);
	printf("place we got = %d\n", place);
	if(place==-1)return;//Better luck next time
	tiles[place] = tile;
}

void renderTerrain(float elapsedTime){
	int i;
	for(i=0;i<tilesSize;i++){
		if(tiles[i].inUse)
			moldDefaultRenderer(&tiles[i].mold);
	}
}

TerrainTile generateTerrainTile(GLfloat xTranslation, GLfloat zTranslation, GLuint textureID){
	int count = VERTICES_PER_SIDE*VERTICES_PER_SIDE;
	GLfloat* vertices = malloc(sizeof(GLfloat)*count*3);
	GLfloat* normals = malloc(sizeof(GLfloat)*count*3);
	GLfloat* textureCoords = malloc(sizeof(GLfloat)*count*2);
	int indexCount = 6*(VERTICES_PER_SIDE-1)*(VERTICES_PER_SIDE-1);
	GLuint* indices = malloc(sizeof(GLuint)*indexCount);
	int x , z, vertexPointer = 0;
	for(x=0;x<VERTICES_PER_SIDE;x++){
		for(z=0;z<VERTICES_PER_SIDE;z++){
			vertices[vertexPointer*3] = ((float)x/((float)VERTICES_PER_SIDE - 1)) * VERTEX_LENGTH;
			vertices[vertexPointer*3] -= xTranslation;
			vertices[vertexPointer*3+1] = z>0&&z<VERTICES_PER_SIDE-1&&x>0&&x<VERTICES_PER_SIDE-1?1:0;
			vertices[vertexPointer*3+2] = ((float)z/((float)VERTICES_PER_SIDE - 1)) * VERTEX_LENGTH;
			vertices[vertexPointer*3+2] -= zTranslation;
			normals[vertexPointer*3] = 0;
			normals[vertexPointer*3+1] = 1;
			normals[vertexPointer*3+2] = 0;
			textureCoords[vertexPointer*2] = (float)x/((float)VERTICES_PER_SIDE - 1);
			textureCoords[vertexPointer*2+1] = (float)z/((float)VERTICES_PER_SIDE - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	int gz,gx;
	for(gz=0;gz<VERTICES_PER_SIDE-1;gz++){
		for(gx=0;gx<VERTICES_PER_SIDE-1;gx++){
			GLuint topLeft = (gz*VERTICES_PER_SIDE)+gx;
			GLuint topRight = topLeft + VERTICES_PER_SIDE;
			GLuint bottomLeft = topLeft+1;
			GLuint bottomRight = topRight + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	int vertexNormalCount = count*3;
	TerrainTile tile;
	loadToVAO(&tile.mold,(PointerWithSize) {vertices,vertexNormalCount},
		(PointerWithSize) {normals,vertexNormalCount},(PointerWithSize) {textureCoords,count*2}, (PointerWithSize) {indices,indexCount});
	tile.inUse=1;
	tile.mold.iboMode = GL_UNSIGNED_INT;
	tile.mold.shaderProgram = getBasicShader();
	tile.mold.size = indexCount;
	tile.mold.textureID = textureID;//For testing we give it a simple texture
	tile.position = (vec3){xTranslation,0,zTranslation};//We do not want to specify any height here.
	free(vertices);
	free(normals);
	free(textureCoords);
	free(indices);
	return tile;
}



