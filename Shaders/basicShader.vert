#version 150
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 verTexCoords;
layout(location = 2) in vec3 normals;
out vec2 texCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;


uniform vec3 lightPosition;
uniform mat4 mvp;

void main(void) {
	texCoords = verTexCoords;
	vec3 toLight = lightPosition - position;
	toLightVector = toLight;
	surfaceNormal = normals;
	gl_Position = mvp*vec4(position,1);
}