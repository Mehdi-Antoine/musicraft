#include <vector>

#include "include/World.hpp"

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

World::World(){
	
}

World::World(Window window)
: m_window(window){
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

Window World::getWindow() const{
	return m_window;
}

int World::getWindowWidth() const{
	return m_window.getWindowWidth();
}

int World::getWindowHeight() const{
	return m_window.getWindowHeight();
}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------SETTERS------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void World::setCubeType(const glm::vec3 &position, char cube_type){
	glm::vec3 pos = position*glm::vec3(.5,.5,.5);
	m_chunks[0].setCubeType(position, cube_type);
}

void World::setCubeType(float x, float y, float z, char cube_type){
	glm::vec3 position(x,y,z);
	m_chunks[0].setCubeType(position, cube_type);
}

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------FUNCTIONS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void World::addChunk(Chunk &chunk){
	m_chunks.push_back(chunk);
}

char World::getCubeType(glm::vec3 &position) const{
	return m_chunks[0].getCubeType(position);
}

char World::getCubeType(float x, float y, float z) const{
	glm::vec3 position(x,y,z);
	return m_chunks[0].getCubeType(position);
}
