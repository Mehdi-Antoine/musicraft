#ifndef EventHandler_h
#define EventHandler_h

#include "InputManager.h"
#include "PlayerManager.h"


class EventHandler {

public:

    void updatePlayer();

    void update();

    EventHandler();


private:
    InputManager m_input;
    PlayerManager m_player_manager;
};

#endif // EventHandler_h
