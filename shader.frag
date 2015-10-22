#version 150
precision highp float;
in vec3 inColor; 
in vec3 pos;
void main(void) {
	gl_FragColor = vec4(inColor,1.0);
}