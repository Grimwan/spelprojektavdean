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
	ID3D11InputLayout* gVertexLayout = nullptr;
public:
	void createShaders(ID3D11Device* &gDevice);
	Shaders();
	~Shaders();
	void objectShaderVSandPS(ID3D11DeviceContext * &gDeviceContext);
	ID3D11VertexShader* &gVertexShaderReturn();
	ID3D11PixelShader* &gPixelShaderReturn();
	ID3D11InputLayout* &gVertexLayoutReturn();
};