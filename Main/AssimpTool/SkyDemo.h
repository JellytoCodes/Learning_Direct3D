#pragma once
#include "IExecute.h"

class SkyDemo : public IExecute
{
public :
	void Init() override;
	void Update() override;
	void Render() override;


private :
	shared_ptr<GameObject>		_obj;
	shared_ptr<GameObject>		_camera;
	shared_ptr<Shader>			_shader;
};

