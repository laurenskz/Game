#ifndef Camera
#define Camera
#include "../include/mmath.h"
mat4* cameraGetViewMatrix(void);
void cameraLogic(float elapsedTime);
void cameraInit(void);
void cameraSetLookatX(float x);
void cameraSetLookatY(float y);
void cameraSetLookatZ(float z);
void lookAtRecalculator(void);
void calculateLookat(void);
void incrementxAngle(float toAdd);
void incrementyAngle(float toAdd);
float calculateNegativeOrPositive(float angle);
#endif
