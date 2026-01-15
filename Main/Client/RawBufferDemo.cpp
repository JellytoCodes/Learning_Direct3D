#include "pch.h"
#include "RawBufferDemo.h"
#include "RawBuffer.h"

void RawBufferDemo::Init()
{
	_shader = make_shared<Shader>(L"RawBufferDemo.fx");

	// 하나의 쓰레드 그룹 내에서, 운영할 쓰레드 개수
	uint32 count = 10 * 8 * 3;

	shared_ptr<RawBuffer> rawBuffer = make_shared<RawBuffer>(nullptr, 0, sizeof(Output) * count);

	_shader->GetUAV("Output")->SetUnorderedAccessView(rawBuffer->GetUAV().Get());

	// x, y, z 쓰레드 그룹
	_shader->Dispatch(0, 0, 1, 1, 1);

	vector<Output> outputs(count);
	rawBuffer->CopyFromOutput(outputs.data());

}

void RawBufferDemo::Update()
{
	
}

void RawBufferDemo::Render()
{

}