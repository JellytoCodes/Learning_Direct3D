#pragma once
#include "ResourceBase.h"

class PixelShader;
class VertexShader;
class InputLayout;

class Shader : public ResourceBase
{
	using Super = ResourceBase;

public :
	Shader();
	virtual ~Shader();

	auto GetInputLayout() { return _inputLayout; }
	auto GetVertexShader() { return _vertexShader; }
	auto GetPixelShader() { return _pixelShader; }

private :
	friend class ResourceManager;

	shared_ptr<InputLayout>					_inputLayout;
	shared_ptr<VertexShader>				_vertexShader;
	shared_ptr<PixelShader>					_pixelShader;
};

