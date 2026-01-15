
RWByteAddressBuffer Output; // UAV

struct ComputeInput
{
	uint3 groupID : SV_GroupID;
	uint3 groupThreadID : SV_GroupThreadID;
	uint3 dispatchThreadID : SV_DispatchThreadID;
	uint groupIndex : SV_GroupIndex;
};

[numthreads(10, 8, 3)]
void CS(ComputeInput input)
{
	uint index = input.groupIndex;
	uint outAddress = index * 10 * 4; // ComputeInput에서 갖고있는 자료 개수(uint3 = 3개 등) * 4byte로 하여 계산한 것이다
	
	Output.Store3(outAddress + 0, input.groupID);
	Output.Store3(outAddress + 12, input.groupThreadID);
	Output.Store3(outAddress + 24, input.dispatchThreadID);
	Output.Store(outAddress + 36, input.groupIndex);
	
}

technique11 T0
{
	pass P0
	{
		SetVertexShader(NULL);
		SetPixelShader(NULL);
		SetComputeShader(CompileShader(cs_5_0, CS()));
	}
}