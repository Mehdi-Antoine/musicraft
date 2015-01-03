#pragma once

#include <GL/glew.h>

#include <glimac/glm.hpp>

<<<<<<< HEAD
#define SIZE 50 
=======
#define SIZE 128 
>>>>>>> 0f0ecb9996dfeefd896c0db42178a89a5b999eb9

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