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

#include "include/Chunk.hpp"

#include "include/World.hpp"
#include "include/Player.hpp"
#include "include/EventHandler.hpp"

#include <iostream>
#include <string>

using namespace glimac;

#define WINDOW_WIDTH_ 1024
#define WINDOW_HEIGHT_ 768


//--------------------------------------------------------------------------------------------------
//---------------------------------------LE MAIN----------------------------------------------------
//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv){


    int TAILLE = 20; //Taille de porc

    FilePath applicationPath(argv[0]);

    FilePath dir_path = applicationPath.dirPath();

    // Initialize SDL and open a window
    //SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "musicraft");
    SDLWindowManager windowManager(WINDOW_WIDTH_, WINDOW_HEIGHT_, "MUSICRAFT");
    const SDL_VideoInfo* info = SDL_GetVideoInfo();
    const int WINDOW_WIDTH  = info->current_w;
    const int WINDOW_HEIGHT = info->current_h; 

    std::cout << "w: " << WINDOW_WIDTH << " h: " << WINDOW_HEIGHT <<std::endl;



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

    glEnable(GL_DEPTH_TEST);

//----------------------------------GL ENVIRONNEMENT------------------------------------------------

    //GlEnvironnement gl_environnement(dir_path);

//-------------------------------CHARGEMENT DES SHADERS---------------------------------------------

    //std::vector<GlShader> shaders;

    //shaders.push_back(GlShader(dir_path, "cube"));
    //shaders.push_back(GlShader(dir_path, "square"));

    //gl_environnement.addShaderVector(shaders);

    std::cout << "CREATION SHADER..." << std::endl;

    GlShader square_shader(dir_path, "square");

    GlShader cube_shader(dir_path, "cube");

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


//--------------------------CREATION DES VARIABLES UNIFORMES----------------------------------------

    std::cout << "CREATION VARIABLE UNIFORME..." << std::endl;

    std::cout << "  GLOBAL MATRIX" << std::endl;

    glm::mat4 projection_matrix = glm::perspective(glm::radians(50.f), (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 1000.f);

    std::cout << "      création global_matrix" << std::endl;
    GlGlobalUniformMatrix global_matrix;
    std::cout << "      ok!" << std::endl;

    std::cout << "      global_matrix.init()" << std::endl;
    global_matrix.init("global_matrix", 1);
    std::cout << "      ok!" << std::endl;

    std::cout << "      global_matrix.attachProgram" << std::endl;
    global_matrix.attachProgram(square_shader.getProgramId());
    global_matrix.attachProgram(cube_shader.getProgramId());
    std::cout << "      ok!" << std::endl;

    std::cout << "      global_matrix.updateProjectionMatrix()" << std::endl;
    global_matrix.updateProjectionMatrix(projection_matrix);
    std::cout << "      ok!" << std::endl;


    std::cout << "  GLOBAL LIGHT" << std::endl;

    std::cout << "      création global_light" << std::endl;
    GlGlobalUniformLight global_light;
    std::cout << "      ok!" << std::endl;

    std::cout << "      global_light.init()" << std::endl;
    global_light.init("global_light", 2);
    std::cout << "      ok!" << std::endl;

    std::cout << "      global_light.attachProgram" << std::endl;
    global_light.attachProgram(square_shader.getProgramId());
    global_light.attachProgram(cube_shader.getProgramId());
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

    std::vector<glm::vec3> cube_color;
    std::vector<glm::vec3> cube_position;

//-----------------------------------CREATION CHUNK-------------------------------------------------

    Chunk chunk;

    char cubeType;

    for (int x = 0; x < 32; ++x)
    {
        for (int z = 0; z < 32; ++z)
        {   
            int y = 0;

            cubeType = x % 2 + 1;
            chunk.setCubeType(x, y, z, cubeType);
            cube_position.push_back(glm::vec3(x * 2, y * 2, z * 2));  
            cube_color.push_back(glm::vec3(cubeType-1, cubeType, 0));      
        }
    }

    for (int x = 0; x < 32; ++x)
    { 
        int y = 1;
        int z = 0;

        cubeType = x % 2 + 1;

        chunk.setCubeType(x, y, z, cubeType);
        cube_position.push_back(glm::vec3(x * 2, y * 2, z * 2));
        cube_color.push_back(glm::vec3(cubeType-1, cubeType, 0));          
    }
    for (int x = 0; x < 32; ++x)
    {   
        int z = 31;
        for(int y = 1; y < 4; ++y){
            cubeType = x % 2 + 1;

            chunk.setCubeType(x, y, z, cubeType);
            cube_position.push_back(glm::vec3(x * 2, y * 2, z * 2)); 
            cube_color.push_back(glm::vec3(cubeType-1, cubeType, 0));  
        }              
    }
    
    for (int z = 0; z < 32; ++z)
    {   
        int x = 0;
        int y = 1;

        cubeType = x % 2 + 1;

        chunk.setCubeType(x, y, z, cubeType);
        cube_position.push_back(glm::vec3(x * 2, y * 2, z * 2)); 
        cube_color.push_back(glm::vec3(cubeType-1, cubeType, 0));        
    }

    for (int z = 0; z < 32 ; ++z)
    {   
        int x = 31;
        int y = 1;

        cubeType = x % 2 + 1;

        chunk.setCubeType(x, y, z, cubeType);
        cube_position.push_back(glm::vec3(x * 2, y * 2, z * 2));  
        cube_color.push_back(glm::vec3(cubeType-1, cubeType, 0));       
    }


//-----------------------------------WORLD CREATION-------------------------------------------------

    World world(WINDOW_WIDTH,WINDOW_HEIGHT);

    world.addChunk(chunk);

//-----------------------------CHARGEMENT DU VBO ET DU VAO------------------------------------------

    std::cout << "CHARGEMENT VBO/VAO DU SOL..." << std::endl;
    GlElement ground(cube_position, cube_color, SQUARE, GL_POINTS); //On charge ce vector dans un vbo
    std::cout << "OK." << std::endl << std::endl;

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

//-----------------------------------------------------------------------------------------------------
//----------------------------------APPLICATION LOOP---------------------------------------------------
//-----------------------------------------------------------------------------------------------------

    bool quit = false;

    while(!quit){

        startTime = windowManager.getTime();

//-----------------------------------EVENT HANDLER-----------------------------------------------------
        eventhandler.update();
        eventhandler.updatePlayer(world);

        //quit ?
        if(eventhandler.getInputManager().getQuit() == true) quit=true;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


//---------------------------------CONSTRUCT V MATRIX--------------------------------------------------

        glm::mat4 view_matrix = eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getViewMatrix();

        glm::vec3 camera_position = eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition();

//----------------------------------UPDATE UNIFORMS----------------------------------------------------

        global_matrix.updateViewMatrix(view_matrix);

//---------------------------------------DRAW !!!!-----------------------------------------------------
    
        texture_sting.use(GL_TEXTURE0);
        texture_rouge.use(GL_TEXTURE1);

        cube_shader.useShader();
        ground.draw();

        texture_sting.stopUse(GL_TEXTURE0);
        texture_rouge.stopUse(GL_TEXTURE1);

//---------------------------------------FPS SHOW------------------------------------------------------
        ++nbFrames;

        currentTime = windowManager.getTime();

        float ellapsedTime = currentTime - lastTime;

        if(ellapsedTime >= 1){

            float res = ellapsedTime / nbFrames;

           if(res > 0.04){
                std::cout << "Warning ! : ";
            }

            //std::cout << res << " sec" << std::endl;
            //std::cout << 1 / res << " fps" << std::endl<< std::endl;

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

