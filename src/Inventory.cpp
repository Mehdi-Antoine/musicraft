#include "include/Inventory.hpp"
#include <iostream>


// Constructors/Destructors
//  

Inventory::Inventory()
	: m_max_size(50), m_current_cube(-1)
{
	for(int i=0; i < m_max_size/2;i++){
		this->addCube(1);
		this->addCube(2);
	}
	this->addCube(3);

}

Inventory::~Inventory(){
	
}

// 
// Methods
//

bool Inventory::isEmpty() const{
	return m_list.empty();
}

int Inventory::getNumberCubes() const{
	int result = 0;
	for (std::map<int,int>::const_iterator it=m_list.begin(); it!=m_list.end(); ++it){
    	result += it->second;
	}
	return result;
}

int Inventory::getCurrentCube(){
	return m_current_cube;
}

void Inventory::setCurrentCube(int cube){
	m_current_cube = cube;
}

bool Inventory::addCube(int cube){
	if (this->getNumberCubes() < m_max_size){
		if(m_list.find(cube) == m_list.end()){
			if(m_list.size() >= m_max_size){
				std::cout << "Plus de place pour un nouveau cube!"<< std::endl;
				return false;
			}
			m_list[cube] = 0; 
		}
		
		m_list[cube]++;
		std::cout << "Cube ajouté!" << std::endl;
		return true;
	}
	std::cout << "Ineventaire plein!" << std::endl;
	return false;
}

bool Inventory::removeCube(int cube){
	if(m_list.find(cube) == m_list.end()){
		if(m_list[cube] > 0){
			m_list[cube]--;
			std::cout << "Cube supprimé!" << std::endl;
			return true;
		}
	}
	std::cout << "Pas de cube!" << std::endl;
	return false;
}

bool Inventory::removeCurrentCube(){
	if(m_current_cube > -1){
		return this->removeCube(this->getCurrentCube());
	}
	return false;
}

void Inventory::show() const{
	std::cout << "*****************INVENTAIRE :*****************" << std::endl;
	for (std::map<int,int>::const_iterator it=m_list.begin(); it!=m_list.end(); ++it){
    	std::cout << "Cube " << it->first << " : " << it->second << std::endl;
	}
	std::cout << "**********************************************" << std::endl;
}

// Accessor methods
//  


// Other methods
//  
