#pragma once
#include <windows.h>
#include "Gameobject.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#include "Shaders.h"
#include "buffers.h"
class DeansRender
{
private:
	std::vector<GameObject*> test;
	ID3D11Device* gDevice = nullptr;
	IDXGISwapChain* gSwapChain = nullptr;
	ID3D11DeviceContext * gDeviceContext = nullptr;
	ID3D11RenderTargetView* gBackbufferRTV = nullptr;
	Shaders shader;
	bool testet = true;
public:

	DeansRender();
	void update();
	~DeansRender();
	void Gameobjectpush(GameObject* &objectfile);
	ID3D11Device *& gDevicereturn();
	IDXGISwapChain *& gSwapChainreturn();
	ID3D11DeviceContext *& gDeviceContextreturn();
	ID3D11RenderTargetView*& gBackbufferRTVreturn();
};