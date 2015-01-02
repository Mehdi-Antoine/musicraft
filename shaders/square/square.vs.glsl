#version 330

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;


out Vertex 
{ 
	vec4 position;
	vec3 color; 
}vertex;

void main() {

	vec4 homogen_position = vec4(aPosition, 1);

	vertex.color = aColor;
	vertex.position = homogen_position;

}
