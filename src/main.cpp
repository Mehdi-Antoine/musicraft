#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/FreeflyCamera.hpp>

#include "include/Window.hpp"

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

    FilePath applicationPath(argv[0]);

    FilePath dir_path = applicationPath.dirPath();

    // Initialize SDL and open a window
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


//----------------------------------GL ENVIRONNEMENT------------------------------------------------

    //GlEnvironnement gl_environnement(dir_path);

//-------------------------------CHARGEMENT DES SHADERS---------------------------------------------

    std::cout << "CREATION SHADER..." << std::endl;

    GlShader square_shader(dir_path, "square");

    GlShader cube_shader(dir_path, "cube");

    std::cout << "OK." << std::endl << std::endl;


    cube_shader.useShader();

//-------------------------------CHARGEMENT DES TEXTURES---------------------------------------------

    std::cout << "CREATION TEXTURE..." << std::endl;

    GlTexture texture_sting(dir_path + "assets/textures/sting.jpg");
    GlTexture texture_rouge(dir_path + "assets/textures/rouge01.jpg");
    GlTexture texture_tron(dir_path + "assets/textures/tron01.jpg");
    GlTexture texture_grille(dir_path + "assets/textures/grille.jpg");

    std::cout << "OK." << std::endl << std::endl;

    cube_shader.attachTexture("texture0", 0);
    cube_shader.attachTexture("texture1", 1);

//--------------------------CREATION DES VARIABLES UNIFORMES----------------------------------------

    std::cout << "CREATION VARIABLE UNIFORME..." << std::endl;

    std::cout << "  GLOBAL MATRIX" << std::endl;

    GlGlobalUniformMatrix global_matrix;

    global_matrix.init("global_matrix", 1);

    global_matrix.attachProgram(square_shader.getProgramId());
    global_matrix.attachProgram(cube_shader.getProgramId());

    glm::mat4 projection_matrix = glm::perspective(glm::radians(45.f), (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 1000.f);
    global_matrix.updateProjectionMatrix(projection_matrix);


    std::cout << "  GLOBAL VEC3" << std::endl;

    GlGlobalUniformVec4 global_vec4;

    global_vec4.init("global_vec4", 3);

    global_vec4.attachProgram(square_shader.getProgramId());
    global_vec4.attachProgram(cube_shader.getProgramId());


    glm::vec4 light_position  = vec4(SIZE/2, 100, SIZE, 0);
    glm::vec3 light_intensity = vec3(0.4, 0.4, 0.4);
    glm::vec3 light_ks        = vec3(1, 1, 1);

    global_vec4.updateLightPosition(light_position);
    global_vec4.updateLightIntensity(light_intensity);
    global_vec4.updateLightKs(light_ks);


    std::cout << "OK." << std::endl << std::endl;

    glEnable(GL_DEPTH_TEST);

//------------------------------CREATION CHUNK / GL_CHUNK-------------------------------------------
    
    //std::cout << "CHARGEMENT VBO/VAO DU SOL..." << std::endl;

    // std::vector<GlElement*> gl_chunks;

    // //CHUNK0
    // Chunk chunk0 = World::createFlatChunk(BASIC1, glm::vec3(0,0,0));

    // world.addChunk(chunk0);  

    GlElement ground(GL_POINTS);
    //GlElement ground2(GL_POINTS);
    //ground.update(cube_position, cube_color);

    // gl_chunks.push_back(&gl_chunk0);


    // //CHUNK1
    // Chunk chunk1 = World::createFlatChunk(BASIC1, glm::vec3(SIZE,0,SIZE));
    // world.addChunk(chunk1);  

    // GlElement gl_chunk1(GL_POINTS);

    // gl_chunks.push_back(&gl_chunk1);


    // //CHUNK2
    // Chunk chunk2 = World::createFlatChunk(BASIC3, glm::vec3(SIZE,0,0));
    // world.addChunk(chunk2);  

    // GlElement gl_chunk2(GL_POINTS);

    // gl_chunks.push_back(&gl_chunk2);

    // //CHUNK3
    // Chunk chunk3 = World::createFlatChunk(BASIC2, glm::vec3(0,0,SIZE));
    // world.addChunk(chunk3);  

    // GlElement gl_chunk3(GL_POINTS);


    // gl_chunks.push_back(&gl_chunk3);

   /* world.addChunk(chunk_norris);
    world.addChunk(chunky);*/

    /*for(int i = 0; i< gl_chunks.size(); ++i){
        world.updateGlElement(*gl_chunks[i], i);
    }*/
    
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

//-----------------------------------WORLD CREATION-------------------------------------------------

    Window window(WINDOW_WIDTH,WINDOW_HEIGHT);
    World world(window);

    std::vector<glm::vec3> cube_color;
    std::vector<glm::vec3> cube_position;
    glm::vec3 pl = eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition();
    world.createMap(pl);
    world.updateMap(pl);
    world.createCoordinates(cube_position, cube_color);

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

        glm::vec3 front_vector = eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getFrontVector();

//----------------------------------UPDATE UNIFORMS----------------------------------------------------

        global_matrix.updateViewMatrix(view_matrix);

        global_vec4.updateCameraPosition(camera_position);

        global_vec4.updateCameraFrontVector(front_vector);

        //std::cout << World::getChunkCoord(camera_position)<<std::endl;




//----------------------------------UPDATE VBO----------------------------------------------------
        cube_position.clear();
        cube_color.clear();

        pl = eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getPosition();
        world.updateMap(pl);
        world.createCoordinates(cube_position, cube_color);
        ground.update(cube_position, cube_color);

        /*cube_position2.clear();
        cube_color2.clear();
        world.getChunk(1).lighten();

        cube_position2 = world.getChunk(1).getAllCoordinates();
        ground2.update(cube_position2, cube_color2);*/


//------------------------------------UPDATE VBO-------------------------------------------------------


        // std::cout << "chunk : " << world.getChunkCoord(camera_position) << std::endl;
        // std::cout << "player in world: " << camera_position << std::endl;
        // std::cout << "player in chunk: " << world.getLocalPosition(camera_position) << std::endl;


        //world.updateGlChunks(gl_chunks);
        //for(int i = 0; i<gl_chunks.size(); ++i){
        //world.updateGlElement(gl_chunks[0], 0);
        //}

//---------------------------------------DRAW !!!!-----------------------------------------------------
        
        glActiveTexture(GL_TEXTURE0);
        texture_tron.bind();
        glActiveTexture(GL_TEXTURE1);
        texture_grille.bind();

        cube_shader.useShader();
        ground.draw();
        //ground2.draw();
        //world.drawWorld(gl_chunks);

        glActiveTexture(GL_TEXTURE0);
        texture_tron.unbind();
        glActiveTexture(GL_TEXTURE1);
        texture_sting.unbind();

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

