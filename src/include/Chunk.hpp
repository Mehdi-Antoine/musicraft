#pragma once

#include "GlElement.hpp"

#include <GL/glew.h>

#include <glimac/glm.hpp>

#define CHUNK_SIZE 32 

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

	ChunkElement m_chunk[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

	
	
public:

	GlElement m_gl_chunk;

	static const int m_size;

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

	Chunk(char cube_type = 0);
	~Chunk();

//--------------------------------------------------GETTERS-----------------------------------------------------

	char getCubeType(float x, float y, float z) const;
	char getCubeType(const glm::vec3 &position) const;

	int getCubeVectorPosition(float x, float y, float z) const;
	int getCubeVectorPosition(const glm::vec3 &position) const;

//--------------------------------------------------SETTERS-----------------------------------------------------

	void setCubeType(int x, int y, int z, char cube_type);
	void setCubeType(const glm::vec3 &position, char cube_type);

	void setCubeVectorPosition(float x, float y, float z, int vector_index);
	void setCubeVectorPosition(const glm::vec3 &position, int vector_index);

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	int getIndex(float value) const;

	void draw();

	void addCube(char type, const glm::vec3 &position, const glm::vec3 &color);
	void addCube(char type, float x, float y, float z, const glm::vec3 &color);

	void setCube(char type, const glm::vec3 &position, const glm::vec3 &color);
	void setCube(char type, float x, float y, float z, const glm::vec3 &color);

};