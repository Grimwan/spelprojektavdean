#ifndef STRUCTS_H
#define STRUCTS_H
#include <windows.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include <iostream>
#include <DirectXMath.h>
#include <dinput.h>
using namespace DirectX;
#pragma once
struct PositonColorVertex
{
	float x, y, z;
	float r, g, b;
};

struct PositonColorNormalVertex
{
	float x, y, z;
	float r, g, b;
	float N, NN, NNN;
};


struct PositonSecondVertexPass
{
	float x, y, z;
};
struct pointlight
{
	pointlight()
	{
		ZeroMemory(this, sizeof(pointlight));
	}
	XMFLOAT3 Position;
	float range;
	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Specular;
};
struct Cameradata
{
	Cameradata()
	{
		ZeroMemory(this, sizeof(Cameradata));
	}
	XMFLOAT3 cameraPos;
	float camerasomething;
};

struct float3 
{
	float x, y, z; 
	float3() { x = 0; y = 0; z = 0; }
	float3(int x, int y, int z) { this->x = x, this->y = y, this->z = z; };
	

	float3 operator-(const float3& o)
	{
		return float3(x - o.x, y - o.y, z - o.z);
	}


};


#endif