#include "../include/utils.h"

char* filetobuf(char *file){
	FILE *fptr;
	    long length;
	    char *buf;

	    fptr = fopen(file, "rb"); /* Open file for reading */
	    if (!fptr) /* Return NULL on failure */
	        return NULL;
	    fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
	    length = ftell(fptr); /* Find out how many bytes into the file we are */
	    buf = (char*)malloc(length+1); /* Allocate a buffer for the entire length of the file and a null terminator */
	    fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
	    fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
	    fclose(fptr); /* Close the file */
	    buf[length] = 0; /* Null terminator */

	    return buf; /* Return the buffer */
}

void loadToVAO(RenderableMold* mold,PointerWithSize vertices, PointerWithSize normals, PointerWithSize textureCoords, PointerWithSize indices){
	GLuint vao, verticesVBO, indexBuffer, normalVBO,vboTexCoords;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER,verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*vertices.size,vertices.data,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &vboTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER,vboTexCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*textureCoords.size,textureCoords.data,GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER,normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*normals.size,normals.data,GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
	if(indices.size!=0){
		glGenBuffers(1,&indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)*indices.size, indices.data,GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuffer);
		mold->size = indices.size;
		mold->ibo = indexBuffer;
	}
	mold->vao = vao;
}
