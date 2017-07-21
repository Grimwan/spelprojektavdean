struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Color : COLOR;
	float4 wPos : POSITION;
};


struct GS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Color : COLOR;
	float4 wPos : POSITION;
};

[maxvertexcount(3)]
void GS_main(triangle  VS_OUT input[3], inout TriangleStream< GS_OUT > OutputStream)
{
	GS_OUT output = (GS_OUT)0;

//	float3 edge0 = input[1].wPos - input[0].wPos;
//	float3 edge1 = input[2].wPos - input[0].wPos;
//	float3 normal = cross(edge0, edge1);
//	normalize(normal);

//	float3 dir = normalize(cameraPos - input[0].wPos);
//	float product = dot(normal, dir);


	//if (product >= 0)
	//{
		for (uint i = 0; i < 3; i++)
		{
			GS_OUT element;
			element.Pos = input[i].Pos;
			element.Color = input[i].Color;
			element.wPos = input[i].wPos;
			OutputStream.Append(element);
		}
		OutputStream.RestartStrip();
	//}
}