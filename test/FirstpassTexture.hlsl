Texture2D tex : register(t0);
SamplerState sampAni;
struct GS_OUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
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

PS_OUT PS_main(GS_OUT input) : SV_Target
{

PS_OUT output;
float4 diffuseu = tex.Sample(sampAni, input.Tex);
output.Normal = float4(input.normal, 4);
output.Position = input.wPos;
output.Diffuse = float4(diffuseu.x, diffuseu.y, diffuseu.z, diffuseu.w);
output.Specular = float4(0.1f, 0.1f, 0.1f, 2);
//output.Diffuse = float4(diffuseu.w, diffuseu.w, diffuseu.w,1);
return output;
}
