struct GS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Color : COLOR;
	float4 wPos : POSITION;
	float3 normal : NORMAL;
};

//cbuffer pointlight : register(b0)
//{
//	float3 LightPosition;
//	float1 LightScale;


//};


float4 PS_main(GS_OUT input) : SV_Target
{
	return float4(input.Color, 1.0f);
};