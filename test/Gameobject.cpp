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

ID3D11Buffer * GameObject::getVertexbuffer()
{
	return VertexBuffer;
}

void GameObject::draw(ID3D11DeviceContext* gDeviceContext, ID3D11InputLayout* gVertexLayout)
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
