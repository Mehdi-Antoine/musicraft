#ifndef EventHandler_h
#define EventHandler_h

#include "InputManager.hpp"
#include "PlayerManager.hpp"
#include "World.hpp"


class EventHandler {


public:

	PlayerManager& getPlayerManager();
	InputManager& getInputManager();

	void update();

    void updatePlayer(World &world);

    EventHandler(InputManager & input, PlayerManager & player_manager);


private:
    InputManager m_input;
    PlayerManager m_player_manager;
};

#endif // EventHandler_h
