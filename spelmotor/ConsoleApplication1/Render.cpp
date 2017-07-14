#include "Render.h"

void render::update()
{
	// clear the back buffer to a deep blue
	float clearColor[] = { 0, 0, 0, 1 };
	gDeviceContext->ClearRenderTargetView(gBackbufferRTV, clearColor);


}
