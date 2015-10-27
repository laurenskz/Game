#include <stdio.h>
#include <stdlib.h>
#include <glew.h>

#include "../include/shaderCompilation.h"
#include "../include/utils.h"

int test(){
	const GLfloat diamond[16][3] = {
			{  -0.25,  0.25,-0.25  },
			{  0.25,  0.25,-0.25  },
			{  0.25, -0.25,-0.25  },
			{  -0.25, -0.25,-0.25},

			{  -0.25,  0.25,0.25  },
			{  0.25,  0.25,0.25  },
			{  0.25, -0.25,0.25  },
			{  -0.25, -0.25,0.25  },

			{ -0.25,-0.25,-0.25 },
			{-0.25,-0.25,0.25},
			{-0.25,0.25,0.25},
			{-0.25,0.25,-0.25},

			{0.25,-0.25,0.25},
			{0.25,-0.25,-0.25},
			{0.25,0.25,-0.25},
			{0.25,0.25,0.25}
	};
	const GLfloat colors[4][3] = {
		    {  1,0,0  }, /* Top left point */
		    {  0,1,0  }, /* Top Right point */
		    {  0,0,1  },/* Bottom left point */
		    {  0,0,1  }}; /* Bottom right point */
	GLuint vao, vbo, indexBuffer, vbo2;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER, 48 * sizeof(GLfloat),diamond,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER,vbo2);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat),colors,GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	GLushort indici[] = {
			0,2,1,
			2,3,0,
			4,6,5,
			6,7,4,
			8,10,9,
			10,11,8,
			12,14,13,
			14,15,12
	};
	glGenBuffers(1,&indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indici), indici,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuffer);
	return vao;
}

int getShaderProgram(char* vertexPath, char* fragmentPath){
	GLuint vertexID, fragmentID, shaderProgram;
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(vertexID, vertexPath);
	compileShader(fragmentID, fragmentPath);
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexID);
	glAttachShader(shaderProgram, fragmentID);
	glLinkProgram(shaderProgram);
	return shaderProgram;
}

int compileShader(GLuint shaderID, char* shaderPath){
	int isCompiled;
	char *shaderSource = filetobuf(shaderPath);
	glShaderSource(shaderID, 1, (const char**)&shaderSource, 0);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID,GL_COMPILE_STATUS,&isCompiled);
	if(isCompiled == GL_FALSE){
		int maxLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
		char *infolog = (char*) malloc(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, infolog);
		printf("Error compiling shader: %s\n Error log:\n%s", shaderPath, infolog);
		free(infolog);
		return 0;
	}else{
		printf("%s was succesfully compiled to run on the hardware\n", shaderPath);
		fflush(stdout);
	}
	return 1;
}

