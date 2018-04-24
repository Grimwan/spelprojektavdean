#include "Gameobject.h"



GameObject::GameObject(ID3D11Device* &gDevice)
{
	typeOfObject = AnObject;
	struct TriangleVertex
	{
		float x, y, z;
		float r, g, b;
	};
	VertexLayoutNumber = 0;
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
	IndexBuffer->Release();
	VertexBuffer->Release();
}

GameObject::GameObject()
{
	VertexLayoutNumber = 0;
	typeOfObject = AnObject;
}

GameObject::GameObject(ID3D11Device *& gDevice, std::vector<PositonColorVertex> Positionsochfergdata)
{
	VertexLayoutNumber = 0;
	typeOfObject = AnObject;
	size = Positionsochfergdata.size();
	amountToDraw = size;
	scaling = XMMatrixScaling(0.5, 0.5, 0.5);
	rotation = XMMatrixRotationRollPitchYaw(0,0, 0); // first up down, second left right, z barrelroll
	translation = XMMatrixTranslation(-0.5,-0.5, 0);
	updateworldmatrix();
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

	size = 6;
}
GameObject::GameObject(ID3D11Device *& gDevice, std::vector<PositonColorNormalVertex> Positionsochfergdata, std::vector<int> Indexdata,objectType objectt)
{
	VertexLayoutNumber = 0;
	typeOfObject = objectt;
	size = Positionsochfergdata.size();
	scaling = XMMatrixScaling(0.5, 0.5, 0.5);
	rotation = XMMatrixRotationRollPitchYaw(0, 0, 0); // first up down, second left right, z barrelroll
	translation = XMMatrixTranslation(-0.5, -20, 0);
	updateworldmatrix();
	//	PositonColorVertex * Positonandcolorconverter = &Positionsochfergdata[0];

	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.ByteWidth = 9 * sizeof(float)*(UINT)Positionsochfergdata.size();
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = Positionsochfergdata.data();
	gDevice->CreateBuffer(&bufferDesc, &data, &VertexBuffer);
	HRESULT hr = gDevice->CreateBuffer(&bufferDesc, &data, &this->VertexBuffer);
	if (FAILED(hr))
		std::cout << "Failed to create vertex buffer!" << std::endl;

	amountToDraw = Indexdata.size();

	//creates indexbuffer
	D3D11_BUFFER_DESC bufferIndex;
	bufferIndex.Usage = D3D11_USAGE_DEFAULT;
	bufferIndex.ByteWidth = sizeof(unsigned int) * Indexdata.size();
	bufferIndex.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferIndex.CPUAccessFlags = 0;
	bufferIndex.MiscFlags = 0;

	// Define the resource data.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = Indexdata.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	// Create the buffer with the device.
	hr = gDevice->CreateBuffer(&bufferIndex, &InitData, &IndexBuffer);
	size = 9;
	if (FAILED(hr))
		std::cout << "Failed to create Index buffer!" << std::endl;


}

GameObject::GameObject(ID3D11Device *& gDevice, std::vector<PositonColorVertex> Positionsochfergdata, std::vector<int> Indexdata)
{
	VertexLayoutNumber = 0;
	typeOfObject = AnObject;
	size = Positionsochfergdata.size();
	scaling = XMMatrixScaling(0.5, 0.5, 0.5);
	rotation = XMMatrixRotationRollPitchYaw(0, 0, 0); // first up down, second left right, z barrelroll
	translation = XMMatrixTranslation(-0.5, -0.5, 0);
	updateworldmatrix();
	//	PositonColorVertex * Positonandcolorconverter = &Positionsochfergdata[0];

	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.ByteWidth = 6 * sizeof(float)*(UINT)Positionsochfergdata.size();
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = Positionsochfergdata.data();
	gDevice->CreateBuffer(&bufferDesc, &data, &VertexBuffer);
	HRESULT hr = gDevice->CreateBuffer(&bufferDesc, &data, &this->VertexBuffer);
	if (FAILED(hr))
		std::cout << "Failed to create vertex buffer!" << std::endl;

	amountToDraw = Indexdata.size();

	//creates indexbuffer
	D3D11_BUFFER_DESC bufferIndex;
	bufferIndex.Usage = D3D11_USAGE_DEFAULT;
	bufferIndex.ByteWidth = sizeof(unsigned int) * Indexdata.size();
	bufferIndex.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferIndex.CPUAccessFlags = 0;
	bufferIndex.MiscFlags = 0;

	// Define the resource data.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = Indexdata.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	size = 6;
	// Create the buffer with the device.
	hr = gDevice->CreateBuffer(&bufferIndex, &InitData, &IndexBuffer);
	if (FAILED(hr))
		std::cout << "Failed to create Index buffer!" << std::endl;


}
GameObject::GameObject(ID3D11Device *& gDevice, std::vector<PositionTexture> Positionsochtexture, std::vector<int> Indexdata, ID3D11ShaderResourceView *& gTextureViewen)
{
	VertexLayoutNumber = 2;
	TextureViewen = gTextureViewen;
	typeOfObject = PosTxtShader;
	size = Positionsochtexture.size();
	scaling = XMMatrixScaling(0.5, 0.5, 0.5);
	rotation = XMMatrixRotationRollPitchYaw(0, 0, 0); // first up down, second left right, z barrelroll
	translation = XMMatrixTranslation(-0.5, -0.5, 0);
	updateworldmatrix();
	//	PositonColorVertex * Positonandcolorconverter = &Positionsochfergdata[0];

	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.ByteWidth = 5 * sizeof(float)*(UINT)Positionsochtexture.size();
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = Positionsochtexture.data();
	gDevice->CreateBuffer(&bufferDesc, &data, &VertexBuffer);
	HRESULT hr = gDevice->CreateBuffer(&bufferDesc, &data, &this->VertexBuffer);
	if (FAILED(hr))
		std::cout << "Failed to create vertex buffer!" << std::endl;

	amountToDraw = Indexdata.size();

	//creates indexbuffer
	D3D11_BUFFER_DESC bufferIndex;
	bufferIndex.Usage = D3D11_USAGE_DEFAULT;
	bufferIndex.ByteWidth = sizeof(unsigned int) * Indexdata.size();
	bufferIndex.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferIndex.CPUAccessFlags = 0;
	bufferIndex.MiscFlags = 0;

	// Define the resource data.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = Indexdata.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	size = 5;
	// Create the buffer with the device.
	hr = gDevice->CreateBuffer(&bufferIndex, &InitData, &IndexBuffer);
	if (FAILED(hr))
		std::cout << "Failed to create Index buffer!" << std::endl;


}
GameObject::GameObject(ID3D11Device *& gDevice, PositonColorVertex * Positionsochfergdata)
{
	VertexLayoutNumber = 0;
	typeOfObject = AnObject;
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

	size = 6;
}





