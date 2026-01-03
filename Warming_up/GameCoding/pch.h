#pragma once

#define CHECK(p) assert(SUCCEEDED(p))

#include "Types.h"
#include "Values.h"
#include "Struct.h"

// STL
#include <vector>
#include <array>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

// WIN
#include <windows.h>
#include <assert.h>
#include <memory>

// Utils
#include "tinyxml2.h"
using namespace tinyxml2;

// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
using namespace DirectX;
using namespace Microsoft::WRL;

// Engine
#include "Game.h"
#define			GAME		GGame
#define			SCENE		GAME->GetSceneManager()
#define			TIME		GAME->GetTimeManager()
#define			INPUT		GAME->GetInputManager()
#define			RESOURCES	GAME->GetResourceManager()
#define			RENDER		GAME->GetRenderManager()

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex\\DirectXTex.lib")
#endif