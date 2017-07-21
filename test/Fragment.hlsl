struct GS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Color : COLOR;
	float4 wPos : POSITION;
};

float4 PS_main(GS_OUT input) : SV_Target
{
	return float4(input.Color, 1.0f);
};