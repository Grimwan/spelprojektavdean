#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "Structs.h"
struct Grid {
	float x;
	float y;
	float height;
};


class Heightmap
{
private:
	int _heightLength = 0;
	int _widthLength = 0;
	Grid** _twodArray;
	std::vector<PositonColorVertex> Vertex;
public:
	Heightmap();
	~Heightmap();
	void loadingBmpPicture(const char* filename);
	void buildgridarray();
	int getheightLength();
	int getwidhtLength();
	void buildscene();
	std::vector<PositonColorVertex> returnvertexdata() { return Vertex; };

	void test();


};