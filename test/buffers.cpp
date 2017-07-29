
#include "buffers.h"





void constantbufferforPointLight(ID3D11Buffer* &ConstantBufferPointLight, pointlight Pointlightdata, ID3D11Device *& gDevice, ID3D11DeviceContext *& gDeviceContext)
{
	HRESULT hr;
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(pointlight);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &Pointlightdata;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	// Create the buffer.
	hr = gDevice->CreateBuffer(&cbDesc, &InitData,
		&ConstantBufferPointLight);

	if (FAILED(hr))
		std::cout << "Failed constantbufferfor pointlight" << std::endl;
	// Set the buffer.
	gDeviceContext->PSSetConstantBuffers(0, 1, &ConstantBufferPointLight);
}

void ConstantBufferForMatrix(ID3D11Buffer *& ConstantBufferWorldMatrix, DirectX::XMFLOAT4X4 WorldMatrix, ID3D11Device *& gDevice, ID3D11DeviceContext *& gDeviceContext)
{
//	DirectX::XMFLOAT4X4 WorldMatrix;
//	XMStoreFloat4x4(&WorldMatrix, WorldMatrixXMMATRIX);
	
	HRESULT hr;
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(XMFLOAT4X4);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;
	//XMFLOAT4X4
	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &WorldMatrix;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	// Create the buffer.
	hr = gDevice->CreateBuffer(&cbDesc, &InitData,
		&ConstantBufferWorldMatrix);

	if (FAILED(hr))
		std::cout << "Failed constantbuffer" << std::endl;
	// Set the buffer.
	gDeviceContext->VSSetConstantBuffers(0, 1, &ConstantBufferWorldMatrix);
}

void createallbuffers(ID3D11Buffer* &ConstantBufferPointLight, ID3D11Buffer* &ConstantBuffermatrix, ID3D11Device* &gDevice, ID3D11DeviceContext * &gDeviceContext)
{
//createPointLightbuffer
	pointlight Firstdatavalues = {
	-1.f, 0.0f, -2.0f,	//v0 pos
//	0.0f, 1.0f, 0.0f,
	1.0f	//v0 range 
};

	
XMMATRIX WorldMatrixXMMATRIX = XMMatrixScaling(1, 1, 1) * XMMatrixRotationX(0) * XMMatrixTranslation(0, 0, 0);
	DirectX::XMFLOAT4X4 WorldMatrix;
	XMStoreFloat4x4(&WorldMatrix, WorldMatrixXMMATRIX);
	constantbufferforPointLight(ConstantBufferPointLight,Firstdatavalues, gDevice, gDeviceContext);
	ConstantBufferForMatrix(ConstantBuffermatrix, WorldMatrix, gDevice, gDeviceContext);
}

void updateBufferMatrix(ID3D11Buffer *& ConstantBuffer, ID3D11Device* &gDevice, ID3D11DeviceContext * &gDeviceContext, DirectX::XMFLOAT4X4 WorldMatrix)
{



	D3D11_MAPPED_SUBRESOURCE resource;
	ZeroMemory(&resource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	gDeviceContext->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	DirectX::XMFLOAT4X4* WorldMatrixmapped = (DirectX::XMFLOAT4X4*)resource.pData;
	*WorldMatrixmapped = WorldMatrix;
	gDeviceContext->Unmap(ConstantBuffer, 0);
}
