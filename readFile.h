#pragma once
#include <vector>

class ReadFile
{
public :
	std::vector<std::pair<int, int>> positions;
	void read(const std::string path);
private:
	std::vector<std::vector<int>> matrixPosition;
	void fillVectorFromMatrix();
};