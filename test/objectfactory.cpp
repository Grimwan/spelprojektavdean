#include "objectfactory.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GameObjectCreationTriangle::~GameObjectCreationTriangle()
{
}

GameObjectCreationTriangle::GameObjectCreationTriangle()
{
}
void GameObjectCreationTriangle::Indexbuffertest(DeansRender *& renderingsfuntionen)
{
	std::vector<PositonColorVertex> testtriangle;
	PositonColorVertex test = {
		0.0f, 1.0f, 0.0f,	//v0 pos
		1.0f, 0.0f, 0.0f,	//v0 color 
	};
	testtriangle.push_back(test);
	
	test = {
		1.0f, 0.0f, 0.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color
	};
	testtriangle.push_back(test);
	
	test = {
		0.0f, 0.0f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	testtriangle.push_back(test);

	test = {
		1.0f, 1.0f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	testtriangle.push_back(test);

	test = {
		1.0f, 0.0f, 0.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color
	};


	testtriangle.push_back(test);

	std::vector<int> Indexdata;
	Indexdata.push_back(0);
	Indexdata.push_back(1);
	Indexdata.push_back(2);

	Indexdata.push_back(0);
	Indexdata.push_back(3);
	Indexdata.push_back(1);

//	Indexdata.push_back(3);
//	Indexdata.push_back(4);
//	Indexdata.push_back(1);



	GameObject * triangletest = new GameObject(renderingsfuntionen->gDevicereturn(), testtriangle,Indexdata);
	renderingsfuntionen->Gameobjectpush(triangletest);
}
void GameObjectCreationTriangle::GameObjectCreationHeightMap(DeansRender *& renderingsfunction, std::string Name,std::string Normal)
{
	
	Heightmap creation;
	creation.loadingBmpPicture(Name.c_str());
	if(Normal == "No")
	{
	creation.buildSceneWithOutNormals();
	GameObject * triangletest = new GameObject(renderingsfunction->gDevicereturn(), creation.returnvertexdata(), creation.returnIndexdata());
	
//	triangletest->setTypeOfObject(heightMapObject);
	
	renderingsfunction->Gameobjectpush(triangletest);
	}
	if (Normal == "Yes")
	{
		creation.buildSceneWithNormals();
		GameObject * triangletest = new GameObject(renderingsfunction->gDevicereturn(), creation.returnVertexNormaldata(), creation.returnIndexdata(), heightMapObject);

			triangletest->setTypeOfObject(heightMapObject);
	//	triangletest->setTypeOfObject(AnObject);
		renderingsfunction->Gameobjectpush(triangletest);
	}

}

void GameObjectCreationTriangle::GameObjectCreationTriangleTextureTest(DeansRender *& renderingsfuntionen)
{
	int height, width, channels;
	float* pictureData = stbi_loadf("Timmy.png", &height, &width, &channels, STBI_rgb_alpha);


	D3D11_TEXTURE2D_DESC bthTexDesc;
	ZeroMemory(&bthTexDesc, sizeof(bthTexDesc));
	bthTexDesc.Width = width;
	bthTexDesc.Height = height;
	bthTexDesc.MipLevels = bthTexDesc.ArraySize = 1;
//	bthTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bthTexDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	bthTexDesc.SampleDesc.Count = 1;
	bthTexDesc.SampleDesc.Quality = 0;
	bthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	bthTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	bthTexDesc.MiscFlags = 0;
	bthTexDesc.CPUAccessFlags = 0;

	//create texture from raw data (float*)
	ID3D11Texture2D  *pTexture = NULL;  //Pointer to the resource that will serve as input to a shader. This resource must have been created with the D3D11_BIND_SHADER_RESOURCE flag. 
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = (void*)pictureData;
	data.SysMemPitch = width * 4 * sizeof(float);
	renderingsfuntionen->gDevicereturn()->CreateTexture2D(&bthTexDesc, &data, &pTexture);

	// resource view description 
	D3D11_SHADER_RESOURCE_VIEW_DESC resViewDesc;
	ZeroMemory(&resViewDesc, sizeof(resViewDesc));
	resViewDesc.Format = bthTexDesc.Format;
	resViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	resViewDesc.Texture2D.MipLevels = bthTexDesc.MipLevels;
	resViewDesc.Texture2D.MostDetailedMip = 0;
	renderingsfuntionen->gDevicereturn()->CreateShaderResourceView(pTexture, &resViewDesc, &gTextureViewen);
	pTexture->Release(); // releaseing tge texture

	std::vector<PositionTexture> testtriangle;
	PositionTexture test = {
		0.0f, 10.0f, 0.0f,	//v0 pos
		0.0f, 0.0f,	//v0 color 
	};
	testtriangle.push_back(test);

	test = {
		10.0f, 0.0f, 0.0f,	//v1
		1.0f, 1.0f,	//v1 color
	};
	testtriangle.push_back(test);

	test = {
		0.0f, 0.0f, 0.0f, //v2
		0.0f, 1.0f,	//v2 color
	};
	testtriangle.push_back(test);

	test = {
		10.0f, 10.0f, 0.0f,	//v0 pos
		1.0f, 0.0f,	//v0 color 
	};
	testtriangle.push_back(test);


	std::vector<int> Indexdata;
	Indexdata.push_back(0);
	Indexdata.push_back(1);
	Indexdata.push_back(2);

	Indexdata.push_back(0);
	Indexdata.push_back(3);
	Indexdata.push_back(1);

	GameObject * triangletest = new GameObject(renderingsfuntionen->gDevicereturn(), testtriangle, Indexdata,gTextureViewen);
	triangletest->setTypeOfObject(PosTxtShader);
	renderingsfuntionen->Gameobjectpush(triangletest);
}

void GameObjectCreationTriangle::GameObjectCreationCubeMapSky(DeansRender *& renderingsfunction,int height , int width, int z)
{
	Skybox skybox;
	skybox.buildCube(width, height,z);
	GameObject * triangletest = new GameObject(renderingsfunction->gDevicereturn(), skybox.returnvertexdata(), skybox.returnIndexdata());
	renderingsfunction->Gameobjectpush(triangletest);
}


GameObjectCreationTriangle::GameObjectCreationTriangle(DeansRender* &renderingsfuntionen)
{

	std::vector<PositonColorVertex> testtriangle;
	PositonColorVertex test = {
		0.0f, 0.5f, 0.0f,	//v0 pos
		1.0f, 0.0f, 0.0f,	//v0 color 
	};
	testtriangle.push_back(test);
	test = {
		0.5f, -0.5f, 0.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color
	};
	testtriangle.push_back(test);
	test = {
		-0.5f, -0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	
	testtriangle.push_back(test);
	test = {
		0.0f, 0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	testtriangle.push_back(test);
	test = {
		1.0f, 0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	testtriangle.push_back(test);
	test = {
		0.5f, -0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	testtriangle.push_back(test);

	
	/*
	std::vector<PositonColorVertex> testtriangle;
	PositonColorVertex test = {
		0.0f, 0.5f, 0.0f,	//v0 pos
		1.0f, 0.0f, 0.0f,	//v0 color 
	};
	testtriangle.push_back(test);
	test = {
		0.5f, -0.5f, 10.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color
	};
	testtriangle.push_back(test);
	test = {
		-0.50f, -0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	*/
	testtriangle.push_back(test);

	GameObject * triangletest = new GameObject(renderingsfuntionen->gDevicereturn(), testtriangle);
	renderingsfuntionen->Gameobjectpush(triangletest);
}

GameObjectCreationTriangle::GameObjectCreationTriangle(DeansRender *& renderingsfuntionen, int mhm)
{

	std::vector<PositonColorVertex> testtriangle;
	PositonColorVertex test = {
		0.5f, 0.5f, 0.0f,	//v0 pos
		1.0f, 0.0f, 0.0f,	//v0 color 
	};
	testtriangle.push_back(test);
	test = {
		1.0f, -0.5f, 0.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color
	};
	testtriangle.push_back(test);
	test = {
		0.0f, -0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};
	testtriangle.push_back(test);

	GameObject * triangletest = new GameObject(renderingsfuntionen->gDevicereturn(), testtriangle);
	renderingsfuntionen->Gameobjectpush(triangletest);
}

