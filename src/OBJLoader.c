#include <stdio.h>
#include <stdlib.h>
#include <FreeImage.h>
#include <glew.h>
#include <string.h>

typedef struct image{
	int width;
	int height;
	GLubyte* texture;
} image;

typedef struct vec3{
	float x,y,z;
} vec3;

typedef struct vec2{
	float x,y;
} vec2;


int getContents(char* fileName);
int analyzeString(char* fileContents, int length);
void skipSpaces(int* p,char* fileContents);
void seekEndOfNumber(int* p, char* fileContents);
void fillNumbers(char** spaceToStore,char* fileContents,int place, int times);
void freeCharPP(char** toFree, int length);
int* getOneFace(char* face);
void seekCharacter(int* p, char c, char* fileContents);
vec2* addElementVec2(vec2 element,vec2* array,int* length,int* pointer);
vec3* addElementVec3(vec3 element,vec3* array,int* length,int* pointer);
void addGLElementVec3(vec3 element,GLfloat** array,int* length,int* pointer);
void addGLElementVec2(vec2 element,GLfloat** array,int* length,int* pointer);

GLuint loadObjToVAO(char* filePath){
	return getContents(filePath);
}

int getContents(char* fileName){
	char * buffer = 0;
	long length;
	FILE * f = fopen (fileName, "rb");
	if (f)
	{
	  fseek (f, 0, SEEK_END);
	  length = ftell (f);
	  fseek (f, 0, SEEK_SET);
	  buffer = malloc (length+1);
	  if (buffer)
	  {
	    fread (buffer, 1, length, f);
	  }
	  fclose (f);
	}
	buffer[length] = '\0';
	return analyzeString(buffer,length);
}

int analyzeString(char* fileContents,int length){
	//We need to allocate a bunch of stuff to store all the data from the file in
	vec3* vertices = malloc(sizeof(vec3)*100);
	int verticesLength = 100;
	int vertexPointer = 0;
	vec2* textureCoordinates = malloc(sizeof(vec2)*100);
	int textureCoordinatesLength = 100;
	int texturePointer = 0;
	vec3* normalVectors = malloc(sizeof(vec3)*100);
	int normalVectorsLength = 100;
	int normalVectorPointer = 0;
	GLfloat* verticesGl = malloc(sizeof(GLfloat)*300);
	int verticesGlLength = 300;
	int verticesGlPointer = 0;
	GLfloat* texturesGl = malloc(sizeof(GLfloat)*300);
	int texturesGlLength = 300;
	int texturesGlPointer = 0;
	GLfloat* normalsGl = malloc(sizeof(GLfloat)*300);
	int normalsGlLength = 300;
	int normalsGlPointer = 0;
	//From here we start going through the file
	int place = 0;
	for(;place<length;){
		if(fileContents[place]=='v'&&fileContents[place+1]==' '){
			char **toStore = malloc(sizeof(char*)*3);
			fillNumbers(toStore,fileContents,place+2,3);
			vec3 vertex;
			vertex.x = atof(toStore[0]);
			vertex.y = atof(toStore[1]);
			vertex.z = atof(toStore[2]);
			vertices = addElementVec3(vertex,vertices,&verticesLength,&vertexPointer);
			freeCharPP(toStore,3);
		}
		else if(fileContents[place]=='v'&&fileContents[place+1]=='t'&&fileContents[place+2]==' '){
			char **toStore = malloc(sizeof(char*)*2);
			fillNumbers(toStore,fileContents,place+3,2);
			vec2 elements;
			elements.x = atof(toStore[0]);
			elements.y = atof(toStore[1]);
			textureCoordinates = addElementVec2(elements,textureCoordinates,&textureCoordinatesLength,&texturePointer);
			freeCharPP(toStore,2);
		}
		else if(fileContents[place]=='v'&&fileContents[place+1]=='n'&&fileContents[place+2]==' '){
			char **toStore = malloc(sizeof(char*)*3);
			fillNumbers(toStore,fileContents,place+2,3);
			vec3 elements;
			elements.x = atof(toStore[0]);
			elements.y = atof(toStore[1]);
			elements.z = atof(toStore[2]);
			normalVectors = addElementVec3(elements,normalVectors,&normalVectorsLength,&normalVectorPointer);
			freeCharPP(toStore,3);
		}
		else if(fileContents[place]=='f'&&fileContents[place+1]==' '){
			char** strings = malloc(sizeof(char*)*3);
			fillNumbers(strings,fileContents,place+2,3);
			int faceToGet = 0;
			for(;faceToGet<3;faceToGet++){
				int* p1 = getOneFace(strings[faceToGet]);
				addGLElementVec3(vertices[p1[0]-1],&verticesGl,&verticesGlLength,&verticesGlPointer);
				addGLElementVec2(textureCoordinates[p1[1]-1],&texturesGl,&texturesGlLength,&texturesGlPointer);
				addGLElementVec3(normalVectors[p1[2]-1],&normalsGl,&normalsGlLength,&normalsGlPointer);
				free(p1);
			}
			freeCharPP(strings,3);
		}
		while(fileContents[place]!='\r'){
			place++;
		}
		place+=2;//We want to skip the \r which place currently points to and also the \n which is after that
		//After this place points to the first character on the next line.
	}
	GLuint vao, vbo, vbo2, vbo3;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*verticesGlPointer,verticesGl,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER,vbo2);
	glBufferData(GL_ARRAY_BUFFER, texturesGlLength * sizeof(GLfloat),texturesGl,GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &vbo3);
	glBindBuffer(GL_ARRAY_BUFFER,vbo3);
	glBufferData(GL_ARRAY_BUFFER, normalsGlLength * sizeof(GLfloat),normalsGl,GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
	printf("verticesGlLength %d",verticesGlPointer);
	return vao;
}

