#include "objectfactory.h"


GameObjectCreationTriangle::~GameObjectCreationTriangle()
{
}

GameObjectCreationTriangle::GameObjectCreationTriangle()
{
}
GameObjectCreationTriangle::GameObjectCreationTriangle(DeansRender* &renderingsfuntionen)
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
