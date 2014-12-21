#version 330

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;

uniform mat4 uPMatrix;
uniform mat4 uVMatrix;

out Vertex 
{ 
	vec4 position;
	vec3 color; 
}vertex;

out vec3 vColor; //Lorsque l'on n'utilise pas le geometry shader

void main() {

	//Conversion en coordonées homogènes
	vec4 homogen_position = vec4(aPosition, 1);

	//gl_Position = uPMatrix * uVMatrix * homogen_position; //Lorsque l'on n'utilise pas le geometry shader

	vertex.color = aColor;
	vertex.position = homogen_position;

    vColor = aColor; //Lorsque l'on n'utilise pas le geometry shader
}
