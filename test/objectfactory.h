#pragma once
#include <windows.h>
#include "Gameobject.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#include "Render.h"
#include "Shaders.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

class GameObjectCreationTriangle
{
private:

public:
	GameObjectCreationTriangle(DeansRender* &renderingsfuntionen);
	GameObjectCreationTriangle(DeansRender* &renderingsfuntionen,int test);
	~GameObjectCreationTriangle();
	GameObjectCreationTriangle();

};


