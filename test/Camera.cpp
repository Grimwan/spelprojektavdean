#include "Camera.h"

camera::camera()
{
	camPosition = XMVectorSet(0, 0, -1, 1);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	camYaw = 0.0f;
	camPitch = 0.0f;
	OldPos.x = 0;
	OldPos.y = 0;
}

camera::~camera()
{
}

void camera::UpdateCamera()
{
	//this first 3 updates the target teh camera looks at. 
	camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0); //0 = camroll will roll in z axel wich = barrelroll.
	camTarget = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	camTarget = XMVector3Normalize(camTarget);

	XMMATRIX RotateYTempMatrix;
	RotateYTempMatrix = XMMatrixRotationY(camYaw);

	camRight = XMVector3TransformCoord(DefaultRight, RotateYTempMatrix);
	camUp = XMVector3TransformCoord(camUp, RotateYTempMatrix);
	camForward = XMVector3TransformCoord(DefaultForward, RotateYTempMatrix);

	camPosition += moveLeftRight*camRight;
	camPosition += moveBackForward*camForward;
	camPosition += moveUpDown*camUp;

	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;
	moveUpDown = 0.0f;

	camTarget = camPosition + camTarget;

	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
	std::cout << "wtf" << std::endl;
}

void camera::DetectInput(double time)
{
	SHORT W = GetAsyncKeyState('W');
	SHORT A = GetAsyncKeyState('A');
	SHORT S = GetAsyncKeyState('S');
	SHORT D = GetAsyncKeyState('D');
	SHORT R = GetAsyncKeyState('R');
	SHORT LMouse = GetAsyncKeyState(VK_LBUTTON);
	SHORT RMouse = GetAsyncKeyState(VK_RBUTTON);
	SHORT Space = GetAsyncKeyState(VK_SPACE);
	SHORT LCtrl = GetAsyncKeyState(VK_LCONTROL);
	SHORT LShift = GetAsyncKeyState(VK_LSHIFT);

	std::cout << XMVectorGetX(camPosition)<< " "<< XMVectorGetY(camPosition) << " " << XMVectorGetZ(camPosition) << std::endl;
	
	if (LMouse)
		ShowCursor(FALSE);
	if(RMouse)
		ShowCursor(TRUE);

	

	float speed = 15.0f * time;

	if (A)
	{
		moveLeftRight -= speed;
	}
	if (D)
	{
		moveLeftRight += speed;
	}
	if (W)
	{
		moveBackForward += speed;
	}
	if (S)
	{
		moveBackForward -= speed;
	}
	if (Space)
	{
		moveUpDown += speed;
	}
	if (LCtrl)
	{
		moveUpDown -= speed;
	}
	POINT NewMouseposition;
	GetCursorPos(&NewMouseposition);
	if ((NewMouseposition.x != OldPos.x) || (NewMouseposition.y != OldPos.y))
	{
		camYaw += (NewMouseposition.x-OldPos.x) * 0.001f;

		camPitch += (NewMouseposition.y - OldPos.y) * 0.001f;

		OldPos = NewMouseposition;
	}

	UpdateCamera();

}

XMFLOAT4X4 camera::camview()
{
	DirectX::XMFLOAT4X4 cameravieww;
	XMStoreFloat4x4(&cameravieww, camView);
	return cameravieww;
}

XMMATRIX camera::camviewXmmatrix()
{
	return camView;
}