#include "pch.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Animation.h"
#include "Shader.h"
#include "ShaderBase.h"
#include "InputLayout.h"

ResourceManager::ResourceManager(ComPtr<ID3D11Device> device) : _device(device)
{

}

void ResourceManager::Init()
{
	// 순서 중요
	CreateDefaultTexture();
	CreateDefaultMesh();
	CreateDefaultShader();
	CreateDefaultMaterial();
	CreateDefaultAnimation();
}

void ResourceManager::CreateDefaultTexture()
{
	{
		auto texture = make_shared<Texture>(_device);
		texture->SetName(L"Skeleton");
		texture->Create(L"Skeleton.png");
		Add(texture->GetName(), texture);	
	}
	{
		auto texture = make_shared<Texture>(_device);
		texture->SetName(L"Snake");
		texture->Create(L"Snake.bmp");
		Add(texture->GetName(), texture);
	}
}

void ResourceManager::CreateDefaultMesh()
{
	shared_ptr<Mesh> mesh = make_shared<Mesh>(_device);
	mesh->SetName(L"Rectangle");
	mesh->CreateDefaultRectangle();
	Add(mesh->GetName(), mesh);
}

void ResourceManager::CreateDefaultShader()
{
	auto _vertexShader = make_shared<VertexShader>(_device);
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	auto _inputLayout = make_shared<InputLayout>(_device);
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());

	auto _pixelShader = make_shared<PixelShader>(_device);
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	// Shader
	shared_ptr<Shader> shader = make_shared<Shader>();
	shader->SetName(L"Default");
	shader->_vertexShader = _vertexShader;
	shader->_inputLayout = _inputLayout;
	shader->_pixelShader = _pixelShader;
	Add(shader->GetName(), shader);
}

void ResourceManager::CreateDefaultMaterial()
{
	shared_ptr<Material> material = make_shared<Material>();
	material->SetName(L"Default");
	material->SetShader(Get<Shader>(L"Default"));
	material->SetTexture(Get<Texture>(L"Skeleton"));
	Add(material->GetName(), material);
}

void ResourceManager::CreateDefaultAnimation()
{
	shared_ptr<Animation> animation = make_shared<Animation>();
	animation->SetTexture(Get<Texture>(L"Snake"));

	/*
	animation->SetName(L"SnakeAnim");
	animation->SetLoop(true);

	animation->AddKeyframe(Keyframe{Vec2 {0.f, 0.f,}, Vec2{100.f, 100.f}, 0.1f});
	animation->AddKeyframe(Keyframe{Vec2 {100.f, 0.f,}, Vec2{100.f, 100.f}, 0.1f});
	animation->AddKeyframe(Keyframe{Vec2 {200.f, 0.f,}, Vec2{100.f, 100.f}, 0.1f});
	animation->AddKeyframe(Keyframe{Vec2 {300.f, 0.f,}, Vec2{100.f, 100.f}, 0.1f});

	animation->Save(L"TestAnim.xml");*/

	// XML 데이터를 Load하여 Animation 출력
	animation->Load(L"TestAnim.xml");

	Add(animation->GetName(), animation);
}