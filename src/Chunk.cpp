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
				m_chunk[x][y][z].type            = cube_type;
				m_chunk[x][y][z].vector_position = -1;				
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

	return m_chunk[getIndex(x)]
				  [getIndex(y)]
				  [getIndex(z)].type;
}

char Chunk::getCubeType(const glm::vec3 &position) const{
	//std::cout << getIndex(position.x) << " " << getIndex(position.y) << " " << getIndex(position.z) << std::endl;
	return m_chunk[getIndex(position.x)]
				  [getIndex(position.y)]
				  [getIndex(position.z)].type;
}


//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------SETTERS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------	

void Chunk::setCubeType(int x, int y, int z, char cube_type){

	m_chunk[getIndex(x)]
		   [getIndex(y)]
		   [getIndex(z)].type = cube_type;

}

void Chunk::setCubeType(const glm::vec3 &position, char cube_type){

	m_chunk[getIndex(position.x)]
		   [getIndex(position.y)]
		   [getIndex(position.z)].type = cube_type;

}

//-------------------------------------------------FUNCTIONS----------------------------------------------------

int Chunk::getIndex(float value) const{


	float decimal = value - int(value);
	return round(value);
}