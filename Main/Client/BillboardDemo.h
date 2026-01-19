#pragma once
#include "IExecute.h"
#include "MonoBehaviour.h"

class GameObject;

class BillboardDemo : public  IExecute
{
public :
	void Init() override;
	void Update() override;
	void Render() override;

private :
	shared_ptr<Shader>					_shader;

};

class BillboardTest : public MonoBehaviour
{
public :
	virtual void Update();
};