#version 330

layout(location = 0) in vec3 buffer_position;
layout(location = 1) in vec3 buffer_color;

out Vertex 
{ 
	vec4 position;
	vec3 color; 
}vertex;

void main() {

	vec4 homogen_position = vec4(buffer_position, 1);

	vertex.color = buffer_color;
	vertex.position = homogen_position;
}
