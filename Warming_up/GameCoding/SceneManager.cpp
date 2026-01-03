#include "pch.h"
#include "SceneManager.h"

#include "Animator.h"
#include "Graphics.h"
#include "GameObject.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Scene.h"
#include "Mesh.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "CameraMove.h"

SceneManager::SceneManager(shared_ptr<Graphics> graphics) : _graphics(graphics)
{

}

void SceneManager::Init()
{
	if (_activeScene == nullptr) return;

	_activeScene->Awake();
	_activeScene->Start();
}

void SceneManager::Update()
{
	if (_activeScene == nullptr) return;

	_activeScene->Update();
	_activeScene->LateUpdate();

	_activeScene->FixedUpdate();
}

void SceneManager::LoadScene(wstring sceneName)
{
	_activeScene = LoadTestScene();
	Init();
}

void SceneManager::Render()
{

}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
	shared_ptr<Scene> scene = make_shared<Scene>();

	//Camera
	{
		shared_ptr<GameObject> _camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		{
			_camera->GetOrAddTransform();
			_camera->AddComponent(make_shared<Camera>());
			scene->AddGameObject(_camera);
		}
		{
			_camera->AddComponent(make_shared<CameraMove>());
		}
	}


	// Monster
	{
		shared_ptr<GameObject>	_monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		{
			_monster->GetOrAddTransform();
			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
			_monster->AddComponent(meshRenderer);

			// TODO : Material
			auto material = RESOURCES->Get<Material>(L"Default");
			meshRenderer->SetMaterial(material);

			auto mesh = RESOURCES->Get<Mesh>(L"Rectangle");
			meshRenderer->SetMesh(mesh);
		}
		{
			auto animator = make_shared<Animator>();
			_monster->AddComponent(animator);
			auto anim = RESOURCES->Get<Animation>(L"SnakeAnim");
			animator->SetAnimation(anim);
		}
		scene->AddGameObject(_monster);	
	}

	{
		shared_ptr<GameObject>	_monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		_monster->GetOrAddTransform()->SetPosition(Vec3{1.f, 1.f, 0.f});
		{
			_monster->GetOrAddTransform();
			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
			_monster->AddComponent(meshRenderer);

			// TODO : Material
			auto material = RESOURCES->Get<Material>(L"Default");
			meshRenderer->SetMaterial(material);

			auto mesh = RESOURCES->Get<Mesh>(L"Rectangle");
			meshRenderer->SetMesh(mesh);
		}
		{
			auto animator = make_shared<Animator>();
			_monster->AddComponent(animator);
			auto anim = RESOURCES->Get<Animation>(L"SnakeAnim");
			animator->SetAnimation(anim);
		}
		scene->AddGameObject(_monster);	
	}
	

	return scene;
}
