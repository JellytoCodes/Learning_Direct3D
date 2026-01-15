#pragma once
class RawBuffer
{
public :
	RawBuffer(void* inputData, uint32 inputByte, uint32 outputByte);
	~RawBuffer();
	ComPtr<ID3D11ShaderResourceView> GetSRV() { return _srv; }
	ComPtr<ID3D11UnorderedAccessView> GetUAV() { return _uav; }

	void		CreateBuffer();

	void		CopyToInput(void* data);
	void		CopyFromOutput(void* data);

private :
	void		CreateInput();
	void		CreateSRV();
	void		CreateOutput();
	void		CreateUAV();
	void		CreateResult();

	// 입력
	ComPtr<ID3D11Buffer>				_input;
	ComPtr<ID3D11ShaderResourceView>	_srv;

	// 출력
	ComPtr<ID3D11Buffer>				_output;
	ComPtr<ID3D11UnorderedAccessView>	_uav;

	// 최종 결과물
	ComPtr<ID3D11Buffer>				_result;

	void*								_inputData;
	uint32								_inputByte = 0;
	uint32								_outputByte = 0;

};