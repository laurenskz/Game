#ifndef SHADER_COMPILATION_H
#define SHADER_COMPILATION_H
#include <glew.h>
#include <stdio.h>
#include <stdlib.h>
int test(void);
int compileShader(GLuint shaderID, char* shaderPath);
int getShaderProgram(char* vertexPath, char* fragmentPath);
#endif
