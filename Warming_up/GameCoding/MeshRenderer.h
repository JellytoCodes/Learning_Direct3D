#pragma once
#include "Component.h"
#include "Material.h"
#include "Shader.h"

class Shader;
class Material;
class Mesh;
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

	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetShader(shared_ptr<Shader> shader) { _material->SetShader(shader); }
	void SetMaterial(shared_ptr<Material> material) { _material = material; }
	void SetTexture(shared_ptr<Texture> texture) { _material->SetTexture(texture); }

	auto GetMesh() { return _mesh; }
	auto GetMaterial() { return _material; }
	auto GetInputLayout() { return GetMaterial()->GetShader()->GetInputLayout(); }
	auto GetVertexShader() { return GetMaterial()->GetShader()->GetVertexShader(); }
	auto GetPixelShader() { return GetMaterial()->GetShader()->GetPixelShader(); }
	auto GetTexture() { return GetMaterial()->GetTexture(); }

private :
	ComPtr<ID3D11Device>				_device;
	ComPtr<ID3D11DeviceContext>			_deviceContext;

	friend class RenderManager;

	shared_ptr<Mesh>					_mesh;
	shared_ptr<Material>				_material;
};

