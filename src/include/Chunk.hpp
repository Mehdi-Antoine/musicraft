#pragma once

#include <GL/glew.h>

#include <glimac/glm.hpp>

#define SIZE 8 

enum CubeType{ 
  EMPTY = 0,
  BASIC1 = 1,
  BASIC2 = 2,
  BASIC3 = 3
};

class Chunk{
private:

	char m_chunk[SIZE][SIZE][SIZE];

	glm::vec3 m_world_position;
	
public:

	static const int m_size;

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

	Chunk(char cube_type = 0);
	Chunk(const Chunk &chunk);
	~Chunk();

//--------------------------------------------------GETTERS-----------------------------------------------------

	char getCubeType(float x, float y, float z) const;
	char getCubeType(const glm::vec3 &position) const;

	glm::vec3 getWorldPosition() const;

//--------------------------------------------------SETTERS-----------------------------------------------------

	void setCubeType(int x, int y, int z, char cube_type);
	void setCubeType(const glm::vec3 &position, char cube_type);

	void setWorldPosition(glm::vec3 world_position);

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	int getIndex(float value) const;

	static glm::vec3 getColorFromType(char type);

};