#include "Global.fx"
#include "Light.fx"

struct VS_OUT
{
	float4 postion : SV_POSITION;
	float2 uv : TEXCOORD;
};

VS_OUT VS(VertexTextureNormalTangent input)
{
		VS_OUT output;
	
		float4 viewPos = mul(float4(input.position.xyz, 0), V);
		float4 clipSpacePos = mul(viewPos, P);	
		output.postion = clipSpacePos.xyzw;
		output.postion.z = output.postion.w * 0.999999f;
		output.uv = input.uv;
		
		return output;
}

float4 PS (VS_OUT input) : SV_TARGET
{
	float color = DiffuseMap.Sample(LinearSampler, input.uv);
	return color;
}

technique11 T0
{
	pass P0
	{
		SetRasterizerState(FrontCounterClockwiseTrue);
		SetVertexShader(CompileShader(vs_5_0, VS()));	
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}