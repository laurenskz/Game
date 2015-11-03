/*
 * Projection.h
 *
 *  Created on: 22 okt. 2015
 *      Author: Laurens
 */

#ifndef PROJECTION_H_
#define PROJECTION_H_

#include <glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/mmath.h"

#define WIDTH 1920
#define HEIGHT 1080
#define FOV 60
#define NEAR_Z 0.5
#define FAR_Z 10000
#define RAD 0.01745329251

mat4* getProjectionMatrix(void);
#endif /* PROJECTION_H_ */
