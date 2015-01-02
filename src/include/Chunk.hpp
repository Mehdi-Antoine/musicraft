#pragma once

#include <GL/glew.h>

#include <glimac/glm.hpp>

#define SIZE 10 

enum CubeType{ 
  EMPTY,
  SOLID
};

class Chunk{
private:

	CubeType m_chunk[SIZE][SIZE][SIZE];
	
public:

	static const int m_size;

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

	Chunk(CubeType cube_type = EMPTY);
	~Chunk();

//--------------------------------------------------GETTERS-----------------------------------------------------

	CubeType getCubeType(float x, float y, float z) const;
	//CubeType getCubeType(const glm::vec3 &position) const;

//--------------------------------------------------SETTERS-----------------------------------------------------

	void setCubeType(int x, int y, int z, CubeType cube_type);

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	int getIndex(float value) const;

};