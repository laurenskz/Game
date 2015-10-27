/*
 * World.c
 *
 *  Created on: 18 okt. 2015
 *      Author: Laurens
 */

#include "../include/World.h"

void worldInit(void){
	cameraInit();
}


void worldLogic(float elapsedTime){
	cameraLogic(elapsedTime);
}

void renderWorld(float elapsedTime){

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

