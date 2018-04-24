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
enum objectType { heightMapObject, AnObject,Skyboxobject,PosTxtShader};

class GameObject
{
private:
int VertexLayoutNumber;
ID3D11Buffer* VertexBuffer = nullptr;
ID3D11Buffer* IndexBuffer = nullptr;
ID3D11ShaderResourceView* TextureViewen = nullptr;

int testet = 0;
XMMATRIX scaling;
XMMATRIX rotation;
XMMATRIX translation;
XMMATRIX WorldMatrix;
float rotationleftright=0;
float rotationupdown = 0;
float rotationbarrelroll = 0;
int size = 0;
int amountToDraw = 0;
objectType typeOfObject;
public:
	 GameObject(ID3D11Device * &gDevice);
	
	~GameObject();
	GameObject();
	GameObject(ID3D11Device * &gDevice,std::vector<PositonColorVertex> Positionsochfergdata);
	GameObject(ID3D11Device * &gDevice, std::vector<PositonColorVertex> Positionsochfergdata,std::vector<int> Indexdata);
	GameObject(ID3D11Device * &gDevice, std::vector<PositionTexture> Positionsochtexture, std::vector<int> Indexdata, ID3D11ShaderResourceView* &gTextureViewen);
	GameObject(ID3D11Device * &gDevice,PositonColorVertex* Positionsochfergdata);

	GameObject(ID3D11Device * &gDevice, std::vector<PositonColorNormalVertex> Positionsochfergdata, std::vector<int> Indexdata, objectType objectt);
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
	ID3D11ShaderResourceView *& TextureViewenreturn();
	void setVertexLayoutNumber(int 	VertexLayoutNumber) { VertexLayoutNumber = this->VertexLayoutNumber; };
	int getVertexLayoutNumber() {return VertexLayoutNumber;};
	void setTypeOfObject(objectType objectType);
	objectType getTypeOfObject() { return typeOfObject; };
	void settranslation(float x, float y, float z);
	void updateworldmatrix();
	void animation();
};