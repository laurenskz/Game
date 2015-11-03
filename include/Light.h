/*
 * Light.h
 *
 *  Created on: 3 nov. 2015
 *      Author: Laurens
 */

#ifndef LIGHT_H
#define LIGHT_H


#include <stdio.h>
#include <stdlib.h>
#include "Types.h"

void initLight(void);

vec3* getLightPosition(void);

vec3* getLightColour(void);

#endif
