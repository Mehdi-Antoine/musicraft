#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/FreeflyCamera.hpp>

#include "include/Player.hpp"
#include "include/EventHandler.hpp"
#include "include/GlslPrograms.hpp"

#include <iostream>
#include <string>

using namespace glimac;

#define WINDOW_WIDTH  700
#define WINDOW_HEIGHT 700

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

    SquareProgram squareProgram(applicationPath);

    squareProgram.m_Program.use();

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
//--------------------------CREATION DES VARIABLES UNIFORMES----------------------------------------
//--------------------------------------------------------------------------------------------------

    glEnable(GL_DEPTH_TEST);

    glm::mat4  ProjMatrix, 
               VMatrix;
    

    ProjMatrix = glm::perspective(glm::radians(50.f), (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 1000.f);

    glUniformMatrix4fv(squareProgram.uPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix));


    glm::vec3  lightPos = glm::vec3(1, 1, 1);

    glUniform3f(squareProgram.uKd, 1, 1, 1);
    glUniform3f(squareProgram.uKs, 1, 1, 1);
    glUniform1f(squareProgram.uShininess, 1);

    glUniform3f(squareProgram.uLightIntensity, 1, 1, 1);
    glUniform3f(squareProgram.uLightPos, 1, 1, 1);

    glUniform1i(squareProgram.uTexture, 0);

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
//---------------------------------CONSTRUCTION PLAYER----------------------------------------------
//--------------------------------------------------------------------------------------------------
    Player player(7);

    Camera camera = player.getBody().getCamera();

    PlayerManager playermanager(player);

    InputManager inputmanager;
    EventHandler eventhandler(inputmanager, playermanager);
    std::cout << "position body: " <<  eventhandler.getPlayerManager().getPlayer().getBody().getPosition().x << " " <<  eventhandler.getPlayerManager().getPlayer().getBody().getPosition().y << " " << eventhandler.getPlayerManager().getPlayer().getBody().getPosition().z << std::endl;
    std::cout << "position camera: " <<  eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition().x << " " <<  eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition().y << " " << eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition().z << std::endl;


//--------------------------------------------------------------------------------------------------
//----------------------------------APPLICATION LOOP------------------------------------------------
//--------------------------------------------------------------------------------------------------

    bool done = false;

    while(!done){

        startTime = windowManager.getTime();

    //event loop
          eventhandler.update();
          eventhandler.updatePlayer();
         
          std::cout << "position body: " <<  eventhandler.getPlayerManager().getPlayer().getBody().getPosition().x << " " <<  eventhandler.getPlayerManager().getPlayer().getBody().getPosition().y << " " << eventhandler.getPlayerManager().getPlayer().getBody().getPosition().z << std::endl;
          std::cout << "position camera: " <<  eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition().x << " " <<  eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition().y << " " << eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition().z << std::endl;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        //CONSTRUCTION MATRICE V
        VMatrix = eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getViewMatrix();

        glm::vec3 cameraPos = eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition();
        glUniform3fv(squareProgram.uCameraPos, 1, glm::value_ptr(cameraPos));

        //GESTION LIGHT
        lightPos = glm::vec3(glm::vec4(TAILLE, TAILLE, TAILLE, 1));

        glUniformMatrix4fv(squareProgram.uVMatrix,    1, GL_FALSE, glm::value_ptr(VMatrix));
        glUniformMatrix4fv(squareProgram.uPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix));

        glUniform3f(squareProgram.uKd, 1, 1, 1);
        glUniform3f(squareProgram.uKs, 1, 1, 1);
        glUniform1f(squareProgram.uShininess, 1);

        glUniform3f(squareProgram.uLightIntensity, TAILLE * 10, TAILLE * 10, TAILLE * 10);
        glUniform3f(squareProgram.uLightPos, lightPos.x, lightPos.y, lightPos.z);

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

           /* if(res > 0.04){
                std::cout << "Warning ! : ";
            }

            std::cout << res << " sec" << std::endl;
            std::cout << 1 / res << " fps" << std::endl<< std::endl;
            */


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

