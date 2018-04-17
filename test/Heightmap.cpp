#include "Heightmap.h"
#define roundDownTheHeight 10
using namespace DirectX;

float3 CrossProductt(float3 First, float3 Second)
{
	return float3((First.y*Second.z) - (First.z * Second.y), (First.z * Second.x) - (First.x * Second.z), (First.x * Second.y) - (First.y * Second.x));
}

float3 normalize(float3 normal)
{
	float size = sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2));
	return float3(normal.x / size, normal.y / size, normal.z / size);
}

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

void Heightmap::buildSceneWithOutNormals()
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

}

void Heightmap::buildSceneWithNormals()
{
	PositonColorNormalVertex pushback;
	int m = 0;

	for (int i = 0; i < _heightLength; i++)
	{
		for (int j = 0; j < _widthLength; j++) //bygger inga trianglar med det borde använda indexbuffer T_T
		{
			pushback = { _twodArray[i][j].x, _twodArray[i][j].height / roundDownTheHeight ,_twodArray[i][j].y,
				1.0f,1.0f,0.0f,
				0.f,0.f,0.f,
			};
			_twodArray[i][j].indexValue = m;
			m++;
			VertexwithNormal.push_back(pushback);
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
	float3 edge0 = float3(VertexwithNormal[1].x, VertexwithNormal[1].y, VertexwithNormal[1].z) - float3(VertexwithNormal[0].x, VertexwithNormal[0].y, VertexwithNormal[0].z);
	float3 edge1 = float3(VertexwithNormal[2].x, VertexwithNormal[2].y, VertexwithNormal[2].z) - float3(VertexwithNormal[0].x, VertexwithNormal[0].y, VertexwithNormal[0].z);
	float3 normalen = CrossProductt(edge0, edge1);
	normalen = normalize(normalen);
	*/

	
	for (int i = 0; i < Index.size(); i++)
	{
		float3 edge0 = float3(VertexwithNormal[Index[i + 1]].x, VertexwithNormal[Index[i + 1]].y, VertexwithNormal[Index[i + 1]].z) - float3(VertexwithNormal[Index[i + 0]].x, VertexwithNormal[Index[i + 0]].y, VertexwithNormal[Index[i + 0]].z);
		float3 edge1 = float3(VertexwithNormal[Index[i + 2]].x, VertexwithNormal[Index[i + 2]].y, VertexwithNormal[Index[i + 2]].z) - float3(VertexwithNormal[Index[i + 0]].x, VertexwithNormal[Index[i + 0]].y, VertexwithNormal[Index[i + 0]].z);
		float3 normalen = CrossProductt(edge0, edge1);
		normalen = normalize(normalen);
		VertexwithNormal[Index[i]].N = VertexwithNormal[Index[i]].N + normalen.x;
		VertexwithNormal[Index[i]].NN = VertexwithNormal[Index[i]].NN + normalen.y;
		VertexwithNormal[Index[i]].NNN = VertexwithNormal[Index[i]].NNN + normalen.z;
	
		VertexwithNormal[Index[i + 1]].N = VertexwithNormal[Index[i + 1]].N + normalen.x;
		VertexwithNormal[Index[i + 1]].NN = VertexwithNormal[Index[i + 1]].NN + normalen.y;
		VertexwithNormal[Index[i + 1]].NNN = VertexwithNormal[Index[i + 1]].NNN + normalen.z;

		VertexwithNormal[Index[i + 2]].N = VertexwithNormal[Index[i + 2]].N + normalen.x;
		VertexwithNormal[Index[i + 2]].NN = VertexwithNormal[Index[i + 2]].NN + normalen.y;
		VertexwithNormal[Index[i + 2]].NNN = VertexwithNormal[Index[i + 2]].NNN + normalen.z;
		i++;
		i++;
	}
	for (int i = 0; i < VertexwithNormal.size(); i++)
	{
		float3 test = normalize(float3(VertexwithNormal[i].N / 7, VertexwithNormal[i].NN/ 7, VertexwithNormal[i].NNN / 7));
		VertexwithNormal[i].N = test.x;
		VertexwithNormal[i].NN = test.y;
		VertexwithNormal[i].NNN = test.z;
	}
	

	
}


void Heightmap::test()
{
	_twodArray;
	_twodArray[5][2];
}
