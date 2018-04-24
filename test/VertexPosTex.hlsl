struct VS_IN
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
	float4 wPos : POSITION;
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
	output.wPos = mul(float4(input.Pos, 1), worldMatrix);



	return output;
}