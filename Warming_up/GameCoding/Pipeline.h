#pragma once
#include "ConstantBuffer.h"
#include "ShaderBase.h"

class Texture;
class IndexBuffer;
class VertexBuffer;
class RasterizerState;
class SamplerState;
class BlendState;
class PixelShader;
class InputLayout;
class VertexShader;

struct PipelineInfo
{
	shared_ptr<InputLayout> _inputLayout;
	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<PixelShader> _pixelShader;

	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<BlendState> _blendState;

	D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

class Pipeline
{
public :
	Pipeline(ComPtr<ID3D11DeviceContext> deviceContext);
	~Pipeline();

	void UpdatePipeline(PipelineInfo info);

	void SetVertexBuffer(shared_ptr<VertexBuffer> buffer);
	void SetIndexBuffer(shared_ptr<IndexBuffer> buffer);

	template <typename T>
	void SetConstantBuffer(uint32 slot, ShaderScope scope, shared_ptr<ConstantBuffer<T>> buffer);

	void SetTexture(uint32 slot, ShaderScope scope, shared_ptr<Texture> texture);
	void SetSamplerState(uint32 slot, ShaderScope scope, shared_ptr<SamplerState> samplerState);

	void Draw(uint32 vertexCount, uint32 startVertexLocation);
	void DrawIndexed(uint32 vertexCount, uint32 startIndexLocation, uint32 baseVertexLocation);

private :
	ComPtr<ID3D11DeviceContext> _deviceContext;
};

template <typename T>
void Pipeline::SetConstantBuffer(uint32 slot, ShaderScope scope, shared_ptr<ConstantBuffer<T>> buffer)
{
	if (scope == ShaderScope::SS_VertexShader)
	_deviceContext->VSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());

	if (scope == ShaderScope::SS_PixelShader)
	_deviceContext->PSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());
}

