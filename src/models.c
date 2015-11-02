#include <stdio.h>
#include <stdlib.h>
#include <glew.h>

int plateau(void){
	const GLfloat diamond[4][3] = {
				{  -2,  0.1,-2  },
				{  2,  0.1,-2  },
				{  2, 0.1,0  },
				{  -2, 0.1,0},
		};
		const GLfloat colors[4][3] = {
			    {  1,0,0  }, /* Top left point */
			    {  0,1,0  }, /* Top Right point */
			    {  0,0,1  },/* Bottom left point */
			    {  0,1,1  }}; /* Bottom right point */
		GLuint vao, vbo, indexBuffer, vbo2,vboTexCoords;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(diamond),diamond,GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glGenBuffers(1, &vbo2);
		glBindBuffer(GL_ARRAY_BUFFER,vbo2);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat),colors,GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
		const GLfloat texCoords[4][2] = {
				{  0, 0   },
				{  1,  0},
				{  1, 10},
				{  0, 10},
		};
		glGenBuffers(1, &vboTexCoords);
		glBindBuffer(GL_ARRAY_BUFFER,vboTexCoords);
		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat),texCoords,GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);
		GLushort indici[] = {
				0,2,1,
				2,3,0,
		};
		glGenBuffers(1,&indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indici), indici,GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuffer);
		return vao;
}
