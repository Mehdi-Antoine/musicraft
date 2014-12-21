#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexCoords;

out vec2 vFragTexCoords;

void main() {
    vFragTexCoords = aVertexTexCoords;
    gl_Position = vec4(aVertexPosition, 0, 1);
}
