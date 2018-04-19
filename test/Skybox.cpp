#include "Skybox.h"

Skybox::Skybox()
{
}

Skybox::~Skybox()
{
}

void Skybox::buildCube(int height, int width,int z)
{

	//Front
	PositonColorVertex test = {
		0.0f, (float)height, 0.0f,	//v0 pos
		1.0f, 0.0f, 0.0f,	//v0 color 
	};
	Vertex.push_back(test);

	test = {
		(float)width, (float)height, 0.0f,	//v1
		1.0f, 0.0f, 0.0f,	//v1 color
	};
	Vertex.push_back(test);

	test = {
		0.0f, 0.0f, 0.0f, //v2
		1.0f, 0.0f, 0.0f	//v2 color
	};
	Vertex.push_back(test);

	test = {
		(float)width, 0.0f, 0.0f, //v2
		1.0f, 0.0f, 0.0f	//v2 color
	};
	Vertex.push_back(test);

	///////////////////////////////
	 test = {
		0.0f, (float)height, (float)-z,	//v0 pos
		0.0f, 1.0f, 0.0f,	//v0 color 
	};
	Vertex.push_back(test);

	test = {
		(float)width, (float)height, (float)-z,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color
	};
	Vertex.push_back(test);

	test = {
		0.0f, 0.0f, (float)-z, //v2
		0.0f, 1.0f, 0.0f	//v2 color
	};
	Vertex.push_back(test);

	test = {
		(float)width, 0.0f, (float)-z, //v2
		0.0f, 1.0f, 0.0f	//v2 color
	};
	Vertex.push_back(test);
	


	//front side of the box
	Indexdata.push_back(0);
	Indexdata.push_back(1);
	Indexdata.push_back(2);

	Indexdata.push_back(1);
	Indexdata.push_back(3);
	Indexdata.push_back(2);

	//right side of the box
	
	Indexdata.push_back(1);
	Indexdata.push_back(5);
	Indexdata.push_back(3);

	Indexdata.push_back(5);
	Indexdata.push_back(7);
	Indexdata.push_back(3);

	//left side of the box

	Indexdata.push_back(2);
	Indexdata.push_back(4);
	Indexdata.push_back(0);

	Indexdata.push_back(2);
	Indexdata.push_back(6);
	Indexdata.push_back(4);

	//back side of the box
	Indexdata.push_back(6);
	Indexdata.push_back(5);
	Indexdata.push_back(4);

	Indexdata.push_back(6);
	Indexdata.push_back(7);
	Indexdata.push_back(5);

	//upper side of the box
	Indexdata.push_back(0);
	Indexdata.push_back(4);
	Indexdata.push_back(5);

	Indexdata.push_back(0);
	Indexdata.push_back(5);
	Indexdata.push_back(1);

	//Down side of the box
	Indexdata.push_back(2);
	Indexdata.push_back(3);
	Indexdata.push_back(7);

	Indexdata.push_back(2);
	Indexdata.push_back(7);
	Indexdata.push_back(6);



}
