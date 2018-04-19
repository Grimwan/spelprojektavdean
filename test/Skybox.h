#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "Structs.h"

class Skybox
{
private:
	std::vector<PositonColorVertex> Vertex;
	std::vector<int> Indexdata;
public:
	Skybox();
	~Skybox();
	void buildCube(int height, int width, int z);
	std::vector<PositonColorVertex> returnvertexdata() { return Vertex; };
	std::vector<int> returnIndexdata() { return Indexdata; };
};