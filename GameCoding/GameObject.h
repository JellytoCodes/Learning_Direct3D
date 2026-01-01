#pragma once
#include "ConstantBuffer.h"
#include "Geometry.h"

class Transform;
struct VertexColorData;
class Pipeline;
struct VertexTextureData;
class VertexBuffer;
class IndexBuffer;
class InputLayout;
class VertexShader;
class PixelShader;
class Texture;
class RasterizerState;
class SamplerState;
class BlendState;

class GameObject
{

public :
	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~GameObject();

	void Update();
	void Render(shared_ptr<Pipeline> pipeline);

private :
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;

	shared_ptr<Geometry<VertexTextureData>> _geometry;
	//shared_ptr<Geometry<VertexColorData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;

	shared_ptr<VertexShader> _vertexShader;

	shared_ptr<PixelShader> _pixelShader;
	shared_ptr<Texture> _texture1;
	shared_ptr<Texture> _texture2;

	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<SamplerState> _samplerState;
	shared_ptr<BlendState> _blendState;

	
	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;

	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _parent;
};

