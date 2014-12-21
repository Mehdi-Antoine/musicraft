#pragma once
#include <vector>

class Inventory {
private:
	std::vector<int> m_list;
	int m_current_cube;
	int m_max_size;
public:
	Inventory();
	~Inventory();

	bool isEmpty() const;
	int size() const;
	int getCurrentCube();
	void setCurrentCube(int cube);

	bool addCube(int cube);

	bool removeCube(int cube);
	bool removeCurrentCube();




	/* data */
};