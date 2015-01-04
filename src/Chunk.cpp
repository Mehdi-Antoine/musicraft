#include "include/Chunk.hpp"
#include "include/GlElement.hpp"

#include <iostream>


const int Chunk::m_size = CHUNK_SIZE;

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

	return m_chunk[getIndex(position.x)]
				  [getIndex(position.y)]
				  [getIndex(position.z)].type;
}

int Chunk::getCubeVectorPosition(float x, float y, float z) const{

	return m_chunk[getIndex(x)]
				  [getIndex(y)]
				  [getIndex(z)].vector_position;

}

int Chunk::getCubeVectorPosition(const glm::vec3 &position) const{

	return m_chunk[getIndex(position.x)]
				  [getIndex(position.y)]
				  [getIndex(position.z)].vector_position;

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

void Chunk::setCubeVectorPosition(float x, float y, float z, int vector_index){

	m_chunk[getIndex(x)]
		   [getIndex(y)]
		   [getIndex(z)].vector_position = vector_index;

}

void Chunk::setCubeVectorPosition(const glm::vec3 &position, int vector_index){

	m_chunk[getIndex(position.x)]
		   [getIndex(position.y)]
		   [getIndex(position.z)].vector_position = vector_index;

}

//-------------------------------------------------FUNCTIONS----------------------------------------------------

int Chunk::getIndex(float value) const{


	float decimal = value - int(value);
	return round(value);
}

void Chunk::addCube(char type, float x, float y, float z, const glm::vec3 &color){

	glm::vec3 position(x, y, z);

	setCubeType(position, type);

	glm::vec3 gl_position = float(2) * position;

	int vector_index = m_gl_chunk.addEntry(gl_position, color);

	setCubeVectorPosition(position, vector_index);

}

void Chunk::addCube(char type, const glm::vec3 &position, const glm::vec3 &color){

	setCubeType(position, type);

	glm::vec3 gl_position = float(2) * position;

	int vector_index = m_gl_chunk.addEntry(gl_position, color);

	setCubeVectorPosition(position, vector_index);
}

void Chunk::setCube(char type, const glm::vec3 &position, const glm::vec3 &color){

	setCubeType(position, type);

	int vector_index = getCubeVectorPosition(position);

	if(type == EMPTY){
		m_gl_chunk.removeEntry(vector_index);
	}
	else{
		glm::vec3 gl_position = float(2) * position;
		m_gl_chunk.subData(gl_position, color, vector_index);
	}

}

void Chunk::setCube(char type, float x, float y, float z, const glm::vec3 &color){

	glm::vec3 position(x, y, z);

	setCubeType(position, type);

	int vector_index = getCubeVectorPosition(position);

	if(type == EMPTY){
		m_gl_chunk.removeEntry(vector_index);
	}
	else{
		glm::vec3 gl_position = float(2) * position;
		m_gl_chunk.subData(gl_position, color, vector_index);
	}

}

void Chunk::draw(){

	m_gl_chunk.draw();

}