#include "Camera.h"

camera::camera()
{
	camPosition = XMVectorSet(0, 0, -1, 1);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	camYaw = 0.0f;
	camPitch = 0.0f;
	OldPos.x = 0;
	OldPos.y = 0;
	MouseOnOff = false;
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
	//std::cout << "wtf" << std::endl;
}

void camera::DetectInput(double time, HWND wndHandle)
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

//	std::cout << XMVectorGetX(camPosition)<< " "<< XMVectorGetY(camPosition) << " " << XMVectorGetZ(camPosition) << std::endl;
/*	
	if (LMouse)
	{
	//(	ShowCursor(FALSE);
	}
	POINT NewMousepositionen;
	NewMousepositionen.x = 640;
	NewMousepositionen.y = 480;
	if(RMouse)
	{
		ScreenToClient(wndHandle, &NewMousepositionen);
		std::cout << NewMousepositionen.x <<" "<<NewMousepositionen.y << std::endl;
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dx = (NewMousepositionen.x) * (65536 / GetSystemMetrics(SM_CXSCREEN)); //x being coord in pixels
		input.mi.dy = (NewMousepositionen.y) * (65536 / GetSystemMetrics(SM_CYSCREEN)); //y being coord in pixels
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(input));
		ShowCursor(TRUE);
	}
	Frågor:
	Fråga 1:
	Vad anser du om vidde?

	Fråga 2: 
	Anser du att han är väldigt egosentrisk?
	
	Fråga 3: Är han självcentrerad?

	Fråga 4: Bryr sig om sig själv och höjer sig själv över skyarna och försöker tala upp opm sig själv

	Fråga 5: Vad stör du dig på hos Vidde?

	Fråga 6: Han kritiserar mycket runt sig själv eller hur?

	Fråga 7: Han har svårt att inse att världen inte kretsar kring sig fast han inte tror det själv

	Fråga 8: han försöker ta upp en plats men inser det inte.

	Fråga 9: 
	*/
	if (LMouse)
	{
		ShowCursor(FALSE);
		MouseOnOff = true;
	}
	if (RMouse)
	{
		ShowCursor(TRUE);
		MouseOnOff = false;
	}
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

/*	if (MouseOnOff)
	{


		OldPos.x = 640;
		OldPos.y = 480;
		ScreenToClient(wndHandle, &OldPos);
		std::cout << OldPos.x << " " << OldPos.y << std::endl;
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dx = (OldPos.x) * (65536 / GetSystemMetrics(SM_CXSCREEN)); //x being coord in pixels
		input.mi.dy = (OldPos.y) * (65536 / GetSystemMetrics(SM_CYSCREEN)); //y being coord in pixels
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(input));
		ShowCursor(TRUE);
		POINT NewMouseposition;
		GetCursorPos(&NewMouseposition);
		if ((NewMouseposition.x != OldPos.x) || (NewMouseposition.y != OldPos.y))
		{
			camYaw += (NewMouseposition.x - OldPos.x) * 0.001f;

			camPitch += (NewMouseposition.y - OldPos.y) * 0.001f;

			//	OldPos = NewMouseposition;
		}*/

			POINT NewMouseposition;
			GetCursorPos(&NewMouseposition);
			if ((NewMouseposition.x != OldPos.x) || (NewMouseposition.y != OldPos.y))
			{
				camYaw += (NewMouseposition.x-OldPos.x) * 0.001f;

				camPitch += (NewMouseposition.y - OldPos.y) * 0.001f;

				OldPos = NewMouseposition;
			}


			
	//}
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