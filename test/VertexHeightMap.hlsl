struct VS_IN
{
	float3 Pos : POSITION;
	float3 Color : COLOR;
	float3 normal : NORMAL;
};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Color : COLOR;
	float4 wPos : POSITION;
	float3 normal : NORMAL;
};


cbuffer WorldMatrix : register(b0)
{
	float4x4 worldMatrix;
}


//-----------------------------------------------------------------------------------------
// VertexShader: VSScene
//-----------------------------------------------------------------------------------------
VS_OUT VS_main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	output.Pos = mul(float4(input.Pos, 1), worldMatrix);
	output.Color = input.Color;
	output.wPos = mul(float4(input.Pos, 1), worldMatrix);
	output.normal = input.normal;
	//	output.Pos = float4(input.Pos, 1);
	//	output.wPos = float4(input.Pos, 1);


	return output;
}