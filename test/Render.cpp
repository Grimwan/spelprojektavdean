#include "Render.h"

DeansRender::DeansRender()
{
}

void DeansRender::update(ID3D11DeviceContext* &gDeviceContext, ID3D11RenderTargetView* &gBackbufferRTV, ID3D11VertexShader* &gVertexShader, ID3D11PixelShader* &gPixelShader, ID3D11InputLayout* &gVertexLayout)
{

	//test

	//test


	// clear the back buffer to a deep blue
	float clearColor[] = { 0, 0, 0, 1 };
	gDeviceContext->ClearRenderTargetView(gBackbufferRTV, clearColor);

	gDeviceContext->VSSetShader(gVertexShader, nullptr, 0);
	gDeviceContext->HSSetShader(nullptr, nullptr, 0);
	gDeviceContext->DSSetShader(nullptr, nullptr, 0);
	gDeviceContext->GSSetShader(nullptr, nullptr, 0);
	gDeviceContext->PSSetShader(gPixelShader, nullptr, 0);
	test[0]->draw(gDeviceContext, gVertexLayout);

}

DeansRender::~DeansRender()
{
}

void DeansRender::Gameobjectpush(GameObject*&objectfile)
{
	test.push_back(objectfile);
}
