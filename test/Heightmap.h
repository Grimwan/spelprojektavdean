#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "Structs.h"
struct Grid {
	float x;
	float y;
	float height;
	int indexValue;
};



class Heightmap
{
private:
	int _heightLength = 0;
	int _widthLength = 0;
	Grid** _twodArray;
	std::vector<PositonColorNormalVertex> VertexwithNormal;
	std::vector<PositonColorVertex> Vertex;
	std::vector<int> Index;
public:
	Heightmap();
	~Heightmap();
	void loadingBmpPicture(const char* filename);
	void buildgridarray();
	int getheightLength();
	int getwidhtLength();
	void buildSceneWithOutNormals();
	void buildSceneWithNormals();
	std::vector<PositonColorNormalVertex> returnVertexNormaldata() { return VertexwithNormal; };
	std::vector<PositonColorVertex> returnvertexdata() { return Vertex; };
	std::vector<int> returnIndexdata() { return Index; };

	void test();


};