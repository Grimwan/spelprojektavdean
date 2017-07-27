#include "Render.h"

DeansRender::DeansRender()
{

}

void DeansRender::update()
{
	if(testet == true)
	{
	shader.createShaders(gDevice);
	createallbuffers(ConstantBufferPointLight, worldMatrix,gDevice, gDeviceContext);
	testet = false;
	}

	// clear the back buffer to a deep blue
	float clearColor[] = { 0, 0, 0, 1 };
	gDeviceContext->ClearRenderTargetView(gBackbufferRTV, clearColor);

	shader.objectShaderVSandPS(gDeviceContext);
//	test[0]->setrotx(25);
//	test[0]->settranslation(2, 0, 0);


//	Camera.DetectInput(1);
	for (int i = 0;i < test.size();i++)
	{
		test[i]->animation();
		test[i]->updateworldmatrix();
//		XMMATRIX yees = Camera.camviewXmmatrix()*test[i]->getWorldMatrixXMMATRIX();

//		DirectX::XMFLOAT4X4 yes;
//		XMStoreFloat4x4(&yes, yees);
		//	test[i]->changeVertexbufferdata(gDeviceContext, test[i]->paintingtwotriangles(1));
		
	//	updateBufferMatrix(worldMatrix, gDevice, gDeviceContext,test[i]->getWorldMatrixXMFLOAT4x4());
	//	updateBufferMatrix(worldMatrix, gDevice, gDeviceContext, Camera.camview());
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
