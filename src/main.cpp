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
#include "include/GlUniform.hpp"
#include "include/GlTexture.hpp"

#include "include/World.hpp"
#include "include/Player.hpp"
<<<<<<< HEAD
#include "include/EventHandler.hpp"
#include "include/GlslPrograms.hpp"
=======
>>>>>>> gl_environnement

#include <iostream>
#include <string>

using namespace glimac;

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 700

//--------------------------------------------------------------------------------------------------
//---------------------------------------LE MAIN----------------------------------------------------
//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv){

    int TAILLE = 20; //Taille de porc

    FilePath applicationPath(argv[0]);

    FilePath dir_path = applicationPath.dirPath();

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

    std::cout << std::endl;
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl << std::endl;

//-----------------------------------WORLD CREATION------------------------------------------------

    //World world;

//----------------------------------GL ENVIRONNEMENT------------------------------------------------

    //GlEnvironnement gl_environnement(dir_path);

//-------------------------------CHARGEMENT DES SHADERS---------------------------------------------

    //std::vector<GlShader> shaders;

    //shaders.push_back(GlShader(dir_path, "cube"));
    //shaders.push_back(GlShader(dir_path, "square"));

    //gl_environnement.addShaderVector(shaders);

    std::cout << "CREATION SHADER..." << std::endl;

    GlShader square_shader(dir_path, "square");

    square_shader.useShader();

    std::cout << "OK." << std::endl << std::endl;

//-------------------------------CHARGEMENT DES TEXTURES---------------------------------------------

    //std::vector<GlTexture> textures;

    //textures.push_back(GlTexture(dir_path + "assets/textures/triforce.png"));
    //textures.push_back(GlTexture(dir_path + "assets/textures/sting.jpg"));

    //gl_environnement.addTextureVector(textures);

    std::cout << "CREATION TEXTURE..." << std::endl;

    GlTexture texture_sting(dir_path + "assets/textures/sting.jpg");
    GlTexture texture_rouge(dir_path + "assets/textures/rouge01.jpg");

    std::cout << "OK." << std::endl << std::endl;

<<<<<<< HEAD
    glm::vec3 cube_color[TAILLE*TAILLE];
    glm::vec3 cube_position[TAILLE*TAILLE];
    
    for(int k=0; k < TAILLE * TAILLE; ++k){
        cube_position[k] = glm::vec3(2*(k/TAILLE), 0, 2*(k%TAILLE));
        cube_color[k]    = glm::vec3(k/TAILLE, 0, k%TAILLE);
    }
    
=======
//---------------------------------CONSTRUCTION CAMERA----------------------------------------------
>>>>>>> gl_environnement




