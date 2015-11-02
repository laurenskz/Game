#include <stdio.h>
#include <stdlib.h>
#include <glew.h>
#include <FreeImage.h>
#include "../include/textureLoader.h"


image* createTexture(char* filePath){
	//FreeImage_Initialise(FALSE);
	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(filePath,0);//Automatocally detects the format(from over 20 formats!)
	FIBITMAP* imagen = FreeImage_Load(formato, filePath,JPEG_ACCURATE);
	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);

	int w = FreeImage_GetWidth(imagen);
	int h = FreeImage_GetHeight(imagen);
	GLubyte* textura = (GLubyte*) malloc(4*w*h);
	char* pixeles = (char*)FreeImage_GetBits(imagen);
	//FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).
	int j = 0;
	for(; j<w*h; j++){
		textura[j*4+0]= pixeles[j*4+2];
		textura[j*4+1]= pixeles[j*4+1];
		textura[j*4+2]= pixeles[j*4+0];
		textura[j*4+3]= pixeles[j*4+3];
	}
	free(pixeles);
	FreeImage_Unload(imagen);
	image* imageToReturn = malloc(sizeof(image));
	imageToReturn->height = h;
	imageToReturn->width = w;
	imageToReturn->texture = textura;
	return imageToReturn;
}
void freeImage(image* imagePointer){
	free(imagePointer->texture);
	free(imagePointer);
}

GLuint textureToID(char* filePath){
	GLuint textureId;
	image* imageP = createTexture(filePath);
	glGenTextures(1,&textureId);
	glBindTexture(GL_TEXTURE_2D,textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imageP->width,imageP->height,0,GL_RGBA,GL_UNSIGNED_BYTE,imageP->texture);
	freeImage(imageP);
	return textureId;
}
