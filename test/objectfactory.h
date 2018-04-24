#pragma once
#include <windows.h>
#include "Gameobject.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#include "Render.h"
#include "Shaders.h"
#include "Heightmap.h"
#include "Skybox.h"


#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

class GameObjectCreationTriangle
{
private:
	ID3D11ShaderResourceView * gTextureViewen;
public:
	GameObjectCreationTriangle(DeansRender* &renderingsfuntionen);
	GameObjectCreationTriangle(DeansRender* &renderingsfuntionen,int test);
	~GameObjectCreationTriangle();
	GameObjectCreationTriangle();

	void Indexbuffertest(DeansRender* &renderingsfuntionen);

	void GameObjectCreationHeightMap(DeansRender* &renderingsfunction, std::string Name, std::string Normal);
	void GameObjectCreationTriangleTextureTest(DeansRender* &renderingsfuntionen);

	void GameObjectCreationCubeMapSky(DeansRender* &renderingsfunction, int height, int width,int z);
};


