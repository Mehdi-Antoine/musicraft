#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <iostream>
#include <string>

using namespace glimac;

#define WINDOW_WIDTH  700
#define WINDOW_HEIGHT 700

//--------------------------------------------------------------------------------------------------
//--------------------------------------STRUCTURES--------------------------------------------------
//--------------------------------------------------------------------------------------------------

struct MyProgram {
    Program m_Program;

    GLint uPMatrix,
          uVMatrix;

    GLint uKd,
          uKs,
          uShininess;

    GLint uLightPos,
          uLightIntensity;

    GLint uCameraPos;

    GLint uTexture;

    MyProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/square/square.vs.glsl",
                              applicationPath.dirPath() + "shaders/square/square.gs.glsl",
                              applicationPath.dirPath() + "shaders/square/square.fs.glsl")) {

        uVMatrix   = glGetUniformLocation(m_Program.getGLId(), "uVMatrix");
        uPMatrix   = glGetUniformLocation(m_Program.getGLId(), "uPMatrix");

        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");

        uLightPos = glGetUniformLocation(m_Program.getGLId(), "uLightPos_vs");
        uLightIntensity =  glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");

        uCameraPos =  glGetUniformLocation(m_Program.getGLId(), "uCameraPos");
        
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");

    }
};

//--------------------------------------------------------------------------------------------------
//---------------------------------------LE MAIN----------------------------------------------------
//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv){

    int TAILLE = 30; //Taille de porc

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "GLImac");

    unsigned int FRAMERATE_MILLISECONDS = 1000 / 35;
    unsigned int startTime;

    float currentTime;
    float lastTime;
    int nbFrames = 0;

    //Création des variables clavier et souris SDL
    int key_z = 0, 
        key_s = 0,
        key_q = 0,
        key_d = 0,
        click = 0;


    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

//--------------------------------------------------------------------------------------------------
//-------------------------------CHARGEMENT DES SHADERS---------------------------------------------
//--------------------------------------------------------------------------------------------------

    FilePath applicationPath(argv[0]);

    MyProgram program(applicationPath);

    program.m_Program.use();

//--------------------------------------------------------------------------------------------------
//-------------------------------CHARGEMENT DES TEXTURES---------------------------------------------
//--------------------------------------------------------------------------------------------------

    //LOAD DES TEXTURES

    std::unique_ptr<Image> textureSting = loadImage(applicationPath.dirPath() + "assets/textures/sting.jpg");

    if(textureSting == NULL){
        std::cerr << "Pas de fichier image chargé pour la texture Sting";
        return EXIT_FAILURE;
    }


    //CREATION DES VARIABLES OPENGL

    GLuint textureSting_id;

    glGenTextures(1, &textureSting_id);

    //LOAD DES TEXTURES DANS OPEN GL

    //Sting
    glBindTexture(GL_TEXTURE_2D, textureSting_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,  
                 0,  
                  GL_RGBA,  
                  textureSting->getWidth(),  
                  textureSting->getHeight(),  
                  0,  
                  GL_RGBA,  
                  GL_FLOAT,  
                  textureSting->getPixels());

    glBindTexture(GL_TEXTURE_2D, 0);


//--------------------------------------------------------------------------------------------------
//-------------CONSTRUCTION CUBE ET INJECTION DANS UN TABLEAU DE VERTICES-------------------------
//--------------------------------------------------------------------------------------------------

    glm::vec3 cube_color[TAILLE*TAILLE];
    glm::vec3 cube_position[TAILLE*TAILLE];
    
    for(int k=0; k < TAILLE * TAILLE; ++k){
        cube_position[k] = glm::vec3(2*(k/TAILLE), 0, 2*(k%TAILLE));
        cube_color[k]    = glm::vec3(k/TAILLE, 0, k%TAILLE);
    }
    
//--------------------------------------------------------------------------------------------------
//---------------------------------CONSTRUCTION CAMERA----------------------------------------------
//--------------------------------------------------------------------------------------------------

    FreeflyCamera freeflyCamera;

//--------------------------------------------------------------------------------------------------
//--------------------------CREATION DES VARIABLES UNIFORMES----------------------------------------
//--------------------------------------------------------------------------------------------------

    glEnable(GL_DEPTH_TEST);

    glm::mat4  ProjMatrix, 
               VMatrix;
    

    ProjMatrix = glm::perspective(glm::radians(50.f), (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 1000.f);

    glUniformMatrix4fv(program.uPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix));


    glm::vec3  lightPos = glm::vec3(1, 1, 1);

    glUniform3f(program.uKd, 1, 1, 1);
    glUniform3f(program.uKs, 1, 1, 1);
    glUniform1f(program.uShininess, 1);

    glUniform3f(program.uLightIntensity, 1, 1, 1);
    glUniform3f(program.uLightPos, 1, 1, 1);

    glUniform1i(program.uTexture, 0);

