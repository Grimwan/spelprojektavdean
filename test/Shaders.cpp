#include "Shaders.h"

void Shaders::createShaders(ID3D11Device* &gDevice)
{
	ID3DBlob* errorBlob;
	HRESULT hr;
	//create vertex shader
	ID3DBlob* pVS = nullptr;
	D3DCompileFromFile(
		L"Vertex.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"VS_main",		// entry point
		"vs_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pVS,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);

	gDevice->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &gVertexShader);


//	float4 wPos : POSITION
	//create input layout (verified using vertex shader)
	D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	gDevice->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &gVertexLayout);
	// we do not need anymore this COM object, so we release it.
	pVS->Release();










	//create Geometry shader
	
	//Geometry shader
	ID3DBlob* pGS = nullptr;
	hr = D3DCompileFromFile(L"GeometryShader.hlsl", nullptr, nullptr, "GS_main", "gs_4_0", 0, 0, &pGS, &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob != nullptr)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
		}
	}
	gDevice->CreateGeometryShader(pGS->GetBufferPointer(), pGS->GetBufferSize(), nullptr, &gGeometryShader);

	pGS->Release();
	
	
	
	
	







	//create pixel shader
	ID3DBlob* pPS = nullptr;
	D3DCompileFromFile(
		L"Fragment.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"PS_main",		// entry point
		"ps_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pPS,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);

	gDevice->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), nullptr, &gPixelShader);
	// we do not need anymore this COM object, so we release it.
	pPS->Release();












	//create pixel shader
	ID3DBlob* pPSFirstPassDeferred = nullptr;
hr =	D3DCompileFromFile(
		L"FragmentShaderFirstPass.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"PS_main",		// entry point
		"ps_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pPSFirstPassDeferred,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);
	if (FAILED(hr))
	{
		if (errorBlob != nullptr)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
		}
	}

	gDevice->CreatePixelShader(pPSFirstPassDeferred->GetBufferPointer(), pPSFirstPassDeferred->GetBufferSize(), nullptr, &gPixelShaderFirstpass);
	// we do not need anymore this COM object, so we release it.
	pPSFirstPassDeferred->Release();











	//create vertex shader
	ID3DBlob* pVSSecondpass = nullptr;
	D3DCompileFromFile(
		L"VertexSecondpass.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"VS_main",		// entry point
		"vs_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pVSSecondpass,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);

	gDevice->CreateVertexShader(pVSSecondpass->GetBufferPointer(), pVSSecondpass->GetBufferSize(), nullptr, &gVertexSecondShader);

	D3D11_INPUT_ELEMENT_DESC inputDescC[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	gDevice->CreateInputLayout(inputDescC, ARRAYSIZE(inputDescC), pVSSecondpass->GetBufferPointer(), pVSSecondpass->GetBufferSize(), &SecondgVertexLayout);
	// we do not need anymore this COM object, so we release it.
	pVSSecondpass->Release();



	//create pixel shader
	ID3DBlob* pPSSecondPassDeferred = nullptr;
	hr = D3DCompileFromFile(
		L"FragmentSecondPass.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"PS_main",		// entry point
		"ps_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pPSSecondPassDeferred,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);
	if (FAILED(hr))
	{
		if (errorBlob != nullptr)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
		}
	}

	gDevice->CreatePixelShader(pPSSecondPassDeferred->GetBufferPointer(), pPSSecondPassDeferred->GetBufferSize(), nullptr, &gPixelShaderSecondpass);
	// we do not need anymore this COM object, so we release it.
	pPSSecondPassDeferred->Release();












	//create vertex shader
	ID3DBlob* VertexshaderHeightMap = nullptr;
	D3DCompileFromFile(
		L"VertexHeightMap.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"VS_main",		// entry point
		"vs_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&VertexshaderHeightMap,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);

	gDevice->CreateVertexShader(VertexshaderHeightMap->GetBufferPointer(), VertexshaderHeightMap->GetBufferSize(), nullptr, &gVertexHeightmap);

	D3D11_INPUT_ELEMENT_DESC inputDescheightmap[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }	
	};
	gDevice->CreateInputLayout(inputDescheightmap, ARRAYSIZE(inputDescheightmap), VertexshaderHeightMap->GetBufferPointer(), VertexshaderHeightMap->GetBufferSize(), &gVertexLayout);
	// we do not need anymore this COM object, so we release it.
	VertexshaderHeightMap->Release();


	//create pixel shader
	ID3DBlob* HeightMapPixelForward = nullptr;
	hr = D3DCompileFromFile(
		L"PixelHeightmapForward.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"PS_main",		// entry point
		"ps_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&HeightMapPixelForward,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);
	if (FAILED(hr))
	{
		if (errorBlob != nullptr)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
		}
	}

	gDevice->CreatePixelShader(HeightMapPixelForward->GetBufferPointer(), HeightMapPixelForward->GetBufferSize(), nullptr, &gPixelShaderHeightmapforward);
	// we do not need anymore this COM object, so we release it.
	HeightMapPixelForward->Release();








	


	//Position Texture

	
	//create vertex shader
	ID3DBlob* pVertexPosTex = nullptr;
	D3DCompileFromFile(
		L"VertexPosTex.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"VS_main",		// entry point
		"vs_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pVertexPosTex,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);

	gDevice->CreateVertexShader(pVertexPosTex->GetBufferPointer(), pVertexPosTex->GetBufferSize(), nullptr, &VertexPosTexShader);


	//	float4 wPos : POSITION
	//create input layout (verified using vertex shader)
	D3D11_INPUT_ELEMENT_DESC inputDescPosTex[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	gDevice->CreateInputLayout(inputDescPosTex, ARRAYSIZE(inputDescPosTex), pVertexPosTex->GetBufferPointer(), pVertexPosTex->GetBufferSize(), &gVertexLayoutPosTex);
	// we do not need anymore this COM object, so we release it.
	pVertexPosTex->Release();

	






	

	//create Geometry shader

	//Geometry shader
	ID3DBlob* pGSPosTex = nullptr;
	hr = D3DCompileFromFile(L"GeometryPosTex.hlsl", nullptr, nullptr, "GS_main", "gs_4_0", 0, 0, &pGSPosTex, &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob != nullptr)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
		}
	}
	gDevice->CreateGeometryShader(pGSPosTex->GetBufferPointer(), pGSPosTex->GetBufferSize(), nullptr, &GeometryPosTexShader);

	pGSPosTex->Release();












	//create pixel shader
	ID3DBlob* pPSposTex = nullptr;
	D3DCompileFromFile(
		L"PixelPosTex.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"PS_main",		// entry point
		"ps_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pPSposTex,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);

	gDevice->CreatePixelShader(pPSposTex->GetBufferPointer(), pPSposTex->GetBufferSize(), nullptr, &PixelPosTexShader);
	// we do not need anymore this COM object, so we release it.
	pPSposTex->Release();

	
	

}

Shaders::Shaders()
{


}

Shaders::~Shaders()
{
	gVertexLayout->Release();
	gVertexShader->Release();
	gPixelShader->Release();
	SecondgVertexLayout->Release();

}

void Shaders::forwardrenderingHeightmap(ID3D11DeviceContext *& gDeviceContext)
{
	gDeviceContext->VSSetShader(gVertexHeightmap, nullptr, 0);
	gDeviceContext->HSSetShader(nullptr, nullptr, 0);
	gDeviceContext->DSSetShader(nullptr, nullptr, 0);
	gDeviceContext->GSSetShader(nullptr, nullptr, 0);
	gDeviceContext->PSSetShader(gPixelShaderHeightmapforward, nullptr, 0);
}

void Shaders::PosTexVsGsPs(ID3D11DeviceContext *& gDeviceContext, ID3D11ShaderResourceView *& gTextureView)
{
	gDeviceContext->VSSetShader(VertexPosTexShader, nullptr, 0);
	gDeviceContext->HSSetShader(nullptr, nullptr, 0);
	gDeviceContext->DSSetShader(nullptr, nullptr, 0);

	gDeviceContext->GSSetShader(GeometryPosTexShader, nullptr, 0);
	gDeviceContext->PSSetShaderResources(0, 1, &gTextureView);
	gDeviceContext->PSSetShader(PixelPosTexShader, nullptr, 0);

}

void Shaders::objectShaderVSandPS(ID3D11DeviceContext *& gDeviceContext)
{
	gDeviceContext->VSSetShader(gVertexShader, nullptr, 0);
	gDeviceContext->HSSetShader(nullptr, nullptr, 0);
	gDeviceContext->DSSetShader(nullptr, nullptr, 0);
	gDeviceContext->GSSetShader(gGeometryShader, nullptr, 0);
	gDeviceContext->PSSetShader(gPixelShader, nullptr, 0);
}

void Shaders::DeferredRenderingFirstPass(ID3D11DeviceContext *& gDeviceContext)
{
	gDeviceContext->VSSetShader(gVertexShader, nullptr, 0);
	gDeviceContext->HSSetShader(nullptr, nullptr, 0);
	gDeviceContext->DSSetShader(nullptr, nullptr, 0);
	gDeviceContext->GSSetShader(gGeometryShader, nullptr, 0);
	gDeviceContext->PSSetShader(gPixelShaderFirstpass, nullptr, 0);
}

void Shaders::DeferredRenderingSecondPass(ID3D11DeviceContext *& gDeviceContext)
{
	gDeviceContext->VSSetShader(gVertexSecondShader, nullptr, 0);
	gDeviceContext->HSSetShader(nullptr, nullptr, 0);
	gDeviceContext->DSSetShader(nullptr, nullptr, 0);
	gDeviceContext->GSSetShader(nullptr, nullptr, 0);
	gDeviceContext->PSSetShader(gPixelShaderSecondpass, nullptr, 0);
}

ID3D11VertexShader *& Shaders::gVertexShaderReturn(int firstsecond)
{
	if (firstsecond == 0)
		return gVertexShader;
	else
		return gVertexSecondShader;
	// TODO: insert return statement here
}

ID3D11PixelShader *& Shaders::gPixelShaderReturn(int firstsecond)
{
	if (firstsecond == 0)
		return gPixelShader;
	else if (firstsecond == 1)
		return gPixelShaderFirstpass;
	else if (firstsecond == 2)
		return gPixelShaderSecondpass;
	// TODO: insert return statement here
}

ID3D11InputLayout *& Shaders::gVertexLayoutReturn(int firstsecond)
{
	if (firstsecond == 0)
		return gVertexLayout;
	else if (firstsecond == 1)
		return SecondgVertexLayout;
	else if (firstsecond == 2)
		return gVertexLayoutPosTex;
	// TODO: insert return statement here
}
