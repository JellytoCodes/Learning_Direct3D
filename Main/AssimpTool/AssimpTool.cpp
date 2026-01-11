#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	{
		shared_ptr<Converter> converter = make_shared<Converter>();


		// 파일 포맷은 여러 형식을 지원하기 때문에 파일 포맷을 명시해야한다.
		// FBX -> Memory
		converter->ReadAssetFile(L"shunguang/Avatar_Female_Size02_ZhenzhenDawnlight_UI.fbx");

		// 여기서 파일 포맷을 명시하지 않은 이유는 함수 내에서 전용으로 명시했기 때문이다.
		// Memory -> CustomData (File)
		converter->ExportMaterialData(L"shunguang/shunguang");
		converter->ExportModelData(L"shunguang/shunguang");

		// CustomData(File) -> Memory
	}

		{
		shared_ptr<Converter> converter = make_shared<Converter>();


		// 파일 포맷은 여러 형식을 지원하기 때문에 파일 포맷을 명시해야한다.
		// FBX -> Memory
		converter->ReadAssetFile(L"Tank/Tank.fbx");

		// 여기서 파일 포맷을 명시하지 않은 이유는 함수 내에서 전용으로 명시했기 때문이다.
		// Memory -> CustomData (File)
		converter->ExportMaterialData(L"Tank/Tank");
		converter->ExportModelData(L"Tank/Tank");

		// CustomData(File) -> Memory
	}
}

void AssimpTool::Update()
{
	
}

void AssimpTool::Render()
{
	
}
