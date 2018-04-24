struct VS_IN
{
	float3 Pos : POSITION;
	float3 Tex : TEXCOORD;
	float3 Norm : NORMAL;
};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Tex : TEXCOORD0;
	float3 Norm : TEXCOORD1;
	float3 wPos : POSITION;
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
	output.Tex = input.Tex;
	output.Norm = mul(input.Norm, worldMatrix);
	output.wPos = mul(float4(input.Pos, 1), worldMatrix);



	return output;
}