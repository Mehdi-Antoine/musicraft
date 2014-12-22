#include "include/PlayerManager.hpp"

#include <iostream>

void PlayerManager::movement(int directionFrontBack, int directionRightLeft)
{
    m_player.moveFront(directionFrontBack);
    m_player.moveLeft(directionRightLeft);
}

void PlayerManager::flyAndRun(bool run, bool fly) {
    m_player.run(run);
    m_player.jetpack(fly);
}

Player& PlayerManager::getPlayer() {
	return m_player;
}

PlayerManager::PlayerManager(Player &player):m_player(player)
{
}

PlayerManager::PlayerManager(PlayerManager & playermanager)
{
	m_player = playermanager.getPlayer();
}

PlayerManager::PlayerManager()
{
}

