
struct VS_INPUT
{
	float4 position : POSITION;
	float2 uv : TEXCOORD;
	//float4 color : COLOR;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
	//float4 color : COLOR;
	
};

cbuffer TransformData : register(b0)
{
	float4 offset;
}


// 위치와 관련된 변화
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position = input.position + offset;
	//output.color = input.color;
	output.uv = input.uv;

	return output;
}

Texture2D texture0 : register(t0);
Texture2D texture1 : register(t1);
SamplerState sampler0 : register(s0);

// 색상과 관련된 변화
float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 color = texture1.Sample(sampler0, input.uv);

	return color;
}