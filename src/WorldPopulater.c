/*
 * WorldPopulater.c
 *
 *  Created on: 30 okt. 2015
 *      Author: Laurens
 */
#include "../include/WorldPopulater.h"

void populateWorld(void){
	RenderableMold* deerMold = loadRenderableMold("Resources/deer-obj.obj","Resources/deer texture.tga");
	int i;
	for(i = 0 ; i < 30 ; i++){
		vec3 position = (vec3){-30*i,0,0};
		Renderable r = (Renderable){1,position,EMPTY_VEC3,EMPTY_VEC3,deerMold};
		addRenderable(r);
	}
	vec3 scale = (vec3){0.5,0.5,0.5};
	for(i = 0 ; i < 30 ; i++){
		vec3 position = (vec3){0,0,30*i};
		Renderable r = (Renderable){1,position,EMPTY_VEC3,scale,deerMold};
		addRenderable(r);
	}
}

