#pragma once
#include "Component.h"

enum class ProjectionType
{
	Perspective,	// 원근 투영
	Orthographic,	// 직교 투영
};

class Camera : public Component
{
	using Super = Component;
public :
	Camera();
	virtual ~Camera();

	virtual void Start() override;
	virtual void Awake() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FixedUpdate() override;

	void SetProjectionType(ProjectionType type) { _projectionType = type; }
	ProjectionType GetProjectionType() const { return _projectionType; }

	void UpdateMatrix();

	static Matrix S_MatView;
	static Matrix S_MatProjection;

private :
	ProjectionType _projectionType = ProjectionType::Orthographic;


};

