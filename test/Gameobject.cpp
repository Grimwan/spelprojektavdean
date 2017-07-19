#include "Gameobject.h"



GameObject::GameObject(ID3D11Device* &gDevice)
{
	struct TriangleVertex
	{
		float x, y, z;
		float r, g, b;
	};

	TriangleVertex triangleVertices[3] =
	{
		0.0f, 0.5f, 0.0f,	//v0 pos
		1.0f, 0.0f, 0.0f,	//v0 color

		0.5f, -0.5f, 0.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color

		-0.5f, -0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};

	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(triangleVertices);
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = triangleVertices;
	gDevice->CreateBuffer(&bufferDesc, &data, &VertexBuffer);
	HRESULT hr = gDevice->CreateBuffer(&bufferDesc, &data, &this->VertexBuffer);
	if (FAILED(hr))
		std::cout << "Failed to create vertex buffer!" << std::endl;
}



GameObject::~GameObject()
{
	VertexBuffer->Release();
}

GameObject::GameObject()
{
}

GameObject::GameObject(ID3D11Device *& gDevice, std::vector<PositonColorVertex> Positionsochfergdata)
{
	
//	PositonColorVertex * Positonandcolorconverter = &Positionsochfergdata[0];
	
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.ByteWidth = 6*sizeof(float)*(UINT)Positionsochfergdata.size();
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = Positionsochfergdata.data();
	gDevice->CreateBuffer(&bufferDesc, &data, &VertexBuffer);
	HRESULT hr = gDevice->CreateBuffer(&bufferDesc, &data, &this->VertexBuffer);
	if (FAILED(hr))
		std::cout << "Failed to create vertex buffer!" << std::endl;
}
GameObject::GameObject(ID3D11Device *& gDevice, PositonColorVertex * Positionsochfergdata)
{
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(Positionsochfergdata);
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = Positionsochfergdata;
	gDevice->CreateBuffer(&bufferDesc, &data, &VertexBuffer);
	HRESULT hr = gDevice->CreateBuffer(&bufferDesc, &data, &this->VertexBuffer);
	if (FAILED(hr))
		std::cout << "Failed to create vertex buffer!" << std::endl;
}





ID3D11Buffer * GameObject::getVertexbuffer()
{
	return VertexBuffer;
}

void GameObject::draw(ID3D11DeviceContext* &gDeviceContext, ID3D11InputLayout* &gVertexLayout)
{


	UINT32 vertexSize = sizeof(float) * 6;
	UINT32 offset = 0;
	gDeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &vertexSize, &offset);

	gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	gDeviceContext->IASetInputLayout(gVertexLayout);


	gDeviceContext->Draw(3, 0);

}

void GameObject::update()
{

}

std::vector<PositonColorVertex> GameObject::paintingtwotriangles(int differentone)
{


	if(differentone == 1)
	{
	std::vector<PositonColorVertex> testtriangle;
	PositonColorVertex test = {
		0.5f, 0.5f, 0.0f,	//v0 pos
		1.0f, 0.0f, 0.0f,	//v0 color 
	};
	testtriangle.push_back(test);
	test = {
		1.0f, -0.5f, 0.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color
	};
	testtriangle.push_back(test);
	test = {
		0.0f, -0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	testtriangle.push_back(test);
	return testtriangle;
	}
	else if (differentone == 2)
	{

		std::vector<PositonColorVertex> testtriangle;
		PositonColorVertex test = {
			0.0f, 0.5f, 0.0f,	//v0 pos
			1.0f, 0.0f, 0.0f,	//v0 color 
		};
		testtriangle.push_back(test);
		test = {
			0.5f, -0.5f, 0.0f,	//v1
			0.0f, 1.0f, 0.0f,	//v1 color
		};
		testtriangle.push_back(test);
		test = {
			-0.5f, -0.5f, 0.0f, //v2
			0.0f, 0.0f, 1.0f	//v2 color
		};
		testtriangle.push_back(test);
		return testtriangle;
	}
}

void GameObject::changeVertexbufferdata(ID3D11DeviceContext*& gDeviceContext, std::vector<PositonColorVertex> Positionsochfergdata)
{
	D3D11_SUBRESOURCE_DATA data;
//	data.pSysMem = Positionsochfergdata.data();
	D3D11_MAPPED_SUBRESOURCE resource;
	ZeroMemory(&resource, sizeof(D3D11_MAPPED_SUBRESOURCE));
	gDeviceContext->Map(VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, Positionsochfergdata.data(), 6 * sizeof(float)*(UINT)Positionsochfergdata.size());
	gDeviceContext->Unmap(VertexBuffer, 0);
}
