#include "pch.h"
#include "AmbientDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "RenderManager.h"

void AmbientDemo::Init()
{
	RESOURCES->Init();

	_shader = make_shared<Shader>(L"Lighting_Ambient.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	_camera->GetTransform()->SetPosition(Vec3(0.f, 0.f, -5.f));

	// Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		
		_obj->GetMeshRenderer()->SetShader(_shader);
	}
	{
		
		auto _mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(_mesh);
	}
	{
		auto _texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
		_obj->GetMeshRenderer()->SetTexture(_texture);
	}

	// Object2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3(0.5f, 0.f, 2.f));
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		_obj2->GetMeshRenderer()->SetShader(_shader);
	}
	{
		
		auto _mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(_mesh);
	}
	{
		auto _texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
		_obj2->GetMeshRenderer()->SetTexture(_texture);
	}


	RENDER->Init(_shader);
}

void AmbientDemo::Update()
{
	_camera->Update();

	RENDER->Update();

	//
	Vec4 lightAmbient(0.f, 1.f, 0.f, 0.f);
	_shader->GetVector("LightAmbient")->SetFloatVector(reinterpret_cast<float*>(&lightAmbient));

	{
		Vec4 materialAmbient(1.f);
		_shader->GetVector("MaterialAmbient")->SetFloatVector(reinterpret_cast<float*>(&materialAmbient));
		_obj->Update();	
	}
	{
		Vec4 materialAmbient(1.f);
		_shader->GetVector("MaterialAmbient")->SetFloatVector(reinterpret_cast<float*>(&materialAmbient));
		_obj2->Update();	
	}
	
}

void AmbientDemo::Render()
{
	
}
