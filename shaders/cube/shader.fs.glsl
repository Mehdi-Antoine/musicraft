#version 330

in vec3 g_Position;
in vec3 g_cube_position;
in vec3 g_Color;
in vec3 g_Normal;
in vec2 g_TexCoords;

layout(std140) uniform global_vec4{
    vec3 light_position;
    vec3 light_intensity;
    vec3 light_ks;
    vec3 camera_position;
    vec3 front_vector;
};

uniform sampler2D texture0;
uniform sampler2D texture1;

out vec3 fFragColor;

vec3 texture_color0 = texture(texture0, g_TexCoords).rgb;
vec3 texture_color1 = texture(texture1, g_TexCoords).rgb;

vec3 blinnPhongPoint(vec3 position, float factor){

	vec3 n = normalize(g_Normal);

	vec3 w = normalize(position - g_Position);

	float d = distance(position, g_Position);

	float L = (light_intensity) / (1 + d + d * d);

	vec3 w0 = normalize(camera_position - g_Position);

	vec3 halfVector = (w + w0) / 2;

	halfVector = normalize(halfVector);

	vec3 color = factor * L * g_Color * (texture(texture1, g_TexCoords).rgb * max(dot(w, n), 0) + texture(texture1, g_TexCoords).rgb * pow(max(dot(halfVector, n), 0), 1));

	return color;

}

vec3 blinnPhongDirectionnal(vec3 position){

	vec3 n = normalize(g_Normal);

	vec3 w = normalize(position);

	vec3 L = light_intensity;

	vec3 w0 = normalize(-g_Position);

	vec3 halfVector = (w + w0) / 2;

	halfVector = normalize(halfVector);

	vec3 color = L * (texture(texture0, g_TexCoords).rgb * max(dot(w, n), 0) + texture(texture0, g_TexCoords).rgb * pow(max(dot(halfVector, n), 0), 1));

	return color;

}

void main() {

    fFragColor += max(blinnPhongDirectionnal(light_position), 0);       //Lumière directionnelle
    fFragColor += 0.1 * texture(texture0, g_TexCoords).rgb;             //Ambiance globale
	
    if(distance(2*camera_position, g_cube_position) < 13){

    	fFragColor += max(blinnPhongPoint(2 * camera_position, 100), 0); //Lumière Point
		
    }

    

}
