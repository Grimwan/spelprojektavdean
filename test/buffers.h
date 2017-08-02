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
void ConstantBufferForMatrix(ID3D11Buffer* &ConstantBufferWorldMatrix, DirectX::XMFLOAT4X4 WorldMatrix,ID3D11Device* &gDevice, ID3D11DeviceContext * &gDeviceContext);
void createallbuffers(ID3D11Buffer *& ConstantBufferCamera,ID3D11Buffer* &ConstantBufferPointLight,ID3D11Buffer* &worldMatrix, ID3D11Device* &gDevice, ID3D11DeviceContext * &gDeviceContext);
void updateBufferMatrix(ID3D11Buffer* &ConstantBuffer, ID3D11Device* &gDevice, ID3D11DeviceContext * &gDeviceContext, DirectX::XMFLOAT4X4 WorldMatrixXMMATRIX);
void constantbufferforCamera(ID3D11Buffer* &ConstantBufferCamera, Cameradata camera, ID3D11Device* &gDevice, ID3D11DeviceContext * &gDeviceContext);
void updateBufferforCamera(ID3D11Buffer* &ConstantBufferCamera, Cameradata camera, ID3D11Device* &gDevice, ID3D11DeviceContext * &gDeviceContext);
void GbufferCreation(ID3D11ShaderResourceView* GBufferSRV[4], ID3D11RenderTargetView* GBufferRTV[4], ID3D11Device* &gDevice, ID3D11DeviceContext * &gDeviceContext);