//--------------------------------------------------------------------------------------
// BTH - Stefan Petersson 2014.
//--------------------------------------------------------------------------------------
#include <windows.h>
#include "Test.h"
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include "Render.h"
#include "Gameobject.h"
#include "Shaders.h"
int * pointertest;


HWND InitWindow(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HRESULT CreateDirect3DContext(HWND wndHandle);
DeansRender renderingsfuntionen;






void SetViewport()
{
	D3D11_VIEWPORT vp;
	vp.Width = (float)640;
	vp.Height = (float)480;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	renderingsfuntionen.gDeviceContextreturn()->RSSetViewports(1, &vp);
}

int wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	MSG msg = { 0 };
	HWND wndHandle = InitWindow(hInstance); //1. Skapa fönster
	
	if (wndHandle)
	{
		CreateDirect3DContext(wndHandle); //2. Skapa och koppla SwapChain, Device och Device Context

		SetViewport(); //3. Sätt viewport



//		CreateShaders(); //4. Skapa vertex- och pixel-shaders
//		GameObject Triangle(renderingsfuntionen.gDevicereturn());
//		GameObject * triangletest = &Triangle;
		GameObject * triangletest = new GameObject(renderingsfuntionen.gDevicereturn());
		renderingsfuntionen.Gameobjectpush(triangletest);
		ShowWindow(wndHandle, nCmdShow);

		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
			//	Render(); //8. Rendera
				renderingsfuntionen.update(renderingsfuntionen.gDeviceContextreturn(), renderingsfuntionen.gBackbufferRTVreturn());
				
				renderingsfuntionen.gSwapChainreturn()->Present(0, 0); //9. Växla front- och back-buffer
			}
		}

	//	gVertexBuffer->Release();

//		gVertexLayout->Release();
//		gVertexShader->Release();
//		gPixelShader->Release();

		renderingsfuntionen.gBackbufferRTVreturn()->Release();
		renderingsfuntionen.gSwapChainreturn()->Release();
		renderingsfuntionen.gDevicereturn()->Release();
		renderingsfuntionen.gDeviceContextreturn()->Release();
		DestroyWindow(wndHandle);
	}

	return (int) msg.wParam;
}

HWND InitWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.hInstance      = hInstance;
	wcex.lpszClassName = L"BTH_D3D_DEMO";
	if (!RegisterClassEx(&wcex))
		return false;

	RECT rc = { 0, 0, 640, 480 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND handle = CreateWindow(
		L"BTH_D3D_DEMO",
		L"BTH Direct3D Demo",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	return handle;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;		
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

HRESULT CreateDirect3DContext(HWND wndHandle)
{
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = wndHandle;                           // the window to be used
	scd.SampleDesc.Count = 4;                               // how many multisamples
	scd.Windowed = TRUE;                                    // windowed/full-screen mode

	// create a device, device context and swap chain using the information in the scd struct
	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&renderingsfuntionen.gSwapChainreturn(),
		&renderingsfuntionen.gDevicereturn(),
		NULL,
		&renderingsfuntionen.gDeviceContextreturn());

	if (SUCCEEDED(hr))
	{
		// get the address of the back buffer
		ID3D11Texture2D* pBackBuffer = nullptr;
		renderingsfuntionen.gSwapChainreturn()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		// use the back buffer address to create the render target
		renderingsfuntionen.gDevicereturn()->CreateRenderTargetView(pBackBuffer, NULL, &renderingsfuntionen.gBackbufferRTVreturn());
		pBackBuffer->Release();

		// set the render target as the back buffer
		renderingsfuntionen.gDeviceContextreturn()->OMSetRenderTargets(1, &renderingsfuntionen.gBackbufferRTVreturn(), NULL);
	}
	return hr;
}