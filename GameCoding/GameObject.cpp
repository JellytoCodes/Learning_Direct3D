#include "pch.h"
#include "GameObject.h"
#include "GeometryHelper.h"
#include "Texture.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "BlendState.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "Pipeline.h"
#include "VertexData.h"
#include "Shader.h"
#include "Transform.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	: _device(device), _deviceContext(deviceContext)
{
	_transform = make_shared<Transform>();
	_parent = make_shared<Transform>();
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(_geometry);

	_vertexBuffer = make_shared<VertexBuffer>(device);
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>(device);
	_indexBuffer->Create(_geometry->GetIndices());

	_vertexShader = make_shared<VertexShader>(device);
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	_inputLayout = make_shared<InputLayout>(device);
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());

	_pixelShader = make_shared<PixelShader>(device);
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	_rasterizerState = make_shared<RasterizerState>(device);
	_rasterizerState->Create();

	_blendState = make_shared<BlendState>(device);
	_blendState->Create();

	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(device, deviceContext);
	_constantBuffer->Create();

	_texture1 = make_shared<Texture>(device);
	_texture1->Create(L"Test1.png");

	_texture2 = make_shared<Texture>(device);
	_texture2->Create(L"Test2.png");	

	_samplerState = make_shared<SamplerState>(device);
	_samplerState->Create();

	_parent->AddChild(_transform);
	_transform->SetParent(_parent);
}

GameObject::~GameObject()
{

}

void GameObject::Update()
{
	Vec3 pos = _parent->GetPosition();
	pos.x += 0.001f;
	_parent->SetPosition(pos);

	_transformData.matWorld = _transform->GetWorldMatrix();

	_constantBuffer->CopyData(_transformData);
}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
{
	PipelineInfo info;
	info._inputLayout = _inputLayout;
	info._vertexShader = _vertexShader;
	info._pixelShader = _pixelShader;
	info._rasterizerState = _rasterizerState;
	info._blendState = _blendState;

	pipeline->UpdatePipeline(info);
	
	pipeline->SetVertexBuffer(_vertexBuffer);
	pipeline->SetIndexBuffer(_indexBuffer);
	
	pipeline->SetConstantBuffer(0, ShaderScope::SS_VertexShader, _constantBuffer);

	pipeline->SetTexture(0, ShaderScope::SS_PixelShader, _texture1);
	pipeline->SetTexture(1, ShaderScope::SS_PixelShader, _texture2);

	pipeline->SetSamplerState(0, ShaderScope::SS_PixelShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
}
