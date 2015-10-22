#include <stdio.h>
#include <stdlib.h>
#include "../include/mvp.h"
#include "../include/mmath.h"
#include "../include/Camera.h"

mat4* createViewMatrix(float xPos, float yPos, float zPos,float xRot,float yRot,float zRot){
	return cameraGetViewMatrix();
}
