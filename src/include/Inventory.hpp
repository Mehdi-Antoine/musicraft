#pragma once
#include <map>

class Inventory {
private:
	std::map<int, int> m_list;
	int m_current_cube;
	int m_max_size;
public:
	Inventory();
	~Inventory();

	bool isEmpty() const;
	int getNumberCubes() const;
	int getCurrentCube();
	void setCurrentCube(int cube);

	bool addCube(int cube);

	bool removeCube(int cube);
	bool removeCurrentCube();

	void show() const;


	/* data */
};