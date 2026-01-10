#include "pch.h"
#include "MaterialDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "RenderManager.h"
#include "Material.h"

void MaterialDemo::Init()
{
	RESOURCES->Init();

	_shader = make_shared<Shader>(L"Lighting.fx");

	// Material
	{
		shared_ptr<Material> material = make_shared<Material>();
		{
			material->SetShader(_shader);
		}
		{
			auto _texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
			material->SetDiffuseMap(_texture);
		}

		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		desc.emissive = Vec4(1.f);

		RESOURCES->Add(L"Veigar", material);
	}

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
		auto _mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(_mesh);
	}
	{
		auto _material = RESOURCES->Get<Material>(L"Veigar");
		_obj->GetMeshRenderer()->SetMaterial(_material);
	}

	// Object2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3(0.5f, 0.f, 2.f));
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		auto _mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(_mesh);
	}
	{
		auto _material = RESOURCES->Get<Material>(L"Veigar")->Clone();
		//MaterialDesc& desc = _material->GetMaterialDesc();
		_obj2->GetMeshRenderer()->SetMaterial(_material);
	}


	RENDER->Init(_shader);
}

void MaterialDemo::Update()
{
	_camera->Update();

	RENDER->Update();

	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.5f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(1.f, 1.f, 1.f, 1.f);
		lightDesc.direction = Vec3(0.f, -1.f, 0.f);
		RENDER->PushLightData(lightDesc);
	}
	{
		_obj->Update();
	}
	{
		_obj2->Update();
	}
}

void MaterialDemo::Render()
{
	
}
