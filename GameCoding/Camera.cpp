#include "pch.h"
#include "Camera.h"

#include "Transform.h"

Matrix Camera::S_MatView		= Matrix::Identity;
Matrix Camera::S_MatProjection	= Matrix::Identity;

Camera::Camera() : Super(ComponentType::Camera)
{

}

Camera::~Camera()
{

}

void Camera::Start()
{
	
}

void Camera::Awake()
{
	
}

void Camera::Update()
{
	UpdateMatrix();
}

void Camera::LateUpdate()
{
	
}

void Camera::FixedUpdate()
{
	
}

void Camera::UpdateMatrix()
{
	Vec3 eyePosition	= GetTransform()->GetPosition();
	Vec3 focusPosition	= eyePosition + GetTransform()->GetLook();
	Vec3 upDirection	= GetTransform()->GetUp();

	S_MatView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
	// == S_MatView = GetTransform()->GetWorldMatrix().Invert();

	if (_projectionType == ProjectionType::Perspective)	S_MatProjection = ::XMMatrixPerspectiveFovLH(XM_PI / 4.f, 800.f / 600.f, 1.f, 100.f);
	else												S_MatProjection = ::XMMatrixOrthographicLH(3, 3, 0.f, 1.f);
}
