struct VS_IN
{
	float3 Pos : POSITION;
};

cbuffer pointlight : register(b0)
{
	float3 LightPosition;
	float range;
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;

};
cbuffer Cameradata : register(b1)
{
	float3 cameraPos;
	float something;
};



float4 VS_main(VS_IN input) : SV_POSITION
{
	
	return float4(input.Pos, 1.0f);
}