#ifndef EventHandler_h
#define EventHandler_h

#include "InputManager.hpp"
#include "PlayerManager.hpp"


class EventHandler {


public:

    void updatePlayer();

    void update();

    EventHandler(InputManager input, PlayerManager player_manager);


private:
    InputManager m_input;
    PlayerManager m_player_manager;
};

#endif // EventHandler_h
