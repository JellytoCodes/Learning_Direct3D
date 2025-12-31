#include "pch.h"
#include "Pipeline.h"
#include "InputLayout.h"
#include "Shader.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "SamplerState.h"

Pipeline::Pipeline(ComPtr<ID3D11DeviceContext> deviceContext) : _deviceContext(deviceContext)
{

}

Pipeline::~Pipeline()
{

}

void Pipeline::UpdatePipeline(PipelineInfo info)
{
	_deviceContext->IASetInputLayout(info._inputLayout->GetComPtr().Get());
	_deviceContext->IASetPrimitiveTopology(info.topology);

	// VS
	if (info._vertexShader)
	_deviceContext->VSSetShader(info._vertexShader->GetComPtr().Get(), nullptr, 0);

	// RS
	if (info._rasterizerState)
	_deviceContext->RSSetState(info._rasterizerState->GetComPtr().Get());

	// PS
	if (info._pixelShader)
	_deviceContext->PSSetShader(info._pixelShader->GetComPtr().Get(), nullptr, 0);

	// OM
	if (info._blendState)
	_deviceContext->OMSetBlendState(
		info._blendState->GetComPtr().Get(), 
		info._blendState->GetBlendFactor(), 
		info._blendState->GetSampleMask());
}

void Pipeline::SetVertexBuffer(shared_ptr<VertexBuffer> buffer)
{
	uint32 stride = buffer->GetStride();
	uint32 offset = buffer->GetOffset();

	_deviceContext->IASetVertexBuffers(0, 1, buffer->GetComPtr().GetAddressOf(), &stride, &offset);
}

void Pipeline::SetIndexBuffer(shared_ptr<IndexBuffer> buffer)
{
	_deviceContext->IASetIndexBuffer(buffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
}

void Pipeline::SetTexture(uint32 slot, ShaderScope scope, shared_ptr<Texture> texture)
{
	if (scope == ShaderScope::SS_VertexShader)
	_deviceContext->VSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());

	if (scope == ShaderScope::SS_PixelShader)
	_deviceContext->PSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());
}

void Pipeline::SetSamplerState(uint32 slot, ShaderScope scope, shared_ptr<SamplerState> samplerState)
{
	if (scope == ShaderScope::SS_VertexShader)
	_deviceContext->VSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());

	if (scope == ShaderScope::SS_PixelShader)
	_deviceContext->PSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());

}

void Pipeline::Draw(uint32 vertexCount, uint32 startVertexLocation)
{
	_deviceContext->Draw(vertexCount, startVertexLocation);
}

void Pipeline::DrawIndexed(uint32 vertexCount, uint32 startIndexLocation, uint32 baseVertexLocation)
{
	_deviceContext->DrawIndexed(vertexCount, startIndexLocation, baseVertexLocation);
}

