#pragma once
#include "Component.h"
class Terrain : public Component
{
	using Super = Component;

public :
	Terrain();
	~Terrain();

	void Create(float sizeX, float sizeZ, shared_ptr<Material> material);

	float GetSizeX() { return _sizeX; }
	float GetSizeZ() { return _sizeZ; }

	bool Pick(float screenX, float screenY, Vec3& pickPos, float& distance);

private :
	shared_ptr<Mesh> _mesh;
	float _sizeX = 0;
	float _sizeZ = 0;
};

