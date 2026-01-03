#include "pch.h"
#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GeometryHelper.h"

Mesh::Mesh(ComPtr<ID3D11Device> device) : Super(ResourceType::Mesh), _device(device)
{
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(_geometry);

	_vertexBuffer = make_shared<VertexBuffer>(device);
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>(device);
	_indexBuffer->Create(_geometry->GetIndices());
}

Mesh::~Mesh()
{

}

void Mesh::CreateDefaultRectangle()
{

}
