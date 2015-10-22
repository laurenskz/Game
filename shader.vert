#version 150
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 outColor;
out vec3 inColor;
out vec3 pos;
uniform mat4 rot;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform int b;
void main(void) {
	inColor = vec3(1,0,0);
	if(gl_VertexID>=4){
		inColor = vec3(0,1,0);
	}
	if(gl_VertexID>=8){
		inColor = vec3(0,0,1);
	}
	if(gl_VertexID>=12){
		inColor = vec3(1,0,1);
	}
	pos = position;
	vec4 newPos = rot*vec4(position,1);
	gl_Position = projectionMatrix*(viewMatrix*newPos);
}