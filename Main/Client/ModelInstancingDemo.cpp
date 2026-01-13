#include "pch.h"
#include "ModelInstancingDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "ModelRenderer.h"
#include "Model.h"

void ModelInstancingDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"ModelInstancingDemo.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	_camera->GetTransform()->SetPosition(Vec3(0.f, 0.f, -5.f));

	// CustomData -> Memory
	shared_ptr<Model> m1 = make_shared<Model>();
	m1->ReadModel(L"Tower/Tower");
	m1->ReadMaterial(L"Tower/Tower");

	for (int i = 0 ; i < 1000 ; i++)
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(rand() % 100, 0 , rand() % 100));
		obj->GetOrAddTransform()->SetScale(Vec3(0.01f));
		obj->AddComponent(make_shared<ModelRenderer>(_shader));
		{
			obj->GetModelRenderer()->SetModel(m1);
		}
		_objs.push_back(obj);
	}

	RENDER->Init(_shader);
}

void ModelInstancingDemo::Update()
{
	_camera->Update();
	RENDER->Update();

	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.4f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(0.f);
		lightDesc.direction = Vec3(1.f, 0.f, 1.f);
		RENDER->PushLightData(lightDesc);
	}

	INSTANCING->Render(_objs);
}

void ModelInstancingDemo::Render()
{
	
}
