#pragma once

#include <GL/glew.h>

#include <glimac/glm.hpp>

#define SIZE 128 

enum CubeType{ 
  EMPTY = 0,
  SOLID = 1
};

class Chunk{
private:

	char m_chunk[SIZE][SIZE][SIZE];
	
public:

	static const int m_size;

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

	Chunk(char cube_type = 0);
	~Chunk();

//--------------------------------------------------GETTERS-----------------------------------------------------

	char getCubeType(float x, float y, float z) const;
	char getCubeType(const glm::vec3 &position) const;

//--------------------------------------------------SETTERS-----------------------------------------------------

	void setCubeType(int x, int y, int z, char cube_type);

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	int getIndex(float value) const;

};