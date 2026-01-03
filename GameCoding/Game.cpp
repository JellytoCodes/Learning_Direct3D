#include "pch.h"
#include "Game.h"

#include "Camera.h"
#include "Graphics.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Pipeline.h"

Game::Game(HWND hwnd) : _hwnd(hwnd)
{
	_graphics = make_shared<Graphics>(hwnd);
	_pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());
}

Game::~Game()
{

}

void Game::Init()
{
	_monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		_monster->GetOrAddTransform();
		_monster->AddComponent(make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext()));
	}

	_camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		_camera->GetOrAddTransform();
		_camera->AddComponent(make_shared<Camera>());
	}
}

void Game::Update()
{
	_monster->Update();

	// TEMP
	

	_camera->Update();
}

void Game::Render()
{
	_graphics->RenderBegin();

	_monster->GetmeshRenderer()->Render(_pipeline);

	_graphics->RenderEnd();
}