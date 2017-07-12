#pragma once
#include <windows.h>
#include "Gameobject.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")


class DeansRender
{
private:
	std::vector<GameObject*> test;

public:

	DeansRender();
	void update(ID3D11DeviceContext* &gDeviceContext,ID3D11RenderTargetView* &gBackbufferRTV, ID3D11VertexShader* &gVertexShader,ID3D11PixelShader* &gPixelShader, ID3D11InputLayout* &gVertexLayout);
	~DeansRender();
	void Gameobjectpush(GameObject* &objectfile);

};