#pragma once

#include <vector>

#include "Chunk.hpp"
#include "Window.hpp"
#include "GlElement.hpp"
#include "PerlinNoise.hpp"



class World{
private:

	std::vector<Chunk> m_chunks;
	Window m_window;
	PerlinNoise m_noise;
	int m_current_index = 0;

public:

	static const int tab_size = 729;
	std::vector<glm::vec3> m_cubes_color[tab_size];
    std::vector<glm::vec3> m_cubes_position[tab_size];

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

	World();
	World(Window window);
	~World();

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------GETTERS------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

	Chunk& getChunk(int index);
	std::vector<Chunk>& getChunkVector();
	Window getWindow() const;
	int getWindowWidth() const;
	int getWindowHeight() const;

	char getCubeType(const glm::vec3 &position) const;
	char getCubeType(float x, float y, float z) const;

	int getChunkVectorSize();


//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------SETTERS------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

	void setCubeType(const glm::vec3 &position, char cube_type);

	//void setCubeType(float x, float y, float z, char cube_type);

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------FUNCTIONS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

	void addChunk(Chunk &chunk);
	void addChunk(glm::vec3 pos);
	void createMap(glm::vec3 &player);
	//void createCoordinates(std::vector<glm::vec3> &cubePosition, std::vector<glm::vec3> &cubeColor);
	int updateMap(glm::vec3 &player);

	static glm::vec3 getChunkCoord(const glm::vec3 &position);

	static glm::vec3 getLocalPosition(const glm::vec3 &position);

	int findChunkIndex(const glm::vec3 &position) const;


	//char getCubeType(const glm::vec3 &position) const;
	//char getCubeType(float x, float y, float z) const;



	void updateGlElement(GlElement &gl_element, int chunk_index);

	void drawWorld(const std::vector<GlElement*> &gl_chunks) const;

};
