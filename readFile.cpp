#include "readFile.h"

using namespace std;

void ReadFile::read(const string path)
{
	//TODO: lire le fichier et remplir la matrice

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