#pragma once
#include "Component.h"

enum class ProjectionType
{
	Perspective, // 원근 투영
	Orthographic, // 직교 투영
};

class Camera :  public Component
{
	using Super = Component;
public:
	Camera();
	virtual ~Camera();
	
	virtual void Update() override;

	void UpdateMatrix();

	void SetNear(float value) { _near = value; }
	void SetFar(float value) { _far = value; }
	void SetFOV(float value) { _fov = value; }
	void SetWidth(UINT value) { _width = value; }
	void SetHeight(UINT value) { _height = value; }

	Matrix& GetViewMatrix() { return _matView; }
	Matrix& GetProjectionMatrix() { return _matProjection; }

private:
	Matrix _matView = Matrix::Identity;
	Matrix _matProjection = Matrix::Identity;

	float _near		= 1.f;
	float _far		= 1000.f;
	float _fov		= XM_PI / 4.f;
	UINT _width		= 0;
	UINT _height	= 0;

public:
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};