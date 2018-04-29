Texture2D normalTexture : register(t0);
Texture2D positionTexture : register(t1);
Texture2D diffuseTexture : register(t2);
Texture2D specularTexture : register(t3);

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

void GetGBuffer(in float2 screenPos, out float3 normal, out float3 position, out float4 diffuse, out float3 specular, out float specularPower)
{
	int3 sampleIndices = int3(screenPos.xy, 0);

	normal = normalTexture.Load(sampleIndices).xyz;
	position = positionTexture.Load(sampleIndices).xyz;
	diffuse = diffuseTexture.Load(sampleIndices).xyzw;
	float4 spec = specularTexture.Load(sampleIndices).xyzw;

	specular = spec.xyz;
	specularPower = spec.w;
}

/*
float4 PS_main(float4 screenPos : SV_POSITION) : SV_Target
{
	float3 normal;
	float3 position;
	float3 diffuse;
	float3 specular;
	float specularPower;

	GetGBuffer(screenPos.xy, normal, position, diffuse, specular, specularPower);
	float3 ljusvector = LightPosition - position;
	float distance = length(ljusvector);
	float procentoflight;
	float specfactor = 0;
	if (distance > range)
	{
		procentoflight = range / distance;
	}
	else
	{
		float3 ljusvectornormalised = normalize(ljusvector);

		float diffusefactor = dot(normal, ljusvectornormalised);
		if (diffusefactor > 0.0f)
		{
			float3 v = normalize(cameraPos - position);
			float3 r = reflect(-ljusvectornormalised, normalize(normal));
			specfactor = pow(saturate(dot(r, v)), 100);

		}
		procentoflight = dot(ljusvectornormalised, normalize(normal));
		//	procentoflight = 1;
	}
	//	return float4(diffuse, 1.0f);
	//  return (float4(1, 1, 1, 1));
	//	return float4(cameraPos,1.0f);
	//	return float4((ambientLight*diffuse + (diffuseLight*diffuse + specularLight)),1.0f);
		return float4(diffuse*procentoflight + specfactor, 1.0f);
	//	return float4(specfactor, specfactor, specfactor, 1.0f);
	//	return float4(procentoflight, procentoflight, procentoflight, 1.0f);// kolla färgdjupet
	//	return float4(ljusvector.x, ljusvector.y, ljusvector.z, 1.0f); //kollar riktigningen på normalena. 
};
*/

float4 PS_main(float4 screenPos : SV_POSITION) : SV_Target
{
	float3 normal;
	float3 position;
	float4 diffuse;
	float3 specular;
	float specularPower;

GetGBuffer(screenPos.xy, normal, position, diffuse, specular, specularPower);

	float3 ljusvector = LightPosition - position;
	float distance = length(ljusvector);
	float procentoflight;
	float specfactor = 0;
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
			float3 v = normalize(cameraPos - position);
			float3 r = reflect(-ljusvectornormalised, normalize(normal));
			specfactor = pow(saturate(dot(r, v)), 100);

		}
		procentoflight = dot(ljusvectornormalised, normalize(normal));
		//	procentoflight = 1;
	}
	//	return float4(input.Color, 1.0f);
	//	return float4(cameraPos,1.0f);
	//	return float4((ambientLight*diffuse + (diffuseLight*diffuse + specularLight)),1.0f);
		return float4(diffuse.xyz*procentoflight + specfactor,diffuse.w);
	//	return float4(normal, 1.0f);
//	return diffuse;
	//	return float4(position, 1.0f);
	//	return float4(specfactor, specfactor, specfactor, 1.0f);
	//	return float4(procentoflight, procentoflight, procentoflight, 1.0f);// kolla färgdjupet
	//	return float4(ljusvector.x, ljusvector.y, ljusvector.z, 1.0f); //kollar riktigningen på normalena. 
};