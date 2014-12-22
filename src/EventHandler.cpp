#include <iostream>
#include "include/EventHandler.hpp"


PlayerManager EventHandler::getPlayerManager(){
    return m_player_manager;
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
        std::cout << "Z" << std::endl;
        directionFrontBack++;
    }
    if(m_input.getKey(SDLK_s) == true) {
        std::cout << "S" << std::endl;
        directionFrontBack--;
    }

    //Marche gauche droite
    if(m_input.getKey(SDLK_q) == true) {
        std::cout << "Q" << std::endl;
        directionRightLeft++;
    }
    if(m_input.getKey(SDLK_d) == true) {
        std::cout << "D" << std::endl;
        directionRightLeft--;
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
