#pragma once
#include <windows.h>

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include <iostream>

class GameObject
{
private:
ID3D11Buffer* VertexBuffer = nullptr;


public:
	 GameObject(ID3D11Device * gDevice);
	~GameObject();
	GameObject();
	ID3D11Buffer& getVertexbuffer();

};