
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

void createallbuffers(ID3D11Buffer *& ConstantBufferCamera,ID3D11Buffer* &ConstantBufferPointLight, ID3D11Buffer* &ConstantBuffermatrix, ID3D11Device* &gDevice, ID3D11DeviceContext * &gDeviceContext)
{
//createPointLightbuffer
//	pointlight Firstdatavalues = {
//	-2.f, 0.0f, -1.0f,	//v0 pos
//	0.0f, 1.0f, 0.0f,
//	1.0f	//v0 range 
//};
	pointlight Firstdatavalues;
	Firstdatavalues.Position = XMFLOAT3(-2.f, 0.0f, -1.0f);
	Firstdatavalues.range = 25.0f;
	Firstdatavalues.Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	Firstdatavalues.Diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	Firstdatavalues.Specular = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);

	Cameradata Firstcameradata;
	Firstcameradata.cameraPos = XMFLOAT3(0.f, 0.f, 1.f);
	Firstcameradata.camerasomething = 1;

	XMMATRIX WorldMatrixXMMATRIX = XMMatrixScaling(1, 1, 1) * XMMatrixRotationX(0) * XMMatrixTranslation(0, 0, 0);
	DirectX::XMFLOAT4X4 WorldMatrix;
	XMStoreFloat4x4(&WorldMatrix, WorldMatrixXMMATRIX);
	constantbufferforCamera(ConstantBufferCamera, Firstcameradata, gDevice, gDeviceContext);
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

void constantbufferforCamera(ID3D11Buffer *& ConstantBufferCamera, Cameradata cameradata, ID3D11Device *& gDevice, ID3D11DeviceContext *& gDeviceContext)
{
	HRESULT hr;
	D3D11_BUFFER_DESC cbDescs;
	cbDescs.ByteWidth = sizeof(Cameradata);
	cbDescs.Usage = D3D11_USAGE_DYNAMIC;
	cbDescs.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDescs.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDescs.MiscFlags = 0;
	cbDescs.StructureByteStride = 0;

	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA InitDatas;
	InitDatas.pSysMem = &cameradata;
	InitDatas.SysMemPitch = 0;
	InitDatas.SysMemSlicePitch = 0;

	// Create the buffer.
	hr = gDevice->CreateBuffer(&cbDescs, &InitDatas,
		&ConstantBufferCamera);

	if (FAILED(hr))
		std::cout << "Failed constantbufferfor Camera" << std::endl;
	// Set the buffer.
	gDeviceContext->PSSetConstantBuffers(1, 1, &ConstantBufferCamera);
}

void updateBufferforCamera(ID3D11Buffer*& ConstantBuffer, Cameradata camera, ID3D11Device *& gDevice, ID3D11DeviceContext *& gDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	ZeroMemory(&resource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	gDeviceContext->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	Cameradata* CameradataMaped = (Cameradata*)resource.pData;
	*CameradataMaped = camera;
	gDeviceContext->Unmap(ConstantBuffer, 0);
}

void GbufferCreation(ID3D11ShaderResourceView* GBufferSRV[4],ID3D11RenderTargetView* GBufferRTV[4], ID3D11Device *& gDevice, ID3D11DeviceContext *& gDeviceContext)
{
	HRESULT hr;
	D3D11_TEXTURE2D_DESC GBufferDesc;
	ZeroMemory(&GBufferDesc, sizeof(GBufferDesc));
	GBufferDesc.Width = (float)640;
	GBufferDesc.Height = (float)480;
	GBufferDesc.MipLevels = 1;
	GBufferDesc.ArraySize = 1;
	GBufferDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	GBufferDesc.SampleDesc.Count = 1;
	GBufferDesc.SampleDesc.Quality = 0;
	GBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	GBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	GBufferDesc.MiscFlags = 0;
	GBufferDesc.CPUAccessFlags = 0;

	ID3D11Texture2D *pTexture[4];
	for (int i = 0; i < 4; i++)
	{
		hr = gDevice->CreateTexture2D(&GBufferDesc, NULL, &pTexture[i]);

		if FAILED(hr)
			std::cout << "Failed to create GBuffer Texture." << std::endl;
	}
	D3D11_RENDER_TARGET_VIEW_DESC GBufferRTVViewDesc;
	ZeroMemory(&GBufferRTVViewDesc, sizeof(GBufferRTVViewDesc));
	GBufferRTVViewDesc.Format = GBufferDesc.Format;
	GBufferRTVViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	D3D11_SHADER_RESOURCE_VIEW_DESC GBufferResViewDesc;
	ZeroMemory(&GBufferResViewDesc, sizeof(GBufferResViewDesc));
	GBufferResViewDesc.Format = GBufferDesc.Format;
	GBufferResViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	GBufferResViewDesc.Texture2D.MipLevels = GBufferDesc.MipLevels;
	GBufferResViewDesc.Texture2D.MostDetailedMip = 0;

	for (int i = 0; i < 4; i++)
	{
		hr = gDevice->CreateRenderTargetView(pTexture[i], &GBufferRTVViewDesc, &GBufferRTV[i]);
		if FAILED(hr)
			std::cout << "Failed to create GBuffer RTV number " << i << "." << std::endl;
		hr = gDevice->CreateShaderResourceView(pTexture[i], &GBufferResViewDesc, &GBufferSRV[i]);
		if FAILED(hr)
			std::cout << "Failed to create GBuffer SRV number " << i << "." << std::endl;
	}
	for (int i = 0; i < 4; i++)
		pTexture[i]->Release();
}


