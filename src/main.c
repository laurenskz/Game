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
#include "../include/Camera.h"
#include "../include/main.h"
#define MAX_KEY 360
#define RAD 0.01745329251
#define WIDTH 1920
#define HEIGHT 1080
#define FOV 60
#define NEAR_Z 0.5
#define FAR_Z 10000



GLFWwindow* initWindow(void);
int initGlew(void);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_pos_callback(GLFWwindow* window, double x, double y);
void render(void);
void logic(float*zTranslation,float*xTranslation,float*yTranslation,float*camX,float*camY,float*camZ,float* cameraRotX,float* cameraRotY, float* cameraRotZ);
GLfloat* getProjectionMatrix(void);


char* keys;
double mouseX, mouseY,mouseXDiff,mouseYDiff;
char newMouse;
char mouseInputAvailable;

int main(void)
{
	keys = calloc(MAX_KEY,sizeof(char));
	newMouse = 1;
	GLFWwindow* window = initWindow();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    if(window==NULL||!initGlew())return -1;
    glfwSetKeyCallback(window,key_callback);
    glfwSetCursorPosCallback(window,mouse_pos_callback);
    int vao = test();
    int shaderProgram = getShaderProgram("shader.vert", "shader.frag");
    int plateauShader = getShaderProgram("plateauShader.vert","plateauShader.frag");
    glClearColor(0.3,0.3,1,1);
    float rotation = 0;
    float zTranslation = -0.6;
    float xTranslation = 0;
    float yTranslation = 0;
    float cameraX = 0;
    float cameraY = 0;
    float cameraZ = 0;
    float cameraRotX = 0;
    float cameraRotY = 0;
    float cameraRotZ = 0;
    int plateauID = plateau();

    GLint modelMatrixLocation = glGetUniformLocation(shaderProgram,"rot");
    GLint projectionMatrixLocation = glGetUniformLocation(shaderProgram,"projectionMatrix");
    GLint plateauProjection = glGetUniformLocation(plateauShader,"projectionMatrix");
    GLint plateauModel = glGetUniformLocation(plateauShader,"modelMatrix");
    GLint plateauView = glGetUniformLocation(plateauShader,"viewMatrix");
    GLint normalView = glGetUniformLocation(shaderProgram,"viewMatrix");
    GLuint deerModel = loadObjToVAO("deer-obj.obj");
    GLuint textureId, deerTextureID;
    image* imageP = createTexture("wood.jpg");
    glGenTextures(1,&textureId);
    glBindTexture(GL_TEXTURE_2D,textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imageP->width,imageP->height,0,GL_RGBA,GL_UNSIGNED_BYTE,imageP->texture);
    freeImage(imageP);
    imageP = createTexture("deer texture.tga");
	glGenTextures(1,&deerTextureID);
	glBindTexture(GL_TEXTURE_2D,deerTextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imageP->width,imageP->height,0,GL_RGBA,GL_UNSIGNED_BYTE,imageP->texture);
	freeImage(imageP);
    GLfloat* projectionMatrix = getProjectionMatrix();
    /* Loop until the user closes the window */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    cameraInit();
    struct timeb start, end;
	int diff = 0;
	int millisecs = 0;
	int frames = 0;
	double localMouseX, localMouseY;
    while (!glfwWindowShouldClose(window))
    {
    	ftime(&start);
    	float timeElapsed = (float)diff/1000;
    	millisecs += diff;
    	if(millisecs>1000){
    		millisecs-=1000;
    		printf("FPS: %d\n",frames);
    		fflush(stdout);
    		frames = 0;
    	}
    	cameraLogic(timeElapsed);
    	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		if(rotation>360)rotation = 0;
		logic(&zTranslation,&xTranslation,&yTranslation,&cameraX,&cameraY,&cameraZ,&cameraRotX,&cameraRotY,&cameraRotZ);
		rotation+=0.03;
		glUseProgram(shaderProgram);
		mat4* translation = translate(xTranslation,yTranslation,zTranslation);
		mat4* rotationMat = rotate(rotation,rotation,0);
		mat4* together = multiplyMat4Mat4(rotationMat,translation);
		mat4* viewMatrix = createViewMatrix(cameraX,cameraY,cameraZ,cameraRotX,cameraRotY,cameraRotZ);
		glUniformMatrix4fv(modelMatrixLocation,1,GL_FALSE,together->data);
		glUniformMatrix4fv(projectionMatrixLocation,1,GL_FALSE,projectionMatrix);
		glUniformMatrix4fv(normalView,1,GL_FALSE,viewMatrix->data);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES,24,GL_UNSIGNED_SHORT,0);
		glUseProgram(plateauShader);
		glUniformMatrix4fv(plateauProjection,1,GL_FALSE,projectionMatrix);
		glUniformMatrix4fv(plateauView,1,GL_FALSE,viewMatrix->data);
		glBindVertexArray(deerModel);
		mat4* modelMat4 = translate(0,zTranslation,0);
		glUniformMatrix4fv(plateauModel,1,GL_FALSE,modelMat4->data);
		free(modelMat4);
		glBindTexture(GL_TEXTURE_2D,deerTextureID);
		glDrawArrays(GL_TRIANGLES,0,4146);
		glBindVertexArray(plateauID);
		int count = 0;
		int x = 0;
		glBindTexture(GL_TEXTURE_2D,textureId);
		for(;count<100;count++){
			mat4* modelMat4 = translate(x,0,0);
			glUniformMatrix4fv(plateauModel,1,GL_FALSE,modelMat4->data);
			glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);
			x-=4;
			free(modelMat4);
		}
    	glBindVertexArray(0);
    	glUseProgram(0);
    	free(translation);
    	free(viewMatrix);
    	/* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        if(newMouse){
        	newMouse = 0;
        	mouseXDiff = mouseX - localMouseX;
        	mouseYDiff = mouseY - localMouseY;
        	localMouseX = mouseX;
        	localMouseY = mouseY;
        	mouseInputAvailable = 1;
        }else{
        	mouseXDiff = 0;
        	mouseYDiff = 0;
        	mouseInputAvailable = 0;
        }
        ftime(&end);
        diff = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
        frames++;
    }

    glfwTerminate();
    return 0;
}

void render(void){
	if(keys[GLFW_KEY_F]){
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glEnd();
	}
}


int initGlew(void){
	GLenum error = glewInit();
	    if(error!=GLEW_OK){
	    	printf("massive error with glew\n");
	    	fflush(stdout);
	    	return 0;
	    }else{
	    	printf("loading glew succeeded :)\n");
	    	fflush(stdout);
	    	return 1;
	    }
}


GLFWwindow* initWindow(){

    /* Initialize the library */
    if (!glfwInit())
        return NULL;
    glfwWindowHint(GLFW_DEPTH_BITS,32);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", glfwGetPrimaryMonitor(), NULL);
    if (!window)
    {
        glfwTerminate();
        return NULL;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    printf("%s\n", glGetString(GL_VERSION));
    fflush(stdout);
    return window;
}

