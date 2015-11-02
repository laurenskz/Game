#include "../include/main.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_pos_callback(GLFWwindow* window, double x, double y);

char* keys;
double mouseX, mouseY,mouseXDiff,mouseYDiff;
char newMouse;
char mouseInputAvailable;
GLFWwindow* window;

int main(void)
{
	if(init()==-1)return -1;
	mainLoop();
    glfwTerminate();
    return 0;
}

int init(void){
	keys = calloc(MAX_KEY,sizeof(char));
	newMouse = 1;
	window = initWindow();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
	if(window==NULL||!initGlew())return -1;
	glfwSetKeyCallback(window,key_callback);
	glfwSetCursorPosCallback(window,mouse_pos_callback);
	glClearColor(0.3,0.3,1,1);
	/* Loop until the user closes the window */
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	worldInit();
	return 0;
}

void mainLoop(void){
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
		worldLogic(timeElapsed);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		renderWorld(timeElapsed);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		handleMouse(&localMouseX,&localMouseY);
		ftime(&end);
		diff = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
		frames++;
	}
}

void handleMouse(double* localMouseX, double* localMouseY ){
	 if(newMouse){
		newMouse = 0;
		mouseXDiff = mouseX - *localMouseX;
		mouseYDiff = mouseY - *localMouseY;
		*localMouseX = mouseX;
		*localMouseY = mouseY;
		mouseInputAvailable = 1;
	}else{
		mouseXDiff = 0;
		mouseYDiff = 0;
		mouseInputAvailable = 0;
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
