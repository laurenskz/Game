#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <glew.h>
#include <glfw3.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>
#include "../include/shaderCompilation.h"
#include "../include/mmath.h"
#include "../include/models.h"
#include "../include/mvp.h"
#include "../include/textureLoader.h"
#include "../include/OBJLoader.h"
#include "../include/Projection.h"
#include "../include/World.h"
#define MAX_KEY 360

char* mainGetKeys(void);

double mainGetMouseDiffX(void);
double mainGetMouseDiffY(void);
char mouseMoved(void);
void handleMouse(double* localMouseX, double* localMouseY );
GLFWwindow* initWindow(void);
int initGlew(void);
int init(void);
void mainLoop(void);
void logic(float*zTranslation,float*xTranslation,float*yTranslation,float*camX,float*camY,float*camZ,float* cameraRotX,float* cameraRotY, float* cameraRotZ);


#endif