void fillNumbers(char** spaceToStore,char* fileContents,int localPlace, int times){
	int x = 0;
	for(;x<times;x++){
		skipSpaces(&localPlace,fileContents);
		int endOfNumber = localPlace;
		seekEndOfNumber(&endOfNumber,fileContents);
		char* number = malloc((1+endOfNumber-localPlace)*sizeof(char));
		int i = 0;
		for(;i<(endOfNumber - localPlace);i++){
			number[i] = fileContents[localPlace+i];
		}
		number[i] = 0;
		spaceToStore[x] = number;
		localPlace = endOfNumber;
		if(fileContents[localPlace]=='\r')return;//If we have reached the end of the line we just have to quit
	}
}

void skipSpaces(int* p,char* fileContents){
	while(fileContents[*p]==' '){
		(*p)++;
	}
}

int* getOneFace(char* face){
	int current = 0;
	int seeker = 0;
	int time = 0;
	int* toReturn = malloc(sizeof(int)*3);
	for(;time<3;time++){
		seekCharacter(&seeker,'/',face);
		int difference = seeker - current;
		if (difference>0) {
			char number[difference+1];
			int i = 0;
			while(current<seeker){
				number[i] = face[current];
				current++;
				i++;
			}
			number[i] = '\0';
			toReturn[time] = atol(number);
		}else{
			toReturn[time] = 0;
		}
		if(face[current]=='\0')break;
		seeker++;//Move on to next char
		current = seeker;
	}
	return toReturn;
}

void seekCharacter(int* p, char c, char* fileContents){
	while(fileContents[*p]!=c&&fileContents[*p]!='\0'){
		(*p)++;
	}
}

void addGLElementVec3(vec3 element,GLfloat** array,int* length,int* pointer){
	GLfloat* toReturn = *array;
	if((*pointer)+3>=*length){
		(*length)+=200;
		GLfloat* newPntr = realloc(toReturn,sizeof(GLfloat)*(*length));
		if(newPntr!=NULL){
			toReturn = newPntr;
		}else{
			fprintf(stderr,"failed to realloc more memory while loading in an obj file");
		}
	}
	toReturn[*pointer] = element.x;
	toReturn[(*pointer)+1] = element.y;
	toReturn[(*pointer)+2] = element.z;
	(*pointer)+=3;
	*array = toReturn;
}
void addGLElementVec2(vec2 element,GLfloat** array,int* length,int* pointer){
	GLfloat* toReturn = *array;
	if((*pointer)+2>=*length){
		(*length)+=200;
		GLfloat* newPntr = realloc(toReturn,sizeof(GLfloat)*(*length));
		if(newPntr!=NULL){
			toReturn = newPntr;
		}else{
			fprintf(stderr,"failed to realloc more memory while loading in an obj file");
		}
	}
	toReturn[*pointer] = element.x;
	toReturn[(*pointer)+1] = element.y;
	(*pointer)+=2;
	*array = toReturn;
}

vec2* addElementVec2(vec2 element,vec2* array,int* length,int* pointer){
	vec2* toReturn = array;
	if((*pointer)>=*length){
		(*length)+=100;
		vec2* newPntr = realloc(array,sizeof(vec2)*(*length));
		if(newPntr!=NULL){
			toReturn = newPntr;
		}else{
			fprintf(stderr,"failed to realloc more memory while loading in an obj file");
		}
	}
	toReturn[*pointer].x = element.x;
	toReturn[*pointer].y = element.y;
	(*pointer)++;
	return toReturn;
}

vec3* addElementVec3(vec3 element,vec3* array,int* length,int* pointer){
	vec3* toReturn = array;
	if((*pointer)>=*length){
		(*length)+=100;
		vec3* newPntr = realloc(array,sizeof(vec3)*(*length));
		if(newPntr!=NULL){
			toReturn = newPntr;
		}else{
			fprintf(stderr,"failed to realloc more memory while loading in an obj file");
		}
	}
	toReturn[*pointer].x = element.x;
	toReturn[*pointer].y = element.y;
	toReturn[*pointer].z = element.z;
	(*pointer)++;
	return toReturn;
}

void seekEndOfNumber(int* p, char* fileContents){
	while(fileContents[*p]!=' '&&fileContents[*p]!='\r'){
		(*p)++;
	}
}
void freeCharPP(char** toFree, int length){
	int i = 0;
	for(;i<length;i++){
		free(toFree[i]);
	}
	free(toFree);
}
