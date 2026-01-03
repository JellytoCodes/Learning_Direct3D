#pragma once
#include "Component.h"
#include "ConstantBuffer.h"
#include "Geometry.h"

class Camera;
struct CameraData;
class MonoBehaviour;
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

class MeshRenderer : public Component
{
	using Super = Component;
public :
	MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	virtual ~MeshRenderer();

	virtual void Start() override;
	virtual void Awake() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FixedUpdate() override;

	void Render(shared_ptr<Pipeline> pipeline);

private :
	ComPtr<ID3D11Device>						_device;
	ComPtr<ID3D11DeviceContext>					_deviceContext;

	// Mesh
	shared_ptr<Geometry<VertexTextureData>>		_geometry;
	shared_ptr<VertexBuffer>					_vertexBuffer;
	shared_ptr<IndexBuffer>						_indexBuffer;
	shared_ptr<InputLayout>						_inputLayout;

	// Material
	shared_ptr<VertexShader>					_vertexShader;

	shared_ptr<PixelShader>						_pixelShader;
	shared_ptr<Texture>							_texture1;
	shared_ptr<Texture>							_texture2;

	shared_ptr<RasterizerState>					_rasterizerState;
	shared_ptr<SamplerState>					_samplerState;
	shared_ptr<BlendState>						_blendState;

	// Camera
	CameraData									_cameraData;
	shared_ptr<ConstantBuffer<CameraData>>		_cameraBuffer;

	// Transform
	TransformData								_transformData;
	shared_ptr<ConstantBuffer<TransformData>>	_transformBuffer;
};