GLfloat* getProjectionMatrix(void){
	GLfloat* matrix = malloc(sizeof(GLfloat)*16);
	float aspecRatio = WIDTH/HEIGHT;
	matrix[0] = 1/(tan((FOV*RAD)/2))/aspecRatio;
	matrix[1] = 0;
	matrix[2] = 0;
	matrix[3] = 0;
	matrix[4] = 0;
	matrix[5] = 1/(tan((FOV*RAD)/2));
	matrix[6] = 0;
	matrix[7] = 0;
	matrix[8] = 0;
	matrix[9] = 0;
	matrix[10] = (-(NEAR_Z+FAR_Z))/(FAR_Z-NEAR_Z);
	matrix[11] = -(2*FAR_Z*NEAR_Z)/(FAR_Z-NEAR_Z);
	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = -1;
	matrix[15] = 0;
	return matrix;
}

void logic(float*zTranslation,float*xTranslation,float*yTranslation,float*camX,float*camY,float*camZ,float* cameraRotX,float* cameraRotY, float* cameraRotZ){
	if(keys[GLFW_KEY_UP])*yTranslation+=0.03;
	if(keys[GLFW_KEY_DOWN])*yTranslation-=0.03;
	if(keys[GLFW_KEY_RIGHT])*xTranslation+=0.03;
	if(keys[GLFW_KEY_LEFT])*xTranslation-=0.03;
	if(keys[GLFW_KEY_I])*zTranslation+=0.03;
	if(keys[GLFW_KEY_K])*zTranslation-=0.03;
}

char* mainGetKeys(void){
	return keys;
}

char mouseMoved(void){
	return mouseInputAvailable;
}

double mainGetMouseDiffX(void){
	return mouseXDiff;
}
double mainGetMouseDiffY(void){
	return mouseYDiff;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	keys[key] = (action!=GLFW_RELEASE);
}

static void mouse_pos_callback(GLFWwindow* window, double x, double y){
	mouseX = x;
	mouseY = y;
	newMouse = 1;
}
