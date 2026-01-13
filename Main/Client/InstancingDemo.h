#pragma once
#include "IExecute.h"

class GameObject;

class InstancingDemo : public  IExecute
{
public :
	void Init() override;
	void Update() override;
	void Render() override;

private :
	vector<shared_ptr<GameObject>>		_objs;
	shared_ptr<GameObject>				_camera;
	shared_ptr<Shader>					_shader;

	// INSTANCING
	shared_ptr<Mesh>	_mesh;
	shared_ptr<Material> _material;

	vector<Matrix> _worlds;
	shared_ptr<VertexBuffer> _instanceBuffer;
};