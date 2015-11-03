/*
 * Shaders.c
 *
 *  Created on: 22 okt. 2015
 *      Author: Laurens
 */

#include "../include/Shaders.h"

Shader* basicShader;
Shader* modelShader;

void loadAllShaders(void){
	basicShader = loadShader(getShaderProgram("Shaders/basicShader.vert", "Shaders/basicShader.frag"));
	modelShader = loadShader(getShaderProgram("Shaders/modelShader.vert", "Shaders/modelShader.frag"));
}


Shader* loadShader(int id){
	Shader* toRet = malloc(sizeof(Shader));
	toRet->id = id;
	toRet->MVPLocation = glGetUniformLocation(id,"mvp");
	toRet->lightColourLocation = glGetUniformLocation(id,"lightColour");
	toRet->lightPositionLocation = glGetUniformLocation(id,"lightPosition");
	toRet->modelMLocation = glGetUniformLocation(id,"modelMatrix");
	uploadLights(toRet);
	return toRet;
}


void uploadLights(Shader* shader){
	glUseProgram(shader->id);
	vec3* pos = getLightPosition();
	vec3* colour = getLightColour();
	glUniform3f(shader->lightColourLocation,colour->x,colour->y,colour->z);
	glUniform3f(shader->lightPositionLocation,pos->x,pos->y,pos->z);
}

Shader* getBasicShader(void){
	return basicShader;
}

Shader* getModelShader(void){
	return modelShader;
}
