#include "include/Player.hpp"
#include "include/State.hpp"

// Constructors/Destructors
//  

Player::Player(){
	this->idle();
}

Player::~Player(){
	
}

//  
// Methods
//  

State Player::getState() const{
	return this->m_state;
}
void Player::setState(State state){
	m_state = state;
}

void Player::updatePlayer(){

}

void Player::idle(){
	this->m_state = State::idle;
}
void Player::move(){
	this->m_state = State::walk;
}
void Player::jump(){
	this->m_state = State::jump;
}
void Player::run(){
	this->m_state = State::run;
}
void Player::jetpack(){
	this->m_state = State::jetpack;
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
