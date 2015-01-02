#include "include/Player.hpp"
#include "include/Body.hpp"
#include "include/Physic.hpp"
#include <glimac/glm.hpp>
#include <vector>
#include <iostream>


// Constructors/Destructors
//  

Player::Player(){
	m_dir_x = 0;
	m_dir_z = 0;
	m_is_running = false;
	m_is_flying = false;
	m_name = 47;
}

Player::Player(Player & player){
	m_dir_x = player.getDirX();
	m_dir_z = player.getDirZ();
	m_is_running = player.getIsRunning();
	m_is_flying = player.getIsFlying();
	m_name = player.getName();
	m_body = player.getBody();

}

Player::Player(int name){
	m_dir_x = 0;
	m_dir_z = 0;
	m_is_running = false;
	m_is_flying = false;
	m_name = name;
}

Player::~Player(){
	
}

//  
// Methods
//  

	

Body& Player::getBody(){
	return m_body;
}
void Player::setBody(Body body){
	m_body = body;
}

int Player::getName() const{
	return m_name;
}
void Player::setName(int name){
	m_name = name;
}

int Player::getDirZ() const{
	return m_dir_z;
}
void Player::setDirZ(int z){
	m_dir_z = z;
}

int Player::getDirX() const{
	return m_dir_x;
}
void Player::setDirX(int x){
	m_dir_x = x;
}

bool Player::getIsRunning() const{
	return m_is_running;
}

bool Player::getIsFlying() const{
	return m_is_flying;
}



void Player::updatePlayer(){
	
	float coeffRunning=0;
	if(m_is_running) coeffRunning = 2; 
	else coeffRunning = 1;

    float coeffJetpacking=0;
	if(m_is_flying) coeffJetpacking = 2;
	else coeffJetpacking = 0;

	m_body.updateBody(m_dir_x, m_dir_z, coeffRunning, coeffJetpacking);

}


void Player::jetpack(bool is_flying){
	this->m_is_flying = is_flying;
}

void Player::run(bool is_running){
	this->m_is_running = is_running;
}

void Player::moveFront(int t){
	setDirZ(t);
}

void Player::moveLeft(int t){
	setDirX(t);
}


bool Player::catchCube(int cube){
	return this->m_inventory.addCube(cube);
}

bool Player::dropCube(){
	return this->m_inventory.removeCurrentCube();
}

bool Player::deleteCube(int cube){
	return this->m_inventory.removeCube(cube);
}


// Accessor methods
//  



// Other methods
//  
