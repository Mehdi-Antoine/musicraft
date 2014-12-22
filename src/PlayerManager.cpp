#include "include/PlayerManager.h"



void PlayerManager::movement(int directionFrontBack, int directionRightLeft)
{
    m_player.moveFront(directionFrontBack);
    m_player.moveLeft(directionRightLeft);
}

void PlayerManager::flyAndRun(bool run, bool fly) {
    m_player.run(run);
    m_player.jetpack(fly);
}

PlayerManager::PlayerManager(Player player)
{
    m_player = player;
}
