#include "include/Player.hpp"
#include "include/Body.hpp"
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

Body Player::getBody() const{
	return this->m_body;
}
void Player::setBody(Body body){
	this->m_body = body;
}


void Player::updatePlayer(){

}

void Player::idle(){
	this->setState(State::idle);
}
void Player::move(){
	this->setState(State::walk);
}
void Player::jump(){
	this->setState(State::jump);
}
void Player::run(){
	this->setState(State::run);
}
void Player::jetpack(){
	this->setState(State::jetpack);
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
