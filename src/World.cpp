#include <vector>

#include <iostream>

#include "include/Window.hpp"

#include "include/World.hpp"

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

World::World(){

}

World::World(Window window)
: m_window(window){

	double persistence = 0.9;
	double frequency = .2;
	double amplitude = 60;
	int octaves = 1;
	int randomseed = 1245;

	m_noise = PerlinNoise(persistence, frequency, amplitude, octaves, randomseed);
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

/*
char World::getCubeType(const glm::vec3 &position) const{
	return m_chunks[0].getCubeType(position);
}

char World::getCubeType(float x, float y, float z) const{
	const glm::vec3 position(x,y,z);
	return m_chunks[0].getCubeType(position);
}*/


int World::getChunkVectorSize(){
	return m_chunks.size();
}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------SETTERS------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void World::setCubeType(const glm::vec3 &position, char cube_type){
	glm::vec3 pos = position*glm::vec3(.5,.5,.5);
	m_chunks[0].setCubeType(position, cube_type);
}
/*
void World::setCubeType(float x, float y, float z, char cube_type){
	m_chunks[0].setCubeType(x, y, z, cube_type);
}*/

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------FUNCTIONS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void World::addChunk(Chunk &chunk){
	m_chunks.push_back(chunk);
}

void World::addChunk(glm::vec3 pos){
	Chunk c = Chunk(m_noise, pos);
	std::cout << pos << std::endl;
	c.lighten();
	m_chunks.push_back(c);
}

void World::createMap(glm::vec3 &player){
	glm::vec3 pos = getChunkCoord(player);
	//std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
	addChunk(glm::vec3(pos.x, pos.y, pos.z + SIZE));
	addChunk(glm::vec3(pos.x, pos.y, pos.z - SIZE));
	addChunk(pos);
	addChunk(glm::vec3(pos.x + SIZE, pos.y, pos.z));
	addChunk(glm::vec3(pos.x + SIZE, pos.y, pos.z + SIZE));
	addChunk(glm::vec3(pos.x + SIZE, pos.y, pos.z - SIZE));
	addChunk(glm::vec3(pos.x - SIZE, pos.y, pos.z));
	addChunk(glm::vec3(pos.x - SIZE, pos.y, pos.z + SIZE));
	addChunk(glm::vec3(pos.x - SIZE, pos.y, pos.z - SIZE));

	addChunk(glm::vec3(pos.x, pos.y - SIZE, pos.z + SIZE));
	addChunk(glm::vec3(pos.x, pos.y - SIZE, pos.z - SIZE));
	addChunk(glm::vec3(pos.x, pos.y - SIZE, pos.z));
	addChunk(glm::vec3(pos.x + SIZE, pos.y - SIZE, pos.z));
	addChunk(glm::vec3(pos.x + SIZE, pos.y - SIZE, pos.z + SIZE));
	addChunk(glm::vec3(pos.x + SIZE, pos.y - SIZE, pos.z - SIZE));
	addChunk(glm::vec3(pos.x - SIZE, pos.y - SIZE, pos.z));
	addChunk(glm::vec3(pos.x - SIZE, pos.y - SIZE, pos.z + SIZE));
	addChunk(glm::vec3(pos.x - SIZE, pos.y - SIZE, pos.z - SIZE));

	addChunk(glm::vec3(pos.x, pos.y + SIZE, pos.z + SIZE));
	addChunk(glm::vec3(pos.x, pos.y + SIZE, pos.z - SIZE));
	addChunk(glm::vec3(pos.x, pos.y + SIZE, pos.z));
	addChunk(glm::vec3(pos.x + SIZE, pos.y + SIZE, pos.z));
	addChunk(glm::vec3(pos.x + SIZE, pos.y + SIZE, pos.z + SIZE));
	addChunk(glm::vec3(pos.x + SIZE, pos.y + SIZE, pos.z - SIZE));
	addChunk(glm::vec3(pos.x - SIZE, pos.y + SIZE, pos.z));
	addChunk(glm::vec3(pos.x - SIZE, pos.y + SIZE, pos.z + SIZE));
	addChunk(glm::vec3(pos.x - SIZE, pos.y + SIZE, pos.z - SIZE));
}

void World::createCoordinates(std::vector<glm::vec3> &cubePosition, std::vector<glm::vec3> &cubeColor){
	for(int i = 0; i < m_chunks.size(); ++i){
		m_chunks[i].getAllCoordinates(cubePosition, cubeColor);
	}
}

void World::updateMap(glm::vec3 &player){
	glm::vec3 pos = getChunkCoord(player);
	int newIndex = findChunkIndex(pos);
	if(newIndex != m_current_index){
		m_current_index = newIndex;
		m_chunks.clear();
		createMap(pos);
	}
}


char World::getCubeType(const glm::vec3 &position) const{

	//glm::vec3 chunk_position = World::getChunkCoord(position);

	//std::cout << "chunk_position = " << chunk_position << std::endl;

	//int index = findChunkIndex(chunk_position);

	//if(index >= 0){
		//std::cout << "in chunk : " << index << std::endl;
		glm::vec3 pos = position;
		return m_chunks[m_current_index].getCubeType(position);
	/*}
	else{
		return -1;
	}*/
	
}

char World::getCubeType(float x, float y, float z) const{
	char type = getCubeType(glm::vec3(x,y,z));
	return type;
}

int World::findChunkIndex(const glm::vec3 &position) const{

	glm::vec3 chunk_position;

	for(int i = 0; i<m_chunks.size(); ++i){

		chunk_position = m_chunks[i].root.coo;
		//std::cout << "chunk pos " << chunk_position << " pos " << position << std::endl;
		if(position == chunk_position){
			return i;
		}
	}

	//std::cout << "CHUNK NOT FOUND : " << position << std::endl;

	return -1;

}

glm::vec3 World::getChunkCoord(const glm::vec3 &position){

	//trouve les coordonnées du chunk correspondant 
	float x = int((position.x/2) / SIZE*2)*SIZE;
	float y = int((position.y/2) / SIZE*2)*SIZE;
	float z = int((position.z/2) / SIZE*2)*SIZE;
	//std::cout << x << " " << y << " " << z << std::endl;
	return glm::vec3(x, y ,z);

}

glm::vec3 World::getLocalPosition(const glm::vec3 &position){

	glm::vec3 chunk_position = getChunkCoord(position);

	float x = position.x - chunk_position.x * SIZE;
	float y = position.y - chunk_position.y * SIZE;
	float z = position.z - chunk_position.z * SIZE;

	return glm::vec3(x, y ,z);

}

void World::updateGlElement(GlElement &gl_element, int chunk_index){

	std::vector<glm::vec3> cube_position;
	std::vector<glm::vec3> cube_color;

	glm::vec3 world_position;// = m_chunks[chunk_index].getWorldPosition();

	glm::vec3 gl_cube_position;

	glm::vec3 current_cube_color;


	char cube_type;
/*
	for (int x = 0; x < SIZE; ++x)
    {
        for (int y = 0; y < SIZE; ++y)
        {
            for (int z = 0; z < SIZE; ++z)
            {   
                cube_type = m_chunks[chunk_index].getCubeType(x,y,z);

                if(cube_type != EMPTY){

                	gl_cube_position = float(2) * (world_position + glm::vec3(x, y ,z));

                    cube_position.push_back(gl_cube_position);

                    current_cube_color = Chunk::getColorFromType(cube_type);

                    cube_color.push_back(current_cube_color); 
                }
            }
        }
    }*/

    gl_element.data(cube_position, cube_color);

}

void World::drawWorld(const std::vector<GlElement*> &gl_chunks) const{

	for(int i = 0; i < gl_chunks.size(); ++i){
		gl_chunks[i]->draw();
	}

}

