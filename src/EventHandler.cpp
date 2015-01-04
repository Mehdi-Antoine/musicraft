#include <iostream>
#include "include/World.hpp"
#include "include/EventHandler.hpp"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 700
#define COIN 50

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

    //Saut et sprint
    if(m_input.getKey(SDLK_SPACE) == true) {
        fly = true;
        
    }
    if(m_input.getKey(SDLK_RSHIFT) == true) {
        run = true;
    }

    //Marche avant arri�re
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

    //Click Gauche --> Pick Cube
    if(m_input.getMouse(1) == true){
        m_player_manager.getPlayer().pickCube(world);
    }


    //mousemotion orientation camera
    int click = 0;
    if(m_input.getMouse(1) == true){
        //std::cout << "m_input.getMouse(1) == true" << std::endl;
        click = 1;
    }
    else click = 0;


    if(m_input.getMouseRel(0) != 0 && m_input.getMouseRel(0) != -1 && m_input.getMouseRel(0) != 1){
        m_player_manager.getPlayer().getBody().getCamera().rotateLeft(-m_input.getMouseRel(0)/2.);
    }
    /*else if( (m_input.getMousePos(0) < COIN || m_input.getMousePos(0) > (WINDOW_WIDTH - COIN) ) && m_input.getMouseRel(0) != 0){
        m_player_manager.getPlayer().getBody().getCamera().rotateLeft(-m_input.getMouseRel(0)/2.);
    }*/
    if(m_input.getMouseRel(1) != 0 && m_input.getMouseRel(1) != -1 && m_input.getMouseRel(1) != 1 ){
        m_player_manager.getPlayer().getBody().getCamera().rotateUp(-m_input.getMouseRel(1)/2.);
    }
    /*else if( (m_input.getMousePos(1) < COIN || m_input.getMousePos(1) > (WINDOW_HEIGHT - COIN) ) && m_input.getMouseRel(1) != 0){
        m_player_manager.getPlayer().getBody().getCamera().rotateUp(-m_input.getMouseRel(1)/2.);
    }*/

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
