#include "include/Inventory.hpp"
#include <iostream>
#include <algorithm>


// Constructors/Destructors
//  

Inventory::Inventory()
	: m_max_size(100),m_current_index(-1)
{
	for(int i=0; i < 5;i++){
		this->addCube(1);
		this->addCube(2);
	}

}

Inventory::~Inventory(){
	
}

// 
// Methods
//

bool Inventory::isEmpty() const{
	return m_type_list.empty();
}

int Inventory::getNumberCubes() const{
	int result = 0;
	for(int i = 0; i < m_nb_list.size(); ++i)
		result += m_nb_list[i];
	return result;
}

int Inventory::getCurrentIndex() const{
	return m_current_index;
}

void Inventory::nextIndex(){
	if(m_current_index == -1 || m_current_index < m_nb_list.size()-1){
		m_current_index++;
	}
	else{
		m_current_index = -1;
	}
}
void Inventory::prevIndex(){
	if(m_current_index >= 0){
		m_current_index--;
	}
	else{
		m_current_index = m_nb_list.size()-1;
	}
}

void Inventory::addCube(char cube){
	if((int) cube > 0 && (int) cube < 4){
		if (this->getNumberCubes() < m_max_size){
			int pos = std::find(m_type_list.begin(), m_type_list.end(), cube) - m_type_list.begin();
			if(pos < m_type_list.size()){
				m_nb_list[pos]++;			}
			else{
				if(m_type_list.size() >= m_max_size){
					std::cout << "Plus de place pour un nouveau cube!"<< std::endl;
				}
				m_type_list.push_back(cube);
				m_nb_list.push_back(1);
			}
		}
		else{
			std::cout << "Ineventaire plein!" << std::endl;	
		}
	}
	else{
		std::cout << "Type de cube inconnu (pas d'ajout)" << std::endl;
	}

}

bool Inventory::removeCube(char &result, int index){
	if(index > -1 && index < m_type_list.size()){
		m_nb_list[index]--;
		result = m_type_list[index];
		if(m_nb_list[index] == 0){
			m_nb_list.erase(m_nb_list.begin()+index);
			m_type_list.erase(m_type_list.begin()+index);
		}
		return true;
	}
	std::cout << "Pas de cube!" << std::endl;
	return false;
}

bool Inventory::removeCurrentCube(char &result){
	if(m_current_index >=0){
		return this->removeCube(result,	getCurrentIndex());
	}
	return false;
}

void Inventory::show() const{
	std::cout << "*****************INVENTAIRE :*****************" << std::endl;
	std::cout << "Current cube : " << getCurrentIndex()<< std::endl;
	for (int i=0; i< m_type_list.size(); ++i){
    	std::cout << "Emplacement " << i <<" : Cube " << (int)m_type_list[i] << " : " << m_nb_list[i] << std::endl;
	}
	std::cout << "**********************************************" << std::endl;
}

// Accessor methods
//  


// Other methods
//  