//--------------------------CREATION DES VARIABLES UNIFORMES----------------------------------------

    std::cout << "CREATION VARIABLE UNIFORME..." << std::endl;

    std::cout << "  GLOBAL MATRIX" << std::endl;

    glm::mat4 view_matrix = freeflyCamera.getViewMatrix();
    glm::mat4 projection_matrix = glm::perspective(glm::radians(50.f), (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 1000.f);
    glm::vec3 camera_position = freeflyCamera.getPosition();

    std::cout << "      création global_matrix" << std::endl;
    GlGlobalUniformMatrix global_matrix;
    std::cout << "      ok!" << std::endl;

    std::cout << "      global_matrix.init()" << std::endl;
    global_matrix.init("global_matrix", 1);
    std::cout << "      ok!" << std::endl;

    std::cout << "      global_matrix.attachProgram(square_shader)" << std::endl;
    global_matrix.attachProgram(square_shader.getProgramId());
    std::cout << "      ok!" << std::endl;

    std::cout << "      global_matrix.update()" << std::endl;
    global_matrix.update(projection_matrix, view_matrix, camera_position);
    std::cout << "      ok!" << std::endl;


    std::cout << "  GLOBAL LIGHT" << std::endl;

    std::cout << "      création global_light" << std::endl;
    GlGlobalUniformLight global_light;
    std::cout << "      ok!" << std::endl;

    std::cout << "      global_light.init()" << std::endl;
    global_light.init("global_light", 2);
    std::cout << "      ok!" << std::endl;

    std::cout << "      global_light.attachProgram(square_shader)" << std::endl;
    global_light.attachProgram(square_shader.getProgramId());
    std::cout << "      ok!" << std::endl;

    std::cout << "      global_light.update()" << std::endl;

    glm::vec3 position  = vec3(1, 1, 1);
    glm::vec3 intensity = vec3(0, 0, 0);
    glm::vec3 ks        = vec3(1, 0, 1);
    float shininess     = 1;


    global_light.update(position, intensity, ks, shininess);
    std::cout << "      ok!" << std::endl;

    std::cout << "OK." << std::endl << std::endl;

//-------------CONSTRUCTION CUBE ET INJECTION DANS UN TABLEAU DE VERTICES---------------------------

    std::cout << "CREATION INDICES CUBES..." << std::endl;
    std::vector<glm::vec3> squares_color;
    std::vector<glm::vec3> squares_position;

    for (int k = 0; k < TAILLE * TAILLE; ++k){
        squares_position.push_back(glm::vec3(2*(k/TAILLE), 0, 2*(k%TAILLE)));        
        squares_color.push_back(glm::vec3(k/TAILLE, 0, k%TAILLE));
    }
    std::cout << "OK." << std::endl << std::endl;

<<<<<<< HEAD
    glBindVertexArray(0);
    
/*DEBUT MODIF MOTEUR BASIQUE*/
=======
//-----------------------------CHARGEMENT DU VBO ET DU VAO------------------------------------------

    std::cout << "CHARGEMENT VBO/VAO DU SOL..." << std::endl;
    GlElement ground(squares_position, squares_color, SQUARE, GL_POINTS);
    std::cout << "OK." << std::endl << std::endl;
>>>>>>> gl_environnement

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

    Camera freeflycamera;
//--------------------------------------------------------------------------------------------------
//----------------------------------APPLICATION LOOP------------------------------------------------
//--------------------------------------------------------------------------------------------------

    bool quit = false;

    while(!quit){

        startTime = windowManager.getTime();

<<<<<<< HEAD
=======
//--------------------------------------CONTROLS----------------------------------------------------
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
>>>>>>> gl_environnement

    //event loop
        eventhandler.update();
        eventhandler.updatePlayer();

        //quit ?
        if(eventhandler.getInputManager().getQuit() == true) quit=true;
            

/*FIN MODIF MOTEUR BASIQUE*/

          //std::cout << "position body: " <<  eventhandler.getPlayerManager().getPlayer().getBody().getPosition().x << " " <<  eventhandler.getPlayerManager().getPlayer().getBody().getPosition().y << " " << eventhandler.getPlayerManager().getPlayer().getBody().getPosition().z << std::endl;
          //std::cout << "position camera: " <<  eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition().x << " " <<  eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition().y << " " << eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition().z << std::endl;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
<<<<<<< HEAD
        //CONSTRUCTION MATRICE V
        VMatrix = eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getViewMatrix();

        glm::vec3 cameraPos = eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition();
        glUniform3fv(squareProgram.uCameraPos, 1, glm::value_ptr(cameraPos));

//std::cout << "-> " << eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getFrontVector() << std::endl;


        //GESTION LIGHT
        lightPos = glm::vec3(glm::vec4(TAILLE, TAILLE, TAILLE, 1));
=======
//---------------------------------CONSTRUCT V MATRIX-----------------------------------------------
>>>>>>> gl_environnement

        //gl_environnement.update(world);


//---------------------------------------DRAW !!!!-----------------------------------------------------
        
        //gl_environnement.draw();

        global_matrix.updateViewMatrix(freeflyCamera.getViewMatrix());

        //texture_sting.use(GL_TEXTURE0);
        texture_rouge.use(GL_TEXTURE0);

        ground.draw();

        texture_rouge.stopUse(GL_TEXTURE0);

//---------------------------------------FPS SHOW------------------------------------------------------
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
<<<<<<< HEAD
            */

=======

            std::cout << "camera : " << freeflyCamera.getPosition() << std::endl;
>>>>>>> gl_environnement

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

