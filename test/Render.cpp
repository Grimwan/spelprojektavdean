#include "Render.h"

DeansRender::DeansRender()
{
	mProjection = XMMatrixPerspectiveLH(3.141592f*0.45f, (float)640 / (float)480, 0.5f, 200.0f);
}

void DeansRender::update(HWND wndHandle)
{
	if(testet == true)
	{
	shader.createShaders(gDevice);
	createallbuffers(ConstantBufferCamera,ConstantBufferPointLight, worldMatrix,gDevice, gDeviceContext);
	testet = false;
	}
	Cameradata cameradataa;
	cameradataa.cameraPos = Camera.returncamPosition();
//	cameradataa.cameraPos = XMFLOAT3(0, 0, 1);
	updateBufferforCamera(ConstantBufferCamera, cameradataa, gDevice,gDeviceContext);
	// clear the back buffer to a deep blue
	float clearColor[] = { 0, 0, 0, 1 };
	gDeviceContext->ClearRenderTargetView(gBackbufferRTV, clearColor);

	shader.objectShaderVSandPS(gDeviceContext);
//	test[0]->setrotx(25);
//	test[0]->settranslation(2, 0, 0);
	test[1]->settranslation(0, 0, 0);

//	Camera.DetectInput(1);
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
		test[i]->draw(gDeviceContext, shader.gVertexLayoutReturn());
	}


//	for (int j = 0;j < test.size();j++)
//	{

	//	test[j]->changeVertexbufferdata(gDeviceContext, test[j]->paintingtwotriangles(2));
//		test[j]->draw(gDeviceContext, shader.gVertexLayoutReturn());
//	}
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
