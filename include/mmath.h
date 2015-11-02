
#ifndef MATRIX_MATH
#define MATRIX_MATH

#include <glew.h>

#include "Types.h"

mat4* identityMat4(void);

mat4* multiplyMat4Mat4(mat4* matrix1,mat4* matrix2);

mat4* rotate(float x,float y,float z);

mat4* translate(float x, float y, float z);

mat4* scale(float x, float y, float z);

vec4* vec3ToVec4(vec3* vector3, float w);

vec4* multiplyMat4Vec4(mat4* matrix, vec4* vector);

void vec3PlusIs(vec3* toAdd, vec3* adding);

mat4* multiplyAllMat4Free(mat4** array,int length);

vec3* normalizeVec3(vec3* vector);

vec3* normalizeVec3Free(vec3* vector);

vec3* addVec3(vec3* vector1,vec3* vector2);

vec3* subVec3(vec3* vector1,vec3* vector2);

vec3* crossProduct(vec3* vector1,vec3* vector2);

double dotProduct(vec3* vector1, vec3* vector2);

vec3* scalarTimesVec3(vec3* vector, float scalar);

#endif
