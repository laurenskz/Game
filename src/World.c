/*
 * World.c
 *
 *  Created on: 18 okt. 2015
 *      Author: Laurens
 */

#include "../include/World.h"

Renderable* renderables;
int renderablesSize;

void worldInit(void){
	cameraInit();
	renderablesSize = INITIAL_RENDERABLES;
	renderables = calloc(sizeof(Renderable),renderablesSize);
}

void addRenderable(Renderable r){
	int place = firstEmptySpot((void**)&renderables,sizeof(Renderable),&renderablesSize);
	if(place==-1)return;//better luck next time
	renderables[place] = r;//Now it is stored in the array
}

void worldLogic(float elapsedTime){
	cameraLogic(elapsedTime);
}

void renderWorld(float elapsedTime){
	int i;
	for(i=0;i<renderablesSize;i++){

	}
}

void setShaderUploadMVP(Renderable* r){
	glUseProgram(r->shaderProgram->id);
		mat4* mvp = createMVP(r);
		glUniformMatrix4fv(r->shaderProgram->MVPLocation,1,GL_FALSE,mvp);
		free(mvp);
}

void worldDefaultRender(Renderable* r){

	if()

}

mat4* createMVP(Renderable* r){
	mat4* model = createModelMatrix(r);
	mat4 *projection = getProjectionMatrix(), *viewMatrix = cameraGetViewMatrix();
	if(model==NULL){
		return multiplyMat4Mat4(viewMatrix,projection);//These don't have to be freed by us. Which is nice
	}
	mat4* first = multiplyMat4Mat4(model,viewMatrix);
	free(model);
	mat4* second = multiplyMat4Mat4(first,projection);
	free(first);
	return second;
}

mat4* createModelMatrix(Renderable* r){
	mat4* toReturn = NULL;
	if(isDifferent(r->scale)){

		mat4* scaleMatrix = scale(r->scale.x,r->scale.y,r->scale.z);

		if(isDifferent(r->rotation)){
			mat4* rotation = rotate(r->rotation.x,r->rotation.y,r->rotation.z);
			mat4* combined = multiplyMat4Mat4(scaleMatrix,rotation);
			free(scaleMatrix);
			free(rotation);
			if(isDifferent(r->position)){
				mat4* position = translate(r->position.x,r->position.y,r->position.z);
				toReturn = multiplyMat4Mat4(combined,position);
				free(position);
				free(combined);
				return toReturn;
			}else{
				return combined;
			}

		}else if(isDifferent(r->position)){
			mat4* position = translate(r->position.x,r->position.y,r->position.z);
			toReturn = multiplyMat4Mat4(scaleMatrix,position);
			free(position);
			free(scaleMatrix);
			return toReturn;
		}else{
			return scaleMatrix;
		}

	}else if(isDifferent(r->rotation)){
		mat4* rotation = rotate(r->rotation.x,r->rotation.y,r->rotation.z);
		if(isDifferent(r->position)){
			mat4* position = translate(r->position.x,r->position.y,r->position.z);
			toReturn = multiplyMat4Mat4(rotation,position);
			free(position);
			free(rotation);
			return toReturn;
		}else{
			return rotation;
		}
	}else if(isDifferent(r->position)){
		return translate(r->position.x,r->position.y,r->position.z);
	}
	return toReturn;
}

char isDifferent(vec3 v){
	return v.x!=0||v.y!=0||v.z!=0;
}

int firstEmptySpot(void** array, int sizeOfElement, int* arraySize){
	void * data = *array;
	int i = 0;
	for(;i<(*arraySize);i++){
		if(!*((char*)(data+(i*sizeOfElement)))){
			return i;
		}
	}
	printf("i = %d",i);
	int toRet = *arraySize;//We already know that this is the position it is going to be (size of old array)
	(*arraySize)+=ARRAY_EXPANSION;
	void* newP = realloc(*array,(*arraySize)*sizeOfElement);
	if(newP==NULL){
		return -1;
	}
	*array = newP;
	//Now that we made the array bigger we have to make sure the next spots are marked as empty
	i++;//Don't mark the spot we want to return as free
	for(;i<(*arraySize);i++){
		*((char*)(newP+(i*sizeOfElement))) = 7;
	}
	return toRet;
}

