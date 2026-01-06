#include "pch.h"
#include "Main.h"

#include "TriangleDemo.h"			// Demo 1
#include "QuadDemo.h"				// Demo 2
#include "ConstantBufferDemo.h"		// Demo 3
#include "CameraDemo.h"				// Demo 4
#include "TextureDemo.h"			// Demo 5
#include "SamplerDemo.h"			// Demo 6
#include "HeightMapDemo.h"			// Demo 7
#include "NormalDemo.h"				// Demo 8
#include "MeshDemo.h"				// Demo 9

#include "Engine/Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameDesc desc;
	desc.appName = L"GameCoding";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 800;
	desc.height = 600;
	desc.clearColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	desc.app = make_shared<MeshDemo>();

	GAME->Run(desc);

	return 0;
}