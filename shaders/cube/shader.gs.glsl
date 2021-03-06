#version 330
layout(points) in;
layout(triangle_strip, max_vertices=36) out;

in Vertex 
{ 
  vec4 position;  
  vec3 color; 
} vertex[];

layout(std140) uniform global_vec4{
    vec3 light_position;
    vec3 light_intensity;
    vec3 light_ks;
    vec3 camera_position;
    vec3 front_vector;
};

layout(std140) uniform global_matrix{
    mat4 p_matrix;
    mat4 v_matrix;   
};

out vec3 g_Color;
out vec3 g_Normal;
out vec2 g_TexCoords;
out vec3 g_Position;
out vec3 g_cube_position;

const float f = 1f;


void main()
{   

    vec3 vector_a = normalize(vec3(vertex[0].position) - 2 * camera_position);

    vec3 vector_b = front_vector;

    float dot_product = dot(vector_a, vector_b);

    if(dot_product > 0.62){

        const int elements[] = int[]
        (
            0,2,1,
            2,3,1,

            1,3,5,
            3,7,5,

            5,7,4,
            7,6,4,

            4,6,0,
            6,2,0,

            3,2,7,
            2,6,7,

            5,4,1,
            4,0,1
        );


        vec4 vertices[] = vec4[]
        (
            vec4(-f,-f,-f, 1), // 0
            vec4(-f,-f,+f, 1), // 1
            vec4(-f,+f,-f, 1), // 2
            vec4(-f,+f,+f, 1), // 3
            vec4(+f,-f,-f, 1), // 4
            vec4(+f,-f,+f, 1), // 5
            vec4(+f,+f,-f, 1), // 6
            vec4(+f,+f,+f, 1)  // 7
        );

        vec3 normals[] = vec3[]
        (
            vec3(-1,0,0), // 0
            vec3(-1,0,0), // 1  // FACE1

            vec3(0,0,1),  // 2
            vec3(0,0,1),  // 3  // FACE2

            vec3(1,0,0),  // 4
            vec3(1,0,0),  // 5  // FACE3

            vec3(0,0,-1), // 6
            vec3(0,0,-1), // 7  // FACE4

            vec3(0,1,0),  // 8
            vec3(0,1,0),  // 9  // FACE5

            vec3(0,-1,0), // 10
            vec3(0,-1,0)  // 11 // FACE6
        );

        vec2 texCoord[] = vec2[]
        (
            vec2(0, 1), //Vertex1  // TRIANGLE 1
            vec2(0, 0), //Vertex2
            vec2(1, 1), //Vertex3

            vec2(0, 0), //Vertex1  // TRIANGLE 2
            vec2(1, 0), //Vertex2
            vec2(1, 1) //Vertex3
        );

        vec4 mv_position;
        vec4 m_position;

        int iIndex = 0;

        int triangle_Nb;

        
        for(int iTri = 0; iTri < 12; ++iTri)
        {
            if(iTri %2 == 0){
                triangle_Nb = 0;
            }
            else{
                triangle_Nb = 3;
            }

            for(int iVert = 0; iVert < 3; ++iVert)
            {
                m_position = vertices[elements[iIndex++]] + vertex[0].position;
                mv_position = v_matrix * m_position;
                gl_Position = p_matrix * mv_position;
                g_Position = vec3(m_position);
                g_Color = vertex[0].color;  
                g_Normal = normals[iTri];
                g_TexCoords = texCoord[triangle_Nb + iVert];
                g_cube_position = vec3(vertex[0].position);

                if(dot(vector_b, g_Normal) <= 0.55){
                    EmitVertex();                
                }

                     
            }
            //if(dot(vector_b, g_Normal) < 0){
                EndPrimitive();
            //}
        }
    }
}