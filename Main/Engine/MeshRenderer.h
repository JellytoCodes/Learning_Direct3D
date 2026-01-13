#pragma once
#include "Component.h"

class Mesh;
class Shader;
class Material;
class InstancingBuffer;

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer();
	virtual ~MeshRenderer();

	virtual void Update() override;

	void SetMesh(shared_ptr<Mesh> mesh)					{ _mesh = mesh; }
	void SetMaterial(shared_ptr<Material> material)		{ _material = material; }
	void SetPass(uint8 pass) { _pass = pass; }

	void RenderInstancing(shared_ptr<InstancingBuffer>& buffer);
	InstanceID GetInstanceID();

	// Legacy
	void SetShader(shared_ptr<Shader> shader) { }
	void SetTexture(shared_ptr<Texture> texture) { }

private:
	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;
	uint8 _pass = 0;
};

