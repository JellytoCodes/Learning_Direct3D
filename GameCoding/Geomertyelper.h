#pragma once

struct VertexColorData;
struct VertexTextureData;

class Geomertyelper
{
public :
	static void CrateRectangle(shared_ptr<Geometry<VertexColorData>> geometry, Color color);
	static void CrateRectangle(shared_ptr<Geometry<VertexTextureData>> geometry);
};