//--------------------------------------------------------------------------------------------------
//-----------------------------CHARGEMENT DU VBO ET DU VAO------------------------------------------
//--------------------------------------------------------------------------------------------------

    GLuint vbo_cube_color;
    GLuint vbo_cube_position;

    glGenBuffers(1, &vbo_cube_color);
    glGenBuffers(1, &vbo_cube_position);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_color);
    glBufferData(GL_ARRAY_BUFFER, TAILLE * TAILLE * sizeof(glm::vec3), cube_color, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_position);
    glBufferData(GL_ARRAY_BUFFER, TAILLE * TAILLE * sizeof(glm::vec3), cube_position, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR = 1;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_position);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*)(0*sizeof(GL_FLOAT)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_color);  
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*)(0*sizeof(GL_FLOAT)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*
    -param1 : index de l'attribut à spécifier
    -param2 : le nombre de composante de l'attribut (=nombre de cases dans le tableau pour définir un attribut)
    -param3 : le type de chaque composante
    -param4 : mystere pour le moment
    -param5 : le nombre de cases à sauter avant de passer à la composante suivante de l'attribut
    -param6 : offset de la première instance de l'attribut
    */

    glBindVertexArray(0);
    

//--------------------------------------------------------------------------------------------------
//----------------------------------APPLICATION LOOP------------------------------------------------
//--------------------------------------------------------------------------------------------------

    bool done = false;

    while(!done){

        startTime = windowManager.getTime();

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)){
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if(e.type == SDL_KEYDOWN){

                if(e.key.keysym.sym == SDLK_ESCAPE){
                    done = true;
                }  

                if(e.key.keysym.sym == SDLK_z){
                    key_z = 1;
                }                 
                if(e.key.keysym.sym == SDLK_s){
                    key_s = 1;
                }
                if(e.key.keysym.sym == SDLK_q){
                    key_q = 1;
                }                 
                if(e.key.keysym.sym == SDLK_d){
                    key_d = 1;
                }
                if(e.key.keysym.sym == SDLK_p){
                    TAILLE++;
                    std::cout << "TAILLE = " << TAILLE << std::endl;
                }
                if(e.key.keysym.sym == SDLK_m){
                    TAILLE--;
                    if(TAILLE <= 0) TAILLE = 1;

                    std::cout << "TAILLE = " << TAILLE << std::endl;
                }
                    
            }

            if(e.type == SDL_KEYUP){
                    
                if(e.key.keysym.sym == SDLK_z){
                    key_z = 0;
                }           
                if(e.key.keysym.sym == SDLK_s){
                    key_s = 0;
                }
                if(e.key.keysym.sym == SDLK_q){
                    key_q = 0;
                }                 
                if(e.key.keysym.sym == SDLK_d){
                    key_d = 0;
                }
                    
            }

            if(e.type == SDL_MOUSEBUTTONDOWN){
                click = 1;
            }

            if(e.type == SDL_MOUSEBUTTONUP){
                click = 0;
            }

            if(e.type == SDL_MOUSEMOTION){
                if(e.motion.xrel != 0 && click == 1){
                    //std::cout << e.motion.xrel << std::endl;
                    freeflyCamera.rotateLeft(-e.motion.xrel/2.);
                }
                if(e.motion.yrel != 0 && click == 1){
                    //std::cout << e.motion.xrel << std::endl;
                    freeflyCamera.rotateUp(-e.motion.yrel/2.);
                }
            }
        }

        if(key_z && !key_s){
            freeflyCamera.moveFront(2);
        }
        if(key_s && !key_z){
            freeflyCamera.moveFront(-2);
        }
        if(key_q && !key_d){
            freeflyCamera.moveLeft(2);
        }
        if(key_d && !key_q){
            freeflyCamera.moveLeft(-2);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        //CONSTRUCTION MATRICE V
        VMatrix = freeflyCamera.getViewMatrix();

        glm::vec3 cameraPos = freeflyCamera.getPosition();
        glUniform3fv(program.uCameraPos, 1, glm::value_ptr(cameraPos));

        //GESTION LIGHT
        lightPos = glm::vec3(glm::vec4(TAILLE, TAILLE, TAILLE, 1));

        glUniformMatrix4fv(program.uVMatrix,    1, GL_FALSE, glm::value_ptr(VMatrix));
        glUniformMatrix4fv(program.uPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix));

        glUniform3f(program.uKd, 1, 1, 1);
        glUniform3f(program.uKs, 1, 1, 1);
        glUniform1f(program.uShininess, 1);

        glUniform3f(program.uLightIntensity, TAILLE * 10, TAILLE * 10, TAILLE * 10);
        glUniform3f(program.uLightPos, lightPos.x, lightPos.y, lightPos.z);

        glBindVertexArray(vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureSting_id);
        
        glDrawArrays(GL_POINTS, 0, TAILLE*TAILLE);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(0);

        ++nbFrames;

        currentTime = windowManager.getTime();

        float ellapsedTime = currentTime - lastTime;

        if(ellapsedTime >= 1){

            float res = ellapsedTime / nbFrames;

            if(res > 0.04){
                std::cout << "Warning ! : ";
            }

            std::cout << res << " sec" << std::endl;
            std::cout << 1 / res << " fps" << std::endl<< std::endl;



            nbFrames = 0;

            lastTime = windowManager.getTime();
        }

        ellapsedTime = windowManager.getTime() - startTime;

        if(ellapsedTime < FRAMERATE_MILLISECONDS){
            SDL_Delay(FRAMERATE_MILLISECONDS - ellapsedTime);
        }

        // Update the display
        windowManager.swapBuffers();


    }    

    glDeleteBuffers(1, &vbo_cube_position);
    glDeleteBuffers(1, &vbo_cube_color);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}

