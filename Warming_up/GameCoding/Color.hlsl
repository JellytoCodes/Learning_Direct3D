
struct VS_INPUT
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

cbuffer TransformData : register(b0)
{
	row_major matrix matWorld;
	row_major matrix matView;
	row_major matrix matProjection;
}

// 위치와 관련된 변화
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;

	float4 position = mul(input.position, matWorld); // W
	position = mul(position, matView); // V
	position = mul(position, matProjection); //P

	output.position = position;
	output.color = input.color;

	return output;
}

// 색상과 관련된 변화
float4 PS(VS_OUTPUT input) : SV_Target
{
	return input.color;
}