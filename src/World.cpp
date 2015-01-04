#include <vector>

#include "include/World.hpp"

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

World::World(){

}

World::~World(){
	
}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------GETTERS------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

Chunk& World::getChunk(int index){
	if(index >= 0 && index < m_chunks.size()){
		return m_chunks[index];
	}
}

std::vector<Chunk>& World::getChunkVector(){

}

char World::getCubeType(const glm::vec3 &position){
	return m_chunks[0].getCubeType(position);
}

char World::getCubeType(float x, float y, float z){
	return m_chunks[0].getCubeType(x, y, z);
}

int World::getCubeVectorPosition(const glm::vec3 &position){
	return m_chunks[0].getCubeVectorPosition(position);
}

int World::getCubeVectorPosition(float x, float y, float z){
	return m_chunks[0].getCubeVectorPosition(x, y, z);
}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------SETTERS------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void World::setCubeType(const glm::vec3 &position, char cube_type){
	m_chunks[0].setCubeType(position, cube_type);
}

void World::setCubeVectorPosition(const glm::vec3 &position){
	
}

void World::setCube(const glm::vec3 &position, const glm::vec3 &color, char cube_type){
	m_chunks[0].setCube(cube_type, position, color);
}

void World::removeCube(const glm::vec3 &position){
	m_chunks[0].setCube(EMPTY, position, glm::vec3(0,0,0));
}

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------FUNCTIONS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void World::addChunk(Chunk &chunk){
	m_chunks.push_back(chunk);
}

void World::drawChunk(int indice){
	m_chunks[indice].draw();
}

