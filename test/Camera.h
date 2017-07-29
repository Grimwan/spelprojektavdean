#pragma once

#pragma once
#include <windows.h>
#include "Gameobject.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#include "Structs.h"
#include <DirectXMath.h>
#include <dinput.h>
using namespace DirectX;
class camera
{
private:
	XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);


	XMVECTOR camTarget;
	XMVECTOR camUp;
	XMVECTOR camPosition;
	XMMATRIX camView;

	XMMATRIX camRotationMatrix;

	float moveLeftRight = 0.0f;
	float moveBackForward = 0.0f;
	float moveUpDown = 0.0f;
	bool MouseOnOff;
	float camYaw = 0.0f; //left right rotation(y-axis);
	float camPitch = 0.0f; //rotation up/down (x-axis)
	POINT OldPos;
public:
	camera();
	~camera();
	void UpdateCamera();
	void DetectInput(double time, HWND wndHandle);
	XMFLOAT4X4 camview();
	XMMATRIX camviewXmmatrix();
	// Get / set world camera position





};