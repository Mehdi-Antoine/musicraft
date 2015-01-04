#version 330
layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in Vertex 
{ 
    vec4 position;
    vec3 color;
} vertex[];

layout(std140) uniform global_matrix{
    mat4 p_matrix;
    mat4 v_matrix;
    vec3 camera_position;
};

out vec3 g_Color;
out vec3 g_Normal;
out vec2 g_TexCoords;
out vec3 g_Position;

const float f = 1;

const vec3 normal_up = vec3(0,1,0);

const int elements[] = int[]
(
    3,2,1,
    2,0,1
);

void main()
{   
    vec4 vertices[] = vec4[]
    (
        vec4(-f,f,-f, 1),
        vec4(-f,f,+f, 1), 
        vec4(+f,f,-f, 1), 
        vec4(+f,f,+f, 1) 
    );

    vec2 texCoord[] = vec2[]
    (
        vec2(0, 0),
        vec2(0, 1),
        vec2(1, 0),
        vec2(1, 1)
    );

    vec4 m_position;
    vec4 mv_position;

    mat4 VPMatrix = p_matrix * v_matrix;

    m_position = (vertices[0] + vertex[0].position);
    mv_position = v_matrix * m_position;
    gl_Position = p_matrix * mv_position;
    g_Position = vec3(m_position);
    g_Color = vec3(1,0,0);//vertex[0].color;  
    g_Normal = normal_up; 
    g_TexCoords = texCoord[0];   
    EmitVertex();

    m_position = (vertices[1] + vertex[0].position);
    mv_position = v_matrix * m_position;
    gl_Position = p_matrix * mv_position;
    g_Position = vec3(m_position);
    g_Color = vec3(0,1,0);//vertex[0].color;
    g_Normal = normal_up;  
    g_TexCoords = texCoord[1];   
    EmitVertex(); 

    m_position = (vertices[2] + vertex[0].position);
    mv_position = v_matrix * m_position;
    gl_Position = p_matrix * mv_position;
    g_Position = vec3(m_position);
    g_Color = vec3(0,0,1);//vertex[0].color; 
    g_Normal = normal_up;  
    g_TexCoords = texCoord[2];    
    EmitVertex();           

    m_position = (vertices[3] + vertex[0].position);
    mv_position = v_matrix * m_position;
    gl_Position = p_matrix * mv_position;
    g_Position = vec3(m_position);
    g_Color = vec3(1,0,0);//vertex[0].color;  
    g_Normal = normal_up; 
    g_TexCoords = texCoord[3];     
    EmitVertex();
  
    EndPrimitive();

}