#include "Render.h"

DeansRender::DeansRender()
{

}

void DeansRender::update(ID3D11DeviceContext* &gDeviceContext, ID3D11RenderTargetView* &gBackbufferRTV)
{
	if(testet == true)
	{
	shader.createShaders(gDevice);
	testet = false;
	}

	// clear the back buffer to a deep blue
	float clearColor[] = { 0, 0, 0, 1 };
	gDeviceContext->ClearRenderTargetView(gBackbufferRTV, clearColor);

	gDeviceContext->VSSetShader(shader.gVertexShaderReturn(), nullptr, 0);
	gDeviceContext->HSSetShader(nullptr, nullptr, 0);
	gDeviceContext->DSSetShader(nullptr, nullptr, 0);
	gDeviceContext->GSSetShader(nullptr, nullptr, 0);
	gDeviceContext->PSSetShader(shader.gPixelShaderReturn(), nullptr, 0);
	test[0]->draw(gDeviceContext, shader.gVertexLayoutReturn());

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
