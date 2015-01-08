#version 330

layout(location = 0) in vec3 buffer_position;
layout(location = 1) in vec3 buffer_color;

out vec3 f_color;

void main() {

	gl_Position = vec4(buffer_position, 1);

	f_color = buffer_color;

}