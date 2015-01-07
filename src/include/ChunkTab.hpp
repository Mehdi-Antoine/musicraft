#pragma once
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <iostream>
#include <vector>
#include "Octree.hpp"
#include "PerlinNoise.hpp"

<<<<<<< HEAD:src/include/Chunk.hpp
#define SIZE 32
=======
#define SIZE 8 
>>>>>>> origin/multi_chunk:src/include/ChunkTab.hpp

enum CubeType{ 
  EMPTY = 0,
  BASIC1 = 1,
  BASIC2 = 2,
  BASIC3 = 3
};

<<<<<<< HEAD:src/include/Chunk.hpp
=======
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
>>>>>>> origin/multi_chunk:src/include/ChunkTab.hpp

class Chunk{
	public:
		Octree root;
		int profondeur = 4;
		float taille = pow(2, profondeur-1);

		Chunk();
		Chunk(int seed, glm::vec3 racine);

		char getCubeType(const glm::vec3 &pos) const;
		void setCubeType(const glm::vec3 &pos, char type);
		void genFlatFloor(Octree &subTree, int etage);
		void genFullCube(Octree &subTree, int etage);
		void genTerrain(Octree &subTree, int etage, float taille, int seed);
		void fillTerrain(Octree &subTree, int etage, float taille, int x, int z, int y);
		void culling(std::vector<float> centres, Octree &subTree, int etage, float taille);
		std::vector<glm::vec3> getAllCoordinates();
		void lighten();
};