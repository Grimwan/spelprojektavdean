#include "Render.h"

DeansRender::DeansRender()
{
	Lasttime=std::chrono::system_clock::now();
	mProjection = XMMatrixPerspectiveLH(3.141592f*0.45f, (float)640 / (float)480, 0.5f, 200.0f);
	forwardordefered = false;

	blendFactor[0] = 1; blendFactor[1] = 1; blendFactor[2] = 1; blendFactor[3] = 1;



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
	SHORT P = GetAsyncKeyState('P');
	SHORT O = GetAsyncKeyState('O');
	if (P)
		forwardordefered = true;

	if (O)
		forwardordefered = false;


	if(testet == true)
	{
	shader.createShaders(gDevice);
	createallbuffers(ConstantBufferCamera,ConstantBufferPointLight, worldMatrix,gDevice, gDeviceContext);
	GbufferCreation(GBufferSRV, GBufferRTV, gDevice, gDeviceContext);
	//testfunctionGbuffer();
	

	//shit
	HRESULT hr;

	//Creation of Lightpass blendstate
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = true;
	BlendDesc.IndependentBlendEnable = false;
	BlendDesc.RenderTarget[0].BlendEnable = true;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	BlendDesc.AlphaToCoverageEnable = true;
	hr = gDevice->CreateBlendState(&BlendDesc, &BlendState);
	if (FAILED(hr))
		std::cout << "Failed with Blendstate" << std::endl;
	//shit


	}
	if(getfps())
	{
		if(forwardordefered)
	pureDefferedrendering(wndHandle);
		else
	pureForwardrendering(wndHandle);
	}
}

void DeansRender::forwardRendering(objectType Type, ID3D11ShaderResourceView *& gTextureView)
{
	gDeviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);

	if (Type == AnObject)
		shader.objectShaderVSandPS(gDeviceContext);
	else if (Type == heightMapObject)
		shader.forwardrenderingHeightmap(gDeviceContext);
	else if (Type == PosTxtShader)
	{
		gDeviceContext->OMSetBlendState(BlendState, nullptr, 0xffffffff);
		shader.PosTexVsGsPs(gDeviceContext, gTextureView);
	}
}

void DeansRender::pureForwardrendering(HWND wndHandle)
{
		gDeviceContext->VSSetConstantBuffers(0, 1, &worldMatrix);
		gDeviceContext->PSSetConstantBuffers(0, 1, &ConstantBufferPointLight);
		gDeviceContext->PSSetConstantBuffers(1, 1, &ConstantBufferCamera);

	Cameradata cameradataa;
	cameradataa.cameraPos = Camera.returncamPosition();
	//	cameradataa.cameraPos = XMFLOAT3(0, 0, 1);
	updateBufferforCamera(ConstantBufferCamera, cameradataa, gDevice, gDeviceContext);
	// clear the back buffer to a deep blue
	float clearColor[] = { 0, 0, 0, 1 };
	gDeviceContext->ClearRenderTargetView(gBackbufferRTV, clearColor);
	gDeviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//	test[0]->setrotx(25);
	//	test[0]->settranslation(2, 0, 0);
//	test[1]->settranslation(0, 0, 0);

	//	Camera.DetectInput(1);

	

	for (int i = 0; i < test.size(); i++)
	{
		forwardRendering(test[i]->getTypeOfObject(),test[i]->TextureViewenreturn());
		test[i]->animation();
		test[i]->updateworldmatrix();
		Camera.DetectInput(dt, wndHandle);
		XMMATRIX yees = XMMatrixTranspose(test[i]->getWorldMatrixXMMATRIX() * Camera.camviewXmmatrix() * mProjection);

		DirectX::XMFLOAT4X4 yes;
		XMStoreFloat4x4(&yes, yees);
		//	test[i]->changeVertexbufferdata(gDeviceContext, test[i]->paintingtwotriangles(1));

		//	updateBufferMatrix(worldMatrix, gDevice, gDeviceContext,test[i]->getWorldMatrixXMFLOAT4x4());
		//	updateBufferMatrix(worldMatrix, gDevice, gDeviceContext, Camera.camview());
		updateBufferMatrix(worldMatrix, gDevice, gDeviceContext, yes);
		test[i]->draw(gDeviceContext, shader.gVertexLayoutReturn(test[i]->getVertexLayoutNumber()));
	}
}

void DeansRender::pureDefferedrendering(HWND wndHandle)
{
	//	gDeviceContext->VSSetConstantBuffers(0, 1, &worldMatrix);
	//	gDeviceContext->PSSetConstantBuffers(0, 1, &ConstantBufferPointLight);
	//	gDeviceContext->PSSetConstantBuffers(1, 1, &ConstantBufferCamera);
	gDeviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	Cameradata cameradataa;
	cameradataa.cameraPos = Camera.returncamPosition();
	//	cameradataa.cameraPos = XMFLOAT3(0, 0, 1);
	updateBufferforCamera(ConstantBufferCamera, cameradataa, gDevice, gDeviceContext);
	// clear the back buffer to a deep blue
	float clearColor[] = { 0, 0, 0, 1 };
	gDeviceContext->ClearRenderTargetView(gBackbufferRTV, clearColor);
	 

	//	test[0]->setrotx(25);
	//	test[0]->settranslation(2, 0, 0);
//	test[1]->settranslation(0, 0, 20);

	//	Camera.DetectInput(1);

	//	forwardRendering();

	
	memset(&clearColor, 0, sizeof(clearColor));
	for (int i = 0; i < 4; i++)
	{
		gDeviceContext->ClearRenderTargetView(GBufferRTV[i], clearColor);
	}
	for (int i = 0; i < test.size(); i++)
	{
		
		DeferredRenderingFirstPass(test[i]->getTypeOfObject(), test[i]->TextureViewenreturn());	
		test[i]->animation();
		test[i]->updateworldmatrix();
		Camera.DetectInput(dt, wndHandle);
		XMMATRIX yees = XMMatrixTranspose(test[i]->getWorldMatrixXMMATRIX() * Camera.camviewXmmatrix() * mProjection);

		DirectX::XMFLOAT4X4 yes;
		XMStoreFloat4x4(&yes, yees);
		//	test[i]->changeVertexbufferdata(gDeviceContext, test[i]->paintingtwotriangles(1));

		//	updateBufferMatrix(worldMatrix, gDevice, gDeviceContext,test[i]->getWorldMatrixXMFLOAT4x4());
		//	updateBufferMatrix(worldMatrix, gDevice, gDeviceContext, Camera.camview());
		updateBufferMatrix(worldMatrix, gDevice, gDeviceContext, yes);
		test[i]->draw(gDeviceContext, shader.gVertexLayoutReturn(test[i]->getVertexLayoutNumber()));
	}


//	gDeviceContext->OMSetBlendState(BlendState, blendFactor, 0xffffffff);

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

//	gDeviceContext->OMSetBlendState(BlendState, nullptr, 0xffffffff);
	gDeviceContext->Draw(6, 0);

	//	GameObject * triangletest = new GameObject(gDevice, testtriangle);
	//	Gameobjectpush(triangletest);


	//	for (int j = 0;j < test.size();j++)
	//	{

	//	test[j]->changeVertexbufferdata(gDeviceContext, test[j]->paintingtwotriangles(2));
	//		test[j]->draw(gDeviceContext, shader.gVertexLayoutReturn());
	//	}

}

void DeansRender::DeferredRenderingFirstPass(objectType Type, ID3D11ShaderResourceView *& gTextureView)
{
	gDeviceContext->OMSetRenderTargets(4, GBufferRTV, depthStencilView);
	gDeviceContext->VSSetConstantBuffers(0, 1, &worldMatrix);
	gDeviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);

	if (Type == AnObject)
		shader.DeferredRenderingFirstPass(gDeviceContext);
	else if (Type == heightMapObject)
		shader.DeferredRenderingFirstPass(gDeviceContext);
	else if (Type == PosTxtShader)
	{
		gDeviceContext->OMSetBlendState(BlendState, nullptr, 0xffffffff);
		shader.deferedrenderingtexvsgsps(gDeviceContext, gTextureView);
	}
}

void DeansRender::DeferredRenderingSecondPass()
{
	gDeviceContext->OMSetRenderTargets(1,&gBackbufferRTV, depthStencilView);
	gDeviceContext->PSSetConstantBuffers(0, 1, &ConstantBufferPointLight);
	gDeviceContext->PSSetConstantBuffers(1, 1, &ConstantBufferCamera);
	gDeviceContext->PSSetShaderResources(0, 4, GBufferSRV);
	shader.DeferredRenderingSecondPass(gDeviceContext);
}

bool DeansRender::getfps()
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now(); // Get current time
	std::chrono::duration<float> deltaTime = now - this->Lasttime;
	Lasttime = now;
	dt = deltaTime.count();
	time = dt + time;
	if (time >= 1 / 60)
		return true;
	else
	{
		time = 0;
		return false;
	}
}
/*
void DeansRender::setdepthStencilView(ID3D11DepthStencilView * depthStencilView)
{
	this->depthStencilView = depthStencilView;
}
*/
DeansRender::~DeansRender()
{
}


void DeansRender::Gameobjectpush(GameObject*&objectfile)
{
	test.push_back(objectfile);
}

ID3D11DepthStencilView *& DeansRender::depthstencilviewreturn()
{
	return depthStencilView;
}

ID3D11Texture2D *& DeansRender::depthStencilBufferreturn()
{
	return depthStencilBuffer;
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
