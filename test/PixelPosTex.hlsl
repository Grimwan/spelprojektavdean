Texture2D tex : register(t0);
SamplerState sampAni;
struct GS_OUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
	float4 wPos : POSITION;
	float3 normal : NORMAL;
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

float4 PS_main(GS_OUT input) : SV_Target
{
	float3 ljusvector = LightPosition - input.wPos.xyz;
	float distance = length(ljusvector);
	float procentoflight;
	float specfactor = 0;
	//	float3 hardcodednormal = float3(0, 1, 0);
	if (distance > range)
	{
		procentoflight = range / distance;
	}
	else
	{
		float3 ljusvectornormalised = normalize(ljusvector);

		float diffusefactor = dot(ljusvector, ljusvectornormalised);
		if (diffusefactor > 0.0f)
		{
			float3 v = normalize(cameraPos - input.wPos.xyz);
			float3 r = reflect(-ljusvectornormalised, normalize(input.normal));
			specfactor = pow(saturate(dot(r, v)), 100);

		}
		procentoflight = dot(ljusvectornormalised, normalize(input.normal));
		//	procentoflight = 1;
	}



	float4 diffuseu = tex.Sample(sampAni, input.Tex);


	return float4(diffuseu.xyz*procentoflight + specfactor, diffuseu.w);
//	return float4(diffuseu);
//	return float4(diffuseu.w, diffuseu.w, diffuseu.w, 0);
}