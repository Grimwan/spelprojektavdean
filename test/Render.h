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
#include "Camera.h"
#include <chrono>
#include <ctime>
class DeansRender
{
private:
	std::vector<GameObject*> test;
	ID3D11Device* gDevice = nullptr;
	IDXGISwapChain* gSwapChain = nullptr;
	ID3D11DeviceContext * gDeviceContext = nullptr;
	ID3D11RenderTargetView* gBackbufferRTV = nullptr;
	//constantbuffer
	ID3D11ShaderResourceView* GBufferSRV[4];
	ID3D11RenderTargetView* GBufferRTV[4];
	ID3D11Buffer* VertexBufferforCube = nullptr;
	ID3D11Buffer* ConstantBufferPointLight = nullptr;
	ID3D11Buffer* ConstantBufferCamera = nullptr;
	ID3D11Buffer* worldMatrix = nullptr;
	XMMATRIX mProjection;
	Shaders shader;
	std::chrono::time_point<std::chrono::system_clock> Lasttime;
	float time;
	float dt;
	bool forwardordefered;
	bool testet = true;
	camera Camera;
public:

	DeansRender();
	void update(HWND wndHandle);
	~DeansRender();
	void forwardRendering();
	void pureForwardrendering(HWND wndHandle);
	void pureDefferedrendering(HWND wndHandle);
	void DeferredRenderingFirstPass();
	void DeferredRenderingSecondPass();
	bool getfps();
	void Gameobjectpush(GameObject* &objectfile);
	ID3D11Device *& gDevicereturn();
	IDXGISwapChain *& gSwapChainreturn();
	void testfunctionGbuffer();
	ID3D11DeviceContext *& gDeviceContextreturn();
	ID3D11RenderTargetView*& gBackbufferRTVreturn();
};