#ifndef MODEL_VIEW_PROJECTION
#define MODEL_VIEW_PROJECTION
#include "mmath.h"
mat4* createProjectionMatrix(int width, int height, float fieldOfView, float farPlane,float nearPlane);
mat4* createViewMatrix(float xPos, float yPos, float zPos,float xRot,float yRot,float zRot);
#endif
