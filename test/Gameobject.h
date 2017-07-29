#pragma once
#include <windows.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#include "Structs.h"
#include <iostream>
#include <DirectXMath.h>
#include <dinput.h>
using namespace DirectX;

class GameObject
{
private:
ID3D11Buffer* VertexBuffer = nullptr;
int testet = 0;
XMMATRIX scaling;
XMMATRIX rotation;
XMMATRIX translation;
XMMATRIX WorldMatrix;
float rotationleftright=0;
float rotationupdown = 0;
float rotationbarrelroll = 0;

public:
	 GameObject(ID3D11Device * &gDevice);
	
	~GameObject();
	GameObject();
	GameObject(ID3D11Device * &gDevice,std::vector<PositonColorVertex> Positionsochfergdata);
	GameObject(ID3D11Device * &gDevice,PositonColorVertex* Positionsochfergdata);
	ID3D11Buffer * getVertexbuffer();
	void draw(ID3D11DeviceContext* &gDeviceContext, ID3D11InputLayout* &gVertexLayout);
	void update();
	std::vector<PositonColorVertex> paintingtwotriangles(int differentmovement);
	void changeVertexbufferdata(ID3D11DeviceContext* &gDeviceContext, std::vector<PositonColorVertex> Positionsochfergdata);
	XMMATRIX getWorldMatrixXMMATRIX();
	XMFLOAT4X4 getWorldMatrixXMFLOAT4x4();
	void setScaling(float scale);
	void setrotx(float rotx);
	void setroty(float roty);
	void setrotz(float rotz);
	void settranslation(float x, float y, float z);
	void updateworldmatrix();
	void animation();
};