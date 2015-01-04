#version 330

in vec3 g_Position;
in vec3 g_Color;
in vec3 g_Normal;
in vec2 g_TexCoords;

layout(std140) uniform global_light{

    vec3  light_position;
    vec3  light_intensity;
    vec3  light_ks;

    float light_shininess;
};

layout(std140) uniform global_matrix{
    mat4 p_matrix;
    mat4 v_matrix;
    vec3 camera_position;
};


uniform sampler2D uTexture;
uniform sampler2D uTexture2;

out vec4 fFragColor;

vec3 blinnPhong(){

	vec3 n = normalize(g_Normal);

	vec3 w = normalize(light_position - g_Position);

	float d = distance(light_position, g_Position);

	float L = (light_intensity) / (1 + d + d * d);

	vec3 w0 = normalize(camera_position - g_Position);

	vec3 halfVector = (w + w0) / 2;

	halfVector = normalize(halfVector);

	vec3 color = L * (texture(uTexture, g_TexCoords).rgb * max(dot(w, n), 0) + light_ks * pow(max(dot(halfVector, n), 0), light_shininess));

	return color;

}

void main() {
    fFragColor = vec4(texture(uTexture2, g_TexCoords).rgb, 1);//camera_position; //max(blinnPhong(), 0) + 0.01 * g_Color;
}
