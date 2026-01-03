#pragma once

struct VertexColorData;
struct VertexTextureData;

class GeometryHelper
{
public :
	static void CreateRectangle(shared_ptr<Geometry<VertexColorData>> geometry, Color color);
	static void CreateRectangle(shared_ptr<Geometry<VertexTextureData>> geometry);
};

