#pragma once
#include <windows.h>
#include "Gameobject.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")


class Shaders
{
private:
	ID3D11VertexShader* gVertexShader = nullptr;
	ID3D11GeometryShader* gGeometryShader = nullptr;
	ID3D11PixelShader* gPixelShader = nullptr;

	ID3D11PixelShader* gPixelShaderFirstpass = nullptr;
	ID3D11VertexShader* gVertexSecondShader = nullptr;
	ID3D11PixelShader* gPixelShaderSecondpass = nullptr;

	ID3D11VertexShader* gVertexHeightmap = nullptr;
	ID3D11PixelShader* gPixelShaderHeightmapforward = nullptr;

	ID3D11InputLayout* gVertexLayoutPosTex = nullptr;
	ID3D11InputLayout* gVertexLayout = nullptr;
	ID3D11InputLayout* SecondgVertexLayout = nullptr;

	ID3D11VertexShader* VertexPosTexShader = nullptr;
	ID3D11GeometryShader* GeometryPosTexShader = nullptr;
	ID3D11PixelShader* PixelPosTexShader = nullptr;
	ID3D11ShaderResourceView * gTextureView;

public:
	void createShaders(ID3D11Device* &gDevice);
	Shaders();
	~Shaders();
	void forwardrenderingHeightmap(ID3D11DeviceContext * &gDeviceContext);
	void PosTexVsGsPs(ID3D11DeviceContext * &gDeviceContext, ID3D11ShaderResourceView *& gTextureView);
	void objectShaderVSandPS(ID3D11DeviceContext * &gDeviceContext);
	void DeferredRenderingFirstPass(ID3D11DeviceContext * &gDeviceContext);
	void DeferredRenderingSecondPass(ID3D11DeviceContext * &gDeviceContext);
	ID3D11VertexShader* &gVertexShaderReturn(int firstsecond);
	ID3D11PixelShader* &gPixelShaderReturn(int firstsecond);
	ID3D11InputLayout* &gVertexLayoutReturn(int firstsecond);
};