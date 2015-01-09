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

    GlShader2D flat_shader(dir_path, "2d");

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


//-----------------------------------CHUNKS CREATION------------------------------------------------

    std::vector<glm::vec3> cube_color;
    std::vector<glm::vec3> cube_position;

    Chunk chunk_norris = Chunk(1245, glm::vec3(0,0,0));

    chunk_norris.root.genAllCoordinates(pow(2,(float)chunk_norris.profondeur), 0, chunk_norris.profondeur);


    chunk_norris.lighten();
/*
    cube_position = chunk_norris.getAllCoordinates();
    std::cout << "Count lightened: " << cube_position.size()<< std::endl;

    srand(0);


    for(unsigned int i = 0; i < cube_position.size(); ++i){
        int cube_type_rand = rand()%(4-1) +1;
        glm::vec3 vec_cube_color = Chunk::getColorFromType(cube_type_rand);
        cube_color.push_back(vec_cube_color);
    }*/

    glEnable(GL_DEPTH_TEST);



//-----------------------------------WORLD CREATION-------------------------------------------------

    Window window(WINDOW_WIDTH,WINDOW_HEIGHT);
    World world(window);

    world.addChunk(chunk_norris);

    world.createCoordinates(cube_position, cube_color);

//-----------------------------------CIBE CREATION--------------------------------------------------

    std::vector<glm::vec3>cible_position;
    std::vector<glm::vec3>cible_color;

    cible_position.push_back(glm::vec3(0,     0.01,    0));
    cible_position.push_back(glm::vec3(0,     0.02,     0));

    cible_position.push_back(glm::vec3(0.01,  0,       0));
    cible_position.push_back(glm::vec3(0.02,   0,       0));

    cible_position.push_back(glm::vec3(0,     -0.01,   0));
    cible_position.push_back(glm::vec3(0,     -0.02,    0));

    cible_position.push_back(glm::vec3(-0.01,  0,      0));
    cible_position.push_back(glm::vec3(-0.02,   0,      0));

    cible_color.push_back(glm::vec3(1, 1, 1));
    cible_color.push_back(glm::vec3(1, 1, 1));
    cible_color.push_back(glm::vec3(1, 1, 1));
    cible_color.push_back(glm::vec3(1, 1, 1));
    cible_color.push_back(glm::vec3(1, 1, 1));
    cible_color.push_back(glm::vec3(1, 1, 1));
    cible_color.push_back(glm::vec3(1, 1, 1));
    cible_color.push_back(glm::vec3(1, 1, 1));   

    GlElement cible(cible_position, cible_color, SQUARE , GL_LINES);

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

        glm::vec3 front_vector = eventhandler.getPlayerManager().getPlayer().getBody().getCamera().getFrontVector();

//----------------------------------UPDATE UNIFORMS----------------------------------------------------

        global_matrix.updateViewMatrix(view_matrix);

        global_vec4.updateCameraPosition(camera_position);

        global_vec4.updateCameraFrontVector(front_vector);


        //std::cout << front_vector << std::endl;

//------------------------------------UPDATE VBO-------------------------------------------------------

        cube_position.clear();
        cube_color.clear();
        
        //cube_position = world.getChunk(0).getAllCoordinates();
        world.createCoordinates(cube_position, cube_color);
        //world.getChunk(0).lighten();
        ground.update(cube_position, cube_color);

//---------------------------------------DRAW !!!!-----------------------------------------------------
        
        glActiveTexture(GL_TEXTURE0);
        texture_tron.bind();

        glActiveTexture(GL_TEXTURE1);
        texture_grille.bind();


        cube_shader.useShader();
        ground.draw();

        flat_shader.useShader();
        cible.draw();

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
