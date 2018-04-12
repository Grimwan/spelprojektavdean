#include "objectfactory.h"


GameObjectCreationTriangle::~GameObjectCreationTriangle()
{
}

GameObjectCreationTriangle::GameObjectCreationTriangle()
{
}
void GameObjectCreationTriangle::Indexbuffertest(DeansRender *& renderingsfuntionen)
{
	std::vector<PositonColorVertex> testtriangle;
	PositonColorVertex test = {
		0.0f, 0.5f, 0.0f,	//v0 pos
		1.0f, 0.0f, 0.0f,	//v0 color 
	};
	testtriangle.push_back(test);
	
	test = {
		0.5f, -0.5f, 0.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color
	};
	testtriangle.push_back(test);
	
	test = {
		-0.5f, -0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	testtriangle.push_back(test);

	test = {
		1.0f, 0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	testtriangle.push_back(test);

	test = {
		1.5f, -0.5f, 0.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color
	};


	testtriangle.push_back(test);

	std::vector<int> Indexdata;
	Indexdata.push_back(0);
	Indexdata.push_back(1);
	Indexdata.push_back(2);

	Indexdata.push_back(0);
	Indexdata.push_back(3);
	Indexdata.push_back(1);

	Indexdata.push_back(3);
	Indexdata.push_back(4);
	Indexdata.push_back(1);



	GameObject * triangletest = new GameObject(renderingsfuntionen->gDevicereturn(), testtriangle,Indexdata);
	renderingsfuntionen->Gameobjectpush(triangletest);
}
void GameObjectCreationTriangle::GameObjectCreationHeightMap(DeansRender *& renderingsfunction, std::string Name,std::string Normal)
{
	
	Heightmap creation;
	creation.loadingBmpPicture(Name.c_str());
	if(Normal == "No")
	{
	creation.buildscene();
	GameObject * triangletest = new GameObject(renderingsfunction->gDevicereturn(), creation.returnvertexdata(), creation.returnIndexdata());
	
	triangletest->setTypeOfObject(heightMapObject);
	
	renderingsfunction->Gameobjectpush(triangletest);
	}
}

GameObjectCreationTriangle::GameObjectCreationTriangle(DeansRender* &renderingsfuntionen)
{
	/*
	std::vector<PositonColorVertex> testtriangle;
	PositonColorVertex test = {
		0.0f, 0.5f, 0.0f,	//v0 pos
		1.0f, 0.0f, 0.0f,	//v0 color 
	};
	testtriangle.push_back(test);
	test = {
		0.5f, -0.5f, 0.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color
	};
	testtriangle.push_back(test);
	test = {
		-0.5f, -0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	
	testtriangle.push_back(test);
	test = {
		0.0f, 0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	testtriangle.push_back(test);
	test = {
		1.0f, 0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	testtriangle.push_back(test);
	test = {
		0.5f, -0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	testtriangle.push_back(test);

	*/
	std::vector<PositonColorVertex> testtriangle;
	PositonColorVertex test = {
		0.0f, 0.5f, 0.0f,	//v0 pos
		1.0f, 0.0f, 0.0f,	//v0 color 
	};
	testtriangle.push_back(test);
	test = {
		0.5f, -0.5f, 10.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color
	};
	testtriangle.push_back(test);
	test = {
		-0.50f, -0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};

	testtriangle.push_back(test);

	GameObject * triangletest = new GameObject(renderingsfuntionen->gDevicereturn(), testtriangle);
	renderingsfuntionen->Gameobjectpush(triangletest);
}

GameObjectCreationTriangle::GameObjectCreationTriangle(DeansRender *& renderingsfuntionen, int mhm)
{

	std::vector<PositonColorVertex> testtriangle;
	PositonColorVertex test = {
		0.5f, 0.5f, 0.0f,	//v0 pos
		1.0f, 0.0f, 0.0f,	//v0 color 
	};
	testtriangle.push_back(test);
	test = {
		1.0f, -0.5f, 0.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color
	};
	testtriangle.push_back(test);
	test = {
		0.0f, -0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	testtriangle.push_back(test);

	GameObject * triangletest = new GameObject(renderingsfuntionen->gDevicereturn(), testtriangle);
	renderingsfuntionen->Gameobjectpush(triangletest);
}

