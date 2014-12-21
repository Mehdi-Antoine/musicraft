#version 330 core

in vec2 vFragTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
    fFragColor = texture(uTexture, vFragTexCoords).rgb;
}
