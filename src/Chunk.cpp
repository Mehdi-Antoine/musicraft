#include "include/Chunk.hpp"
#include <iostream>


const int Chunk::m_size = SIZE;

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

Chunk::Chunk(char cube_type){

	for (int x = 0; x < Chunk::m_size; ++x)
	{
		for (int y = 0; y < Chunk::m_size; ++y)
		{
			for (int z = 0; z < Chunk::m_size; ++z)
			{		
				m_chunk[x][y][z] = cube_type;				
			}
		}
	}

}

Chunk::~Chunk(){

}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------GETTERS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

char Chunk::getCubeType(float x, float y, float z) const{

	return m_chunk[getIndex(x)][getIndex(y)][getIndex(z)];
}

char Chunk::getCubeType(const glm::vec3 &position) const{
	//std::cout << getIndex(position.x) << " " << getIndex(position.y) << " " << getIndex(position.z) << std::endl;
	return m_chunk[getIndex(position.x)]
				  [getIndex(position.y)]
				  [getIndex(position.z)];

}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------SETTERS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------	

void Chunk::setCubeType(int x, int y, int z, char cube_type){

	m_chunk[getIndex(x)][getIndex(y)][getIndex(z)] = cube_type;

}

void Chunk::setCubeType(const glm::vec3 &position, char cube_type){

	m_chunk[getIndex(position.x)]
		   [getIndex(position.y)]
		   [getIndex(position.z)] = cube_type;

}

//-------------------------------------------------FUNCTIONS----------------------------------------------------

int Chunk::getIndex(float value) const{


	float decimal = value - int(value);
	return round(value);
}

glm::vec3 Chunk::getColorFromType(char cube_type){
	switch (cube_type) {

		case EMPTY:
		  return glm::vec3(0,0,0);
		  break;

		case BASIC1:
		  return glm::vec3(0.75,
						   0.17,
						   0.62);
		  break;

		case BASIC2:
		  return glm::vec3(0.17,
						   0.75,
						   0.47);
		  break;

		case BASIC3:
		  return glm::vec3(0.22,
						   0.4,
						   0.75);
		  break;

		default:
		  return glm::vec3(1,1,1);
		  break;
	}
}