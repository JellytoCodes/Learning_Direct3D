#include "Global.fx"
#include "Light.fx"

struct VS_IN
{
	float4 position : POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	
	// INSTANCING
	uint instanceID : SV_INSTANCEID;
	matrix world : INST;
};

struct VS_OUT
{
	float4 postion : SV_POSITION;
	float3 worldPosition : POSITION1;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
};

VS_OUT VS(VS_IN input)
{
	VS_OUT output;
	
	output.postion = mul(input.position, input.world);
	output.worldPosition = output.postion;
	output.postion = mul(output.postion, VP);
	output.uv = input.uv;
	output.normal = input.normal;
		
	return output;
}

float4 PS (VS_OUT input) : SV_TARGET
{
	float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
	return color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
}