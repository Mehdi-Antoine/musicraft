#pragma once

#include <GL/glew.h>

#include <glimac/glm.hpp>

#define SIZE 128 

enum CubeType{ 
  EMPTY = 0,
  BASIC = 1,
  STING = 2
};

struct ChunkElement{

	char type;
	int  vector_position;

};

class Chunk{
private:

	ChunkElement m_chunk[SIZE][SIZE/4][SIZE];
	
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
	void setCubeType(const glm::vec3 &position, char cube_type);

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	int getIndex(float value) const;

};