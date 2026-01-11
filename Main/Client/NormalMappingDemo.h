#pragma once
#include "IExecute.h"

class GameObject;

class NormalMappingDemo : public  IExecute
{
public :
	void Init() override;
	void Update() override;
	void Render() override;
	
	shared_ptr<GameObject>		_obj;
	shared_ptr<GameObject>		_obj2;
	shared_ptr<GameObject>		_camera;
	shared_ptr<Shader>			_shader;

	Matrix _world		= Matrix::Identity;
	Vec3 _lightDir		= Vec3(0.f, -1.f, 0.f);
};
