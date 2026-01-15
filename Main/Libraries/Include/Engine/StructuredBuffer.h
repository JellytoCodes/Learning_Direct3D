#pragma once

class StructuredBuffer
{
public :
	StructuredBuffer(void* inputData, uint32 inputStride, uint32 inputCount, uint32 outputStride, uint32 outputCount);
	~StructuredBuffer();

	ComPtr<ID3D11ShaderResourceView>		GetSRV()					{ return _srv; }
	ComPtr<ID3D11UnorderedAccessView>		GetUAV()					{ return _uav; }

	void									CreateBuffer();

	void									CopyToInput(void* data);
	void									CopyFromOutput(void* data);

	uint32									GetInputByteWidth()			{ return _inputStride * _inputCount; }
	uint32									GetOutputByteWidth()		{ return _outputStride * _outputCount; }

private :
	void									CreateInput();
	void									CreateSRV();
	void									CreateOutput();
	void									CreateUAV();
	void									CreateResult();

	// 입력
	ComPtr<ID3D11Buffer>				_input;
	ComPtr<ID3D11ShaderResourceView>	_srv;

	// 출력
	ComPtr<ID3D11Buffer>				_output;
	ComPtr<ID3D11UnorderedAccessView>	_uav;

	// 최종 결과물
	ComPtr<ID3D11Buffer>				_result;	

	void* _inputData;

	uint32 _inputStride = 0;
	uint32 _inputCount = 0;

	uint32 _outputStride = 0;
	uint32 _outputCount = 0;
};

