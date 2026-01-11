#pragma once
#include "IExecute.h"

class ImGUIDemo : public IExecute
{
public :
	void Init() override;
	void Update() override;
	void Render() override;

	void Test();

private :
	shared_ptr<GameObject>		_obj;
	shared_ptr<GameObject>		_camera;
	shared_ptr<Shader>			_shader;

	bool show_demo_window = true;
	bool show_another_window = false;
	Vec4 clear_color = Vec4(0.f);
};

