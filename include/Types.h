/*
 * Types.h
 *
 *  Created on: 2 nov. 2015
 *      Author: Laurens
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <glew.h>

typedef struct vec2{
	GLfloat x;
	GLfloat y;
} vec2;

typedef struct vec3{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} vec3;

typedef struct vec4{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
} vec4;

typedef struct mat4{
	GLfloat data[16];
} mat4;

typedef struct PointerWithSize{
	GLvoid* data;
	GLsizeiptr size;
}PointerWithSize;

typedef struct Shader{
	GLuint id;
	int MVPLocation;
	int lightPositionLocation;
	int lightColourLocation;
	int modelMLocation;
} Shader;

typedef struct RenderableMold{
	GLuint vao;
	GLuint textureID;
	GLuint size;//The amount of vertices to draw
	int iboMode;//if -1 dont use it
	int ibo;
	Shader* shaderProgram;
} RenderableMold;

typedef struct Renderable{
	char inUse;
	vec3 position, rotation, scale;
	RenderableMold* mold;
} Renderable;



#endif /* TYPES_H_ */
