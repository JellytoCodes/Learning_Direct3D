#pragma once
#include "IExecute.h"

class GameObject;
class Texture;

class GlobalTestDemo : public  IExecute
{
public :
	void Init() override;
	void Update() override;
	void Render() override;
	
	shared_ptr<GameObject>		_obj;
	shared_ptr<GameObject>		_camera;

	Matrix _world		= Matrix::Identity;
	Vec3 _lightDir		= Vec3(0.f, -1.f, 0.f);
};
