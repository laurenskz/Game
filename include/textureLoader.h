#ifndef TEXTURE_LOADER
#define TEXTURE_LOADER

typedef struct image{
	int width;
	int height;
	GLubyte* texture;
} image;

image* createTexture(char* filePath);
void freeImage(image* imagePointer);

GLuint textureToID(char* filePath);
#endif
