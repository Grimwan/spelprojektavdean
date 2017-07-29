struct GS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Color : COLOR;
	float4 wPos : POSITION;
	float3 normal : NORMAL;
};

cbuffer pointlight : register(b0)
{
	float3 LightPosition;
	float1 LightScale;

};


float4 PS_main(GS_OUT input) : SV_Target
{
	float3 ljusvector = input.wPos.xyz - LightPosition;
	ljusvector = normalize(ljusvector);
	float procentoflight = dot(ljusvector, normalize(input.normal));
//	procentoflight = 1;
//	return float4(input.Color, 1.0f);
	return float4(input.Color*procentoflight, 1.0f);
//	return float4(procentoflight, procentoflight, procentoflight, 1.0f);// kolla färgdjupet
//	return float4(procentoflight.x, ljusvector.y, ljusvector.z, 1.0f); //kollar riktigningen på normalena. 
};