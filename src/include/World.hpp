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

public:

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
	void addChunk(glm::vec3 &pos);

	static glm::vec3 getChunkCoord(const glm::vec3 &position);

	static glm::vec3 getLocalPosition(const glm::vec3 &position);

	int findChunkIndex(const glm::vec3 &position) const;


	//char getCubeType(const glm::vec3 &position) const;
	//char getCubeType(float x, float y, float z) const;



	void updateGlElement(GlElement &gl_element, int chunk_index);

	void drawWorld(const std::vector<GlElement*> &gl_chunks) const;

};
