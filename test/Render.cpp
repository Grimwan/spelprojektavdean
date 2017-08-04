#include "Render.h"

DeansRender::DeansRender()
{
	mProjection = XMMatrixPerspectiveLH(3.141592f*0.45f, (float)640 / (float)480, 0.5f, 200.0f);
}
void DeansRender::testfunctionGbuffer()
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
void DeansRender::update(HWND wndHandle)
{
	if(testet == true)
	{
	shader.createShaders(gDevice);
	createallbuffers(ConstantBufferCamera,ConstantBufferPointLight, worldMatrix,gDevice, gDeviceContext);
	GbufferCreation(GBufferSRV, GBufferRTV, gDevice, gDeviceContext);
	//testfunctionGbuffer();
	
	}
//	gDeviceContext->VSSetConstantBuffers(0, 1, &worldMatrix);
//	gDeviceContext->PSSetConstantBuffers(0, 1, &ConstantBufferPointLight);
//	gDeviceContext->PSSetConstantBuffers(1, 1, &ConstantBufferCamera);

	Cameradata cameradataa;
	cameradataa.cameraPos = Camera.returncamPosition();
//	cameradataa.cameraPos = XMFLOAT3(0, 0, 1);
	updateBufferforCamera(ConstantBufferCamera, cameradataa, gDevice,gDeviceContext);
	// clear the back buffer to a deep blue
	float clearColor[] = { 0, 0, 0, 1 };
	gDeviceContext->ClearRenderTargetView(gBackbufferRTV, clearColor);


//	test[0]->setrotx(25);
//	test[0]->settranslation(2, 0, 0);
	test[1]->settranslation(0, 0, 0);

//	Camera.DetectInput(1);

//	forwardRendering();


	DeferredRenderingFirstPass();
	for (int i = 0;i < test.size();i++)
	{
		test[i]->animation();
		test[i]->updateworldmatrix();
		Camera.DetectInput(0.00001,wndHandle);
		XMMATRIX yees = XMMatrixTranspose(test[i]->getWorldMatrixXMMATRIX() * Camera.camviewXmmatrix() * mProjection);

		DirectX::XMFLOAT4X4 yes;
		XMStoreFloat4x4(&yes, yees);
		//	test[i]->changeVertexbufferdata(gDeviceContext, test[i]->paintingtwotriangles(1));
		
	//	updateBufferMatrix(worldMatrix, gDevice, gDeviceContext,test[i]->getWorldMatrixXMFLOAT4x4());
	//	updateBufferMatrix(worldMatrix, gDevice, gDeviceContext, Camera.camview());
		updateBufferMatrix(worldMatrix, gDevice, gDeviceContext,yes);
		test[i]->draw(gDeviceContext, shader.gVertexLayoutReturn(0));
	}
	



	DeferredRenderingSecondPass();
	
	gDeviceContext->IASetInputLayout(shader.gVertexLayoutReturn(1));
	if (testet == true)
	{
	std::vector<PositonSecondVertexPass> Cubeinfrontofcamera;
	PositonSecondVertexPass Cube = {
		-1.0f, -1.0f, 0.0f	//v0 pos
	};
	Cubeinfrontofcamera.push_back(Cube);
	Cube = {
		-1.0f, 1.0f, 0.0f //v1 pos
	};
	Cubeinfrontofcamera.push_back(Cube);
	Cube = {
		1.0f, -1.0f, 0.0f //v2
	};
	Cubeinfrontofcamera.push_back(Cube);



	Cube = {
		-1.0f, 1.0f, 0.0f //v2
		
	};
	Cubeinfrontofcamera.push_back(Cube);
	Cube = {
		1.0f, 1.0f, 0.0f	//v0 pos
	};
	Cubeinfrontofcamera.push_back(Cube);
	Cube = {
		1.0f, -1.0f, 0.0f //v2
		
	};
	Cubeinfrontofcamera.push_back(Cube);


		D3D11_BUFFER_DESC bufferDesc;
		memset(&bufferDesc, 0, sizeof(bufferDesc));
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.ByteWidth = 3 * sizeof(float)*(UINT)Cubeinfrontofcamera.size();
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = Cubeinfrontofcamera.data();
		gDevice->CreateBuffer(&bufferDesc, &data, &VertexBufferforCube);
		HRESULT hr = gDevice->CreateBuffer(&bufferDesc, &data, &this->VertexBufferforCube);
		if (FAILED(hr))
			std::cout << "Failed to create vertex buffer!" << std::endl;
		testet = false;
	}


	UINT32 vertexSize = sizeof(float) * 3;
	UINT32 offset = 0;
	gDeviceContext->IASetVertexBuffers(0, 1, &VertexBufferforCube, &vertexSize, &offset);

	gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	gDeviceContext->IASetInputLayout(shader.gVertexLayoutReturn(1));


	gDeviceContext->Draw(6, 0);
//	GameObject * triangletest = new GameObject(gDevice, testtriangle);
//	Gameobjectpush(triangletest);


//	for (int j = 0;j < test.size();j++)
//	{

	//	test[j]->changeVertexbufferdata(gDeviceContext, test[j]->paintingtwotriangles(2));
//		test[j]->draw(gDeviceContext, shader.gVertexLayoutReturn());
//	}
	
}

void DeansRender::forwardRendering()
{
	shader.objectShaderVSandPS(gDeviceContext);
}

void DeansRender::DeferredRenderingFirstPass()
{
	float clearColor[4];
	memset(&clearColor, 0, sizeof(clearColor));
	for (int i = 0; i < 4; i++)
	{
		gDeviceContext->ClearRenderTargetView(GBufferRTV[i], clearColor);
	}
	gDeviceContext->OMSetRenderTargets(4, GBufferRTV, nullptr);
	gDeviceContext->VSSetConstantBuffers(0, 1, &worldMatrix);
	shader.DeferredRenderingFirstPass(gDeviceContext);

}

void DeansRender::DeferredRenderingSecondPass()
{
	gDeviceContext->OMSetRenderTargets(1,&gBackbufferRTV, nullptr);
	gDeviceContext->PSSetConstantBuffers(0, 1, &ConstantBufferPointLight);
	gDeviceContext->PSSetConstantBuffers(1, 1, &ConstantBufferCamera);
	gDeviceContext->PSSetShaderResources(0, 4, GBufferSRV);
	shader.DeferredRenderingSecondPass(gDeviceContext);
}

DeansRender::~DeansRender()
{
}


void DeansRender::Gameobjectpush(GameObject*&objectfile)
{
	test.push_back(objectfile);
}

ID3D11Device *& DeansRender::gDevicereturn()
{
	return gDevice;
	// TODO: insert return statement here
}

IDXGISwapChain *& DeansRender::gSwapChainreturn()
{
	return gSwapChain;
	// TODO: insert return statement here
}

ID3D11DeviceContext *& DeansRender::gDeviceContextreturn()
{
	return gDeviceContext;
	// TODO: insert return statement here
}

ID3D11RenderTargetView *& DeansRender::gBackbufferRTVreturn()
{
	return gBackbufferRTV;
	// TODO: insert return statement here
}
