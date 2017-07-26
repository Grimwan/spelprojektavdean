
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

void ConstantBufferForMatrix(ID3D11Buffer *& ConstantBufferWorldMatrix, ID3D11Device *& gDevice, ID3D11DeviceContext *& gDeviceContext)
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

void createallbuffers(ID3D11Buffer* &ConstantBufferPointLight, ID3D11Device* &gDevice, ID3D11DeviceContext * &gDeviceContext)
{
//createPointLightbuffer
	pointlight Firstdatavalues = {
	-3.f, 0.0f, -1.0f,	//v0 pos
//	0.0f, 1.0f, 0.0f,
	1.0f	//v0 range 
};
	constantbufferforPointLight(ConstantBufferPointLight,Firstdatavalues, gDevice, gDeviceContext);

}
