#include "Heightmap.h"
#define roundDownTheHeight 10


	

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
	int m = 0;

	for (int i = 0; i < _heightLength; i++)
	{
		for (int j = 0; j < _widthLength; j++) //bygger inga trianglar med det borde använda indexbuffer T_T
		{
			pushback = { _twodArray[i][j].x, _twodArray[i][j].height/ roundDownTheHeight ,_twodArray[i][j].y,
				1.0f,1.0f,0.0f,
			};
			_twodArray[i][j].indexValue = m;
			m++;
			Vertex.push_back(pushback);
		}
	}

	for (int i = 0; i < _heightLength - 1; i++)
	{
		for (int j = 0; j < _widthLength - 1; j++)
		{
			Index.push_back(_twodArray[i][j].indexValue);
			Index.push_back(_twodArray[i][j + 1].indexValue);
			Index.push_back(_twodArray[i + 1][j].indexValue);
			
			Index.push_back(_twodArray[i][j + 1].indexValue);
			Index.push_back(_twodArray[i + 1][j + 1].indexValue);
			Index.push_back(_twodArray[i + 1][j].indexValue);



		}
	}
	
	/*
	PositonColorVertex test = {
		0.0f, 0.0f, 0.0f,	//v0 pos
		1.0f, 0.0f, 0.0f,	//v0 color 
	};
	Vertex.push_back(test);

	test = {
		1.0f, 0.0f, 0.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color
	};
	Vertex.push_back(test);

	test = {
		0.0f, 0.0f, 1.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	Vertex.push_back(test);

	test = {
		1.0f, 0.0f, 1.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	Vertex.push_back(test);
	
	
	Index.push_back(0);
	Index.push_back(1);
	Index.push_back(2);

	Index.push_back(1);
	Index.push_back(2);
	Index.push_back(3);
	*/
/*
	for (int i = 0; i < Vertex.size(); i++)
		std::cout << Vertex[i].x << " " << Vertex[i].y << " " << Vertex[i].z << std::endl;

	for (int i = 0; i < Index.size(); i++)
	{
		std::cout << Index[i] << std::endl;
	}
	*/
}

void Heightmap::test()
{
	_twodArray;
	_twodArray[5][2];
}
