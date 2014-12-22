#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/FreeflyCamera.hpp>

#include "include/GlEnvironnement.hpp"
#include "include/GlElement.hpp"
#include "include/GlShader.hpp"
#include "include/GlLight.hpp"
#include "include/GlUniform.hpp"
#include "include/GlTexture.hpp"

#include "include/World.hpp"
#include "include/Player.hpp"

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

    FilePath applicationPath(argv[0]);

    FilePath dir_path = applicationPath.dirPath();

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

//-----------------------------------WORLD CREATION------------------------------------------------

    World world;

//----------------------------------GL ENVIRONNEMENT------------------------------------------------

    GlEnvironnement gl_environnement(dir_path);

//-------------------------------CHARGEMENT DES SHADERS---------------------------------------------

    std::vector<GlShader> shaders;

    shaders.push_back(GlShader(dir_path + "cube"));
    shaders.push_back(GlShader(dir_path + "square"));

    gl_environnement.addShaderVector(shaders);

//-------------------------------CHARGEMENT DES TEXTURES---------------------------------------------

    std::vector<GlTexture> textures;

    //GlTexture sting(dir_path + "assets/textures/sting.jpg");
    //textures.push_back(sting);
    textures.push_back(GlTexture(dir_path + "assets/textures/triforce.png"));

    gl_environnement.addTextureVector(textures);

    
//---------------------------------CONSTRUCTION CAMERA----------------------------------------------

    FreeflyCamera freeflyCamera;

//--------------------------CREATION DES VARIABLES UNIFORMES----------------------------------------

    glm::mat4 view_matrix = freeflyCamera.getViewMatrix();
    glm::mat4 projection_matrix = glm::perspective(glm::radians(50.f), (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 1000.f);

    gl_environnement.updateViewMatrix(view_matrix);
    gl_environnement.updateProjectionMatrix(view_matrix);

//-----------------------------CHARGEMENT DU VBO ET DU VAO------------------------------------------

    GlElement ground(square_positions, square_colors, SQUARE, GL_POINTS);
    GlElement music_cubes(cube_positions, cube_colors, CUBE, GL_POINTS);

    gl_environnement.addElement(ground);
    gl_environnement.addElement(music_cubes);
 
//--------------------------------------------------------------------------------------------------
//----------------------------------APPLICATION LOOP------------------------------------------------
//--------------------------------------------------------------------------------------------------

    bool done = false;

    while(!done){

        startTime = windowManager.getTime();

//--------------------------------------CONTROLS----------------------------------------------------
        

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
//---------------------------------CONSTRUCT V MATRIX-----------------------------------------------

        gl_environnement.update(world);


//---------------------------------------DRAW !!!!-----------------------------------------------------
        
        gl_environnement.draw();

//---------------------------------------FPS SHOW------------------------------------------------------
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

//-----------------------------------FPS FREEZE-------------------------------------------------------
        ellapsedTime = windowManager.getTime() - startTime;

        if(ellapsedTime < FRAMERATE_MILLISECONDS){
            SDL_Delay(FRAMERATE_MILLISECONDS - ellapsedTime);
        }

        // Update the display
        windowManager.swapBuffers();


    }    

//-----------------------------------VBO CLEAN-------------------------------------------------------

    return EXIT_SUCCESS;
}

