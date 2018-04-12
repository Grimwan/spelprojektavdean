struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Color : COLOR;
	float4 wPos : POSITION;
	float3 normal : NORMAL;
};

struct PS_OUT
{
	float4 Normal : SV_Target0;
	float4 Position : SV_Target1;
	float4 Diffuse : SV_Target2;
	float4 Specular : SV_Target3;
};


PS_OUT PS_main(VS_OUT input)
{
	PS_OUT output;
	output.Normal = float4(input.normal, 1.0f);
	output.Position = input.wPos;
	output.Diffuse = float4(input.Color, 1.0f);
	output.Specular = float4(0.3f, 0.3f, 0.3f, 1);
	return output;
};