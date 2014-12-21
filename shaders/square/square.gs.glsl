#version 330
layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in Vertex 
{ 
    vec4 position;
    vec3 color;
} vertex[];

out vec3 g_Color;
out vec3 g_Normal;
out vec2 g_TexCoords;
out vec3 g_Position;

uniform mat4 uVMatrix;
uniform mat4 uPMatrix;

const float f = 1.f;

const vec3 normalUp = vec3(0,1,0);

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

    vec4 Mposition;
    vec4 MVposition;

    mat4 VPMatrix = uPMatrix * uVMatrix;

    //mat4 NormalMatrix = transpose(inverse(uVMatrix * translate(mat4(1), vertex[0].position)));

    Mposition = (vertices[0] + vertex[0].position);
    MVposition = uVMatrix * Mposition;
    gl_Position = uPMatrix * MVposition;
    g_Position = vec3(Mposition);
    g_Color = vertex[0].color;  
    g_Normal = normalUp; 
    g_TexCoords = texCoord[0];   
    EmitVertex();

    Mposition = (vertices[1] + vertex[0].position);
    MVposition = uVMatrix * Mposition;
    gl_Position = uPMatrix * MVposition;
    g_Position = vec3(Mposition);
    g_Color = vertex[0].color;
    g_Normal = normalUp;  
    g_TexCoords = texCoord[1];   
    EmitVertex(); 

    Mposition = (vertices[2] + vertex[0].position);
    MVposition = uVMatrix * Mposition;
    gl_Position = uPMatrix * MVposition;
    g_Position = vec3(Mposition);
    g_Color = vertex[0].color; 
    g_Normal = normalUp;  
    g_TexCoords = texCoord[2];    
    EmitVertex();           

    Mposition = (vertices[3] + vertex[0].position);
    MVposition = uVMatrix * Mposition;
    gl_Position = uPMatrix * MVposition;
    g_Position = vec3(Mposition);
    g_Color = vertex[0].color;  
    g_Normal = normalUp; 
    g_TexCoords = texCoord[3];     
    EmitVertex();
  
    EndPrimitive();

}