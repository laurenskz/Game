#version 150
precision highp float;
uniform sampler2D samplerTexture;
in vec2 texCoords;
void main(void) {
	gl_FragColor = texture(samplerTexture,texCoords);
}