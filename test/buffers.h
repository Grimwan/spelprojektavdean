#pragma once
#include <windows.h>
#include "Gameobject.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#include "Structs.h"




void constantbufferforPointLight(ID3D11Buffer* &ConstantBufferPointLight,pointlight Pointlightdata, ID3D11Device* &gDevice, ID3D11DeviceContext * &gDeviceContext);
void ConstantBufferForMatrix(ID3D11Buffer* &ConstantBufferWorldMatrix, ID3D11Device* &gDevice, ID3D11DeviceContext * &gDeviceContext);
void createallbuffers(ID3D11Buffer* &ConstantBufferPointLight, ID3D11Device* &gDevice, ID3D11DeviceContext * &gDeviceContext);
