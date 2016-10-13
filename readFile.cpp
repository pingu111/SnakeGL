#include "readFile.h"
#include <fstream>
#include <sstream>
#include <assert.h>

using namespace std;

void ReadFile::read(const string path)
{
	ifstream infile(path);
	int i = 0;
	string line;
	while (getline(infile, line))
	{
		++i;
		matrixPosition.push_back(vector<int>());
		for (auto iter = line.begin();iter < line.end();iter++)
		{
			assert(*iter == '0' || *iter == '1');
			int value = *iter - '0';
			assert(value == 0 || value == 1);
			matrixPosition[i].push_back(*iter);
		}
	}

	fillVectorFromMatrix();
}

void ReadFile::fillVectorFromMatrix()
{
	positions = vector<pair<int, int>>();

	for (auto i = matrixPosition.begin();i < matrixPosition.end;i++)
	{
		for (auto j = i->begin();j < i->end();j++)
		{
			if (*j == 1)
			{
				positions.push_back(pair<int,int>(
													i-matrixPosition.begin(),
													j-i->begin()
												 ));
			}
		}
	}
}