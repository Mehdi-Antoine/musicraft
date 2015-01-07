#pragma once

#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <iostream>
#include <vector>
#include "Octree.hpp"
#include "PerlinNoise.hpp"

#define SIZE 16 


enum CubeType{ 
  EMPTY = 0,
  BASIC1 = 1,
  BASIC2 = 2,
  BASIC3 = 3
};

class Chunk{
private:

public:
	Octree root;
	int profondeur = 4;
	float taille = pow(2, profondeur-1);
	
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

	static glm::vec3 getColorFromType(char type);

};
