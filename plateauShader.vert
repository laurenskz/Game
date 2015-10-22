#version 150
layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normals;
layout(location = 1) in vec2 verTexCoords;
out vec2 texCoords;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform int b;
void main(void) {
	texCoords = verTexCoords;
	gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(position,1);
}