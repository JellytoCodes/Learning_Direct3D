#include "pch.h"
#include "TriangleDemo.h"

void TriangleDemo::Init()
{
	_shader = make_shared<Shader>(L"Triangle.fx");

	{
		_vertices.resize(3);

		_vertices[0].position = Vec3{-0.5f, 0.f, 0.f};
		_vertices[1].position = Vec3{0.f, 0.5f, 0.f};
		_vertices[2].position = Vec3{0.5f, 0.f, 0.f};
	}

	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->Create(_vertices);
}

void TriangleDemo::Update()
{
	
}

void TriangleDemo::Render()
{
	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);

	_shader->Draw(0, 1, 3);
}