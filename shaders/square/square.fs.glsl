#version 330

in vec3 g_Position;
in vec3 g_Color;
in vec3 g_Normal;
in vec2 g_TexCoords;


uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightPos_vs; 
uniform vec3 uLightIntensity;

uniform vec3 uCameraPos;

uniform sampler2D uTexture;


out vec3 fFragColor;

vec3 blinnPhong(){

	vec3 n = normalize(g_Normal);

	vec3 w = normalize(uLightPos_vs - g_Position);

	float d = distance(uLightPos_vs, g_Position);

	float L = (uLightIntensity) / (1 + d + d * d);

	vec3 w0 = normalize(uCameraPos - g_Position);

	vec3 halfVector = (w + w0) / 2;

	halfVector = normalize(halfVector);

	vec3 color = L * (texture(uTexture, g_TexCoords).rgb * max(dot(w, n), 0) + uKs * pow(max(dot(halfVector, n), 0), uShininess));

	return color;

}

void main() {
    fFragColor = max(blinnPhong(), 0); //+ 0.01 * g_Color;
}
