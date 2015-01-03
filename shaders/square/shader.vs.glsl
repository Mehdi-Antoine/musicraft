#version 330

layout(location = 0) in vec3 aPosition;
layout(location = 1) in int aType;

out Vertex 
{ 
	vec4 position;
	int type; 
}vertex;

void main() {

	vec4 homogen_position = vec4(aPosition, 1);

	vertex.type = aType;
	vertex.position = homogen_position;
}
