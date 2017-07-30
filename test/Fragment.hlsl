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
	float3 ljusvector = input.wPos.xyz - LightPosition;
	float distance = length(ljusvector);
	float procentoflight;
	float specfactor = 0;
	if (distance > range)
	{
		 procentoflight = range/distance;
	}
	else
	{



	float3 ljusvectornormalised = normalize(ljusvector);

	float diffusefactor = dot(ljusvector, ljusvectornormalised);
		if (diffusefactor > 0.0f)
		{
			float3 v = normalize(cameraPos - input.wPos.xyz);
			float3 r = reflect(-ljusvector, ljusvectornormalised);
			specfactor = pow(max(dot(r, v),0.0f), 100);

		}
	 procentoflight = dot(ljusvectornormalised, normalize(input.normal));
//	procentoflight = 1;
	}
//	return float4(input.Color, 1.0f);
//	return float4(cameraPos,1.0f);
//	return float4((ambientLight*diffuse + (diffuseLight*diffuse + specularLight)),1.0f);
 	return float4(input.Color*procentoflight+ specfactor, 1.0f);
//	return float4(procentoflight, procentoflight, procentoflight, 1.0f);// kolla färgdjupet
//	return float4(ljusvector.x, ljusvector.y, ljusvector.z, 1.0f); //kollar riktigningen på normalena. 
};