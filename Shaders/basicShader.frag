#version 150
precision highp float;
uniform sampler2D samplerTexture;
uniform vec3 lightColour;

in vec3 surfaceNormal;
in vec3 toLightVector;

in vec2 texCoords;
void main(void) {
	float lightIntension = dot(normalize(surfaceNormal), normalize(toLightVector));
	if(lightIntension<0)lightIntension=0;
	vec3 lightColourWithBrightness = lightIntension * lightColour;
	gl_FragColor = vec4(lightColourWithBrightness,1)* texture(samplerTexture,texCoords);
}