#include <iostream>
#include "include/EventHandler.hpp"


PlayerManager& EventHandler::getPlayerManager(){
    return m_player_manager;
}


InputManager& EventHandler::getInputManager(){
    return m_input;
}

void EventHandler::updatePlayer(){
    int directionFrontBack = 0;
    int directionRightLeft = 0;
    bool fly = false;
    bool run = false;

    //m_player_manager.movement(directionFrontBack, directionRightLeft);
    //m_player_manager.flyAndRun(run,fly);

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


    //mousemotion orientation camera
    int click = 0;
    if(m_input.getMouse(1) == true){
        //std::cout << "m_input.getMouse(1) == true" << std::endl;
        click = 1;
    }
    else click = 0;

    if(m_input.getMouseRel(0) != 0 && click == 1) {
        //std::cout << "getMouseRel(0) X= " << m_input.getMouseRel(0) <<std::endl;
        m_player_manager.getPlayer().getBody().getCamera().rotateLeft(- m_input.getMouseRel(0) /2.);
    }
    if(m_input.getMouseRel(1) != 0 && click == 1) {
        //std::cout << "getMouseRel(1) Y= "<< m_input.getMouseRel(1) << std::endl;   
        m_player_manager.getPlayer().getBody().getCamera().rotateUp(- m_input.getMouseRel(1) /2.);
    }





    m_player_manager.movement(directionFrontBack, directionRightLeft);
    m_player_manager.flyAndRun(run,fly);

    m_player_manager.getPlayer().updatePlayer();   
}

void EventHandler::update(){
    m_input.updateInput();
}



EventHandler::EventHandler(InputManager & input, PlayerManager & player_manager){
    m_input = input;
    m_player_manager = player_manager;
}
