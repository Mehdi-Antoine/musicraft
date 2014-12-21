#include "include/EventHandler.h"



void EventHandler::updatePlayer()
{
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

    m_player_manager.movement(directionFrontBack, directionRightLeft);
    m_player_manager.flyAndRun(run,fly);

}

void EventHandler::update()
{
    m_input.updateInput();
}

EventHandler::EventHandler()
{
}
