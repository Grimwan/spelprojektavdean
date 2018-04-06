#include "Heightmap.h"



	

Heightmap::Heightmap()
{
}

Heightmap::~Heightmap()
{
	for (int j = 0; j < _heightLength; j++)
	{
		delete[] _twodArray[j];
	}
	delete[] _twodArray;
}

void Heightmap::loadingBmpPicture(const char * filename)
{
	FILE* f = fopen(filename, "rb");
	if (f == NULL)
	{
		throw "Argument Exception";
	}

	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f);

	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	_heightLength = height;
	_widthLength = width;


	buildgridarray();

	int row_padded = (width * 3 + 3) & (~3);
	unsigned char* data = new unsigned char[row_padded];
	unsigned char tmp;
	int realj = 0;
	for (int i = 0; i < height; i++)
	{
		realj = 0;
		fread(data, sizeof(unsigned char), row_padded, f);
		for (int j = 0; j < width * 3; j += 3)
		{
			// Convert (B, G, R) to (R, G, B)
			tmp = data[j];
			data[j] = data[j + 2];
			data[j + 2] = tmp;



			_twodArray[i][realj].height = data[j];
			_twodArray[i][realj].x = i;
			_twodArray[i][realj].y = realj;
			realj++;
		}
	
	}
		delete[] data;
		fclose(f);
	
}

void Heightmap::buildgridarray()
{
	//building the 2D array
	_twodArray = new Grid*[_heightLength];
	for (int j = 0; j < _heightLength; j++)
	{
		_twodArray[j] = new Grid[_widthLength];
	}
}

int Heightmap::getheightLength()
{
	return _heightLength;
}

int Heightmap::getwidhtLength()
{
	return _widthLength;
}

void Heightmap::buildscene()
{
	PositonColorVertex pushback;
	
	for (int i = 0; i < _heightLength; i++)
	{
		for (int j = 0; j < _widthLength; j++) //bygger inga trianglar med det borde använda indexbuffer T_T
		{
			pushback = { _twodArray[i][j].x,_twodArray[i][j].y,0,
				1,0,0,
			};
			Vertex.push_back(pushback);
		}
	}
	int test;
	
}

void Heightmap::test()
{
	_twodArray;
	_twodArray[5][2];
}
