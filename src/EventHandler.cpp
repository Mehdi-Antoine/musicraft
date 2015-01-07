#include <iostream>
#include "include/World.hpp"
#include "include/EventHandler.hpp"
#include "include/Window.hpp"

#define COIN 30

PlayerManager& EventHandler::getPlayerManager(){
    return m_player_manager;
}


InputManager& EventHandler::getInputManager(){
    return m_input;
}

void EventHandler::updatePlayer(World &world){
    int directionFrontBack = 0;
    int directionRightLeft = 0;
    bool fly = false;
    bool run = false;

    //TAB -> show inventory
    if(m_input.getKey(SDLK_TAB) == true) {
        m_player_manager.getPlayer().getInventory().show();
    }

    //Saut et sprint
    if(m_input.getKey(SDLK_SPACE) == true) {
        fly = true;
        
    }
    if(m_input.getKey(SDLK_RSHIFT) == true) {
        run = true;
    }

    //Marche avant arrière
    if(m_input.getKey(SDLK_z) == true) {
        directionFrontBack++;
    }
    if(m_input.getKey(SDLK_s) == true) {
        directionFrontBack--;
    }

    //Marche gauche droite
    if(m_input.getKey(SDLK_q) == true) {
        directionRightLeft++;
    }
    if(m_input.getKey(SDLK_d) == true) {
        directionRightLeft--;  
    }

    //fullscreen ?
    if(m_input.getKey(SDLK_F1) == true) {
        std::cout << "Mode plein écran" << std::endl;
        world.getWindow().updateVideoMode(1);
    }
    if(m_input.getKey(SDLK_F2) == true) {
        std::cout << "Mode fenêtré" << std::endl;
        world.getWindow().updateVideoMode(2);
    }
    if(m_input.getKey(SDLK_F3) == true) {
        std::cout << "Mode 1024x768" << std::endl;
        world.getWindow().updateVideoMode(3);
    }

    //Click Gauche --> Pick Cube
    if(m_input.getMouse(1) == true){
        m_player_manager.getPlayer().pickCube(world);
    }

    //Click Droit --> Create Cube

    if(m_input.getMouse(3) == true){
        m_player_manager.getPlayer().addCube(world);
    }

    if(m_input.getMouse(3) == true){
        m_player_manager.getPlayer().addCube(world);
    }

    //Mouse wheel : change current cube in inventory
    if(m_input.getMouseWheel(0) == true){
        //m_player_manager.getPlayer().getInventory().setNextCurrentCube();
        //m_input.setMouseWheelFalse(0);
    }
    if(m_input.getMouseWheel(1) == true){
        //m_player_manager.getPlayer().getInventory().setPrevCurrentCube();
        //m_input.setMouseWheelFalse(1);
    }

    //mousemotion orientation camera
    int click = 0;
    if(m_input.getMouse(1) == true){
        //std::cout << "m_input.getMouse(1) == true" << std::endl;
        click = 1;
    }
    else click = 0;


    int WINDOW_WIDTH = world.getWindowWidth();
    int WINDOW_HEIGHT = world.getWindowHeight();
    
    float angle = 1.5;

    float rel_x = m_input.getMouseRel(0);
    float rel_y = m_input.getMouseRel(1);
    if(rel_x > angle) rel_x = angle;
    else if(rel_x < -angle) rel_x = -angle;
    if(rel_y > angle) rel_y = angle;
    else if(rel_y < -angle) rel_y = -angle;

    if(rel_x != 0 && rel_x != -1 && rel_x != 1){
        m_player_manager.getPlayer().getBody().getCamera().rotateLeft(-rel_x);
    }
    if(m_input.getMousePos(0) < 3*COIN && m_input.getMousePos(0) >= 0 && rel_x < 0){
        //std::cout << "coin gauche " <<  m_input.getMousePos(0) <<" rel: " << rel_x<< std::endl;
        m_player_manager.getPlayer().getBody().getCamera().rotateLeft(angle);
    }
    if(m_input.getMousePos(0) > (WINDOW_WIDTH - 3*COIN) && m_input.getMousePos(0) <= WINDOW_WIDTH && rel_x >= 0){
        //std::cout << "coin droit "<<  m_input.getMousePos(0) << " rel: " << rel_x << std::endl;
        m_player_manager.getPlayer().getBody().getCamera().rotateLeft(-angle);
    } 

    if(rel_y != 0 && rel_y != -1 && rel_y != 1 ){
        m_player_manager.getPlayer().getBody().getCamera().rotateUp(-rel_y);
    }
    if(m_input.getMousePos(1) < 3*COIN && m_input.getMousePos(1) >= 0 && rel_y < 0){
        m_player_manager.getPlayer().getBody().getCamera().rotateUp(angle);
        //std::cout << "coin haut "<<  m_input.getMousePos(1) << " rel: " << rel_y<< std::endl;
    }
    if(m_input.getMousePos(1) > (WINDOW_HEIGHT - 3*COIN) && m_input.getMousePos(1) <= WINDOW_HEIGHT && rel_y >= 0  ){
        m_player_manager.getPlayer().getBody().getCamera().rotateUp(-angle);
        //std::cout << "coin bas "<<  m_input.getMousePos(1) << " rel: " << rel_y << std::endl;

    }





    m_player_manager.movement(directionFrontBack, directionRightLeft);
    m_player_manager.flyAndRun(run,fly); 
    m_player_manager.getPlayer().updatePlayer(world);   
}

void EventHandler::update(){
    m_input.updateInput();
}



EventHandler::EventHandler(InputManager & input, PlayerManager & player_manager){
    m_input = input;
    m_player_manager = player_manager;
}