ID3D11Buffer * GameObject::getVertexbuffer()
{
	return VertexBuffer;
}

void GameObject::draw(ID3D11DeviceContext* &gDeviceContext, ID3D11InputLayout* &gVertexLayout)
{
	UINT32 vertexSize = sizeof(float) *size;
	UINT32 offset = 0;
	gDeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &vertexSize, &offset);

	if (IndexBuffer!= nullptr)
		gDeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	gDeviceContext->IASetInputLayout(gVertexLayout);

	if (IndexBuffer != nullptr)
		gDeviceContext->DrawIndexed(amountToDraw, 0, 0);
	else
		gDeviceContext->Draw(size, 0);

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

XMMATRIX GameObject::getWorldMatrixXMMATRIX()
{
	return WorldMatrix;
}

XMFLOAT4X4 GameObject::getWorldMatrixXMFLOAT4x4()
{
	DirectX::XMFLOAT4X4 WorldMatrixen;
	XMStoreFloat4x4(&WorldMatrixen, WorldMatrix);
	return WorldMatrixen;
}

void GameObject::setScaling(float scale)
{
	scaling = XMMatrixScaling(scale, scale, scale);
}

void GameObject::setrotx(float rotx)
{
	rotation = XMMatrixRotationX(rotx);
}

void GameObject::setroty(float roty)
{
	rotation = XMMatrixRotationY(roty);
}

void GameObject::setrotz(float rotz)
{
	rotation = XMMatrixRotationZ(rotz);
}

ID3D11ShaderResourceView *& GameObject::TextureViewenreturn()
{
	return TextureViewen;
}

void GameObject::setTypeOfObject(objectType objectType)
{
	typeOfObject = objectType;
}

void GameObject::settranslation(float x, float y, float z)
{
	translation = XMMatrixTranslation(x, y, z);
}

void GameObject::updateworldmatrix()
{
//	WorldMatrix = (scaling * rotation * translation);
//	WorldMatrix = (scaling * translation * rotation);
//	WorldMatrix =  translation*rotation*scaling;
	WorldMatrix = scaling*rotation*translation;
}

void GameObject::animation()
{
	SHORT M = GetAsyncKeyState('M');
	if(M)
	{
	rotation=XMMatrixRotationRollPitchYaw(rotationleftright, rotationupdown, rotationbarrelroll); // first up down, second left right, z barrelroll
	rotationupdown = rotationupdown + 0.001;

	}
	SHORT N = GetAsyncKeyState('N');
	if (N)
	{
		rotation = XMMatrixRotationRollPitchYaw(rotationleftright, rotationupdown, rotationbarrelroll); // first up down, second left right, z barrelroll
		rotationupdown = rotationupdown - 0.001;
	}
	SHORT J = GetAsyncKeyState('J');
	if (J)
	{
		rotation = XMMatrixRotationRollPitchYaw(rotationleftright, rotationupdown, rotationbarrelroll); // first up down, second left right, z barrelroll
		rotationbarrelroll = rotationbarrelroll + 0.001;
	}
	SHORT K = GetAsyncKeyState('K');
	if (K)
	{
		rotation = XMMatrixRotationRollPitchYaw(rotationleftright, rotationupdown, rotationbarrelroll); // first up down, second left right, z barrelroll
		rotationbarrelroll = rotationbarrelroll - 0.001;
	}
	SHORT U = GetAsyncKeyState('U');
	if (U)
	{
		rotation = XMMatrixRotationRollPitchYaw(rotationleftright, rotationupdown, rotationbarrelroll); // first up down, second left right, z barrelroll
		rotationleftright = rotationleftright + 0.001;
	}
	SHORT I = GetAsyncKeyState('I');
	if (I)
	{
		rotation = XMMatrixRotationRollPitchYaw(rotationleftright, rotationupdown, rotationbarrelroll); // first up down, second left right, z barrelroll
		rotationleftright = rotationleftright - 0.001;
	}


}
