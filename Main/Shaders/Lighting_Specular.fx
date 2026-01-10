#include "Global.fx"

float3 LightDir;			// 광원에 대한 방향
float4 LightSpecular;		// 스펙큘러에 대한 색상
float4 MaterialSpecular;	// 물체가 받아들이는 스펙큘러값

Texture2D DiffuseMap;

MeshOutput VS(VertexTextureNormal input)
{
	MeshOutput output;

	output.position = mul(input.position, W);
	output.worldPosition = input.position.xyz;
	output.position = mul(output.position, VP);
	
	output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);

	return output;
}

// Specular (반사광)
// 한방향으로 완전히 반사되는 빛 (Phong)
float4 PS(MeshOutput input) : SV_TARGET
{
	float3 R = reflect(LightDir, input.normal);
	// == float3 R = LightDir - (2 * input.normal * dot(LightDir, normalize(input.normal)));
	R = normalize(R);
	
	float3 cameraPosition = -V._41_42_43;
	float3 E = normalize(cameraPosition - input.worldPosition);
	
	float value = saturate(dot(R, E));	// clamp(0 ~ 1)
	float specular = pow(value, 10);
	
	float color = LightSpecular * MaterialSpecular * specular;
	
	return color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
}