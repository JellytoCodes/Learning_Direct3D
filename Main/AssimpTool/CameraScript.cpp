#include "pch.h"
#include "CameraScript.h"

void CameraScript::Start()
{
	
}

void CameraScript::Update()
{
	float dt = TIME->GetDeltaTime();

	Vec3 pos = GetTransform()->GetPosition();

	if (INPUT->GetButton(KEY_TYPE::W))	pos += GetTransform()->GetLook() * _speed * dt;
	if (INPUT->GetButton(KEY_TYPE::S))	pos -= GetTransform()->GetLook() * _speed * dt;
	if (INPUT->GetButton(KEY_TYPE::A))	pos += GetTransform()->GetRight() * _speed * dt;
	if (INPUT->GetButton(KEY_TYPE::D))	pos -= GetTransform()->GetRight() * _speed * dt;

	GetTransform()->SetPosition(pos);

	//

	Vec3 rot = GetTransform()->GetLocalRotation();

	if (INPUT->GetButton(KEY_TYPE::Q))	rot.x += dt * 0.5f;
	if (INPUT->GetButton(KEY_TYPE::E))	rot.x -= dt * 0.5f;
	if (INPUT->GetButton(KEY_TYPE::Z))	rot.y += dt * 0.5f;
	if (INPUT->GetButton(KEY_TYPE::C))	rot.y -= dt * 0.5f;

	GetTransform()->SetLocalRotation(rot);
	
}
