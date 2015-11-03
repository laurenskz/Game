/*
 * Shaders.h
 *
 *  Created on: 22 okt. 2015
 *      Author: Laurens
 */

#ifndef SHADERS_H_
#define SHADERS_H_


#include "../include/shaderCompilation.h"
#include <glew.h>
#include "Types.h"
#include "Light.h"

Shader* getBasicShader(void);
void loadAllShaders(void);
Shader* loadShader(int id);
void uploadLights(Shader* shader);
Shader* getModelShader(void);

#endif /* SHADERS_H_ */
