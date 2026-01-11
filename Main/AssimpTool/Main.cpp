#include "pch.h"
#include "Main.h"

#include "ImGUIDemo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameDesc desc;
	desc.appName		= L"GameCoding";
	desc.hInstance		= hInstance;
	desc.vsync			= false;
	desc.hWnd			= nullptr;
	desc.width			= 1200;
	desc.height			= 800;
	desc.clearColor		= Color(0.f, 0.f, 0.f, 0.f);
	desc.app			= make_shared<ImGUIDemo>();
	//desc.app			= make_shared<AssimpTool>();

	GAME->Run(desc);

	return 0;
}
