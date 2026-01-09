#include "pch.h"
#include "DepthStencilDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "RenderManager.h"

void DepthStencilDemo::Init()
{
	RESOURCES->Init();

	auto _shader = make_shared<Shader>(L"GlobalTest.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	_camera->GetTransform()->SetPosition(Vec3(0.f, 0.f, -10.f));

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
	//


	RENDER->Init(_shader);
}

void DepthStencilDemo::Update()
{
	_camera->Update();

	RENDER->Update();
	_obj->Update();_obj2->Update();
}

void DepthStencilDemo::Render()
{
	
}
