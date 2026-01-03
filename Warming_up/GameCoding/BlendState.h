#pragma once

class BlendState
{
public :
	BlendState(ComPtr<ID3D11Device> device);
	~BlendState();

	ComPtr<ID3D11BlendState> GetComPtr() { return _blendState; }
	const float* GetBlendFactor() const { return &_blendFactor; }
	uint32 GetSampleMask() const { return _sampleMask; }

	void Create();

private :
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11BlendState> _blendState;
	float _blendFactor = 0.f;
	uint32 _sampleMask = 0xFFFFFFFF;
};

