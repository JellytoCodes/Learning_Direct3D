#pragma once
#include "MonoBehaviour.h"

class CameraScript : public MonoBehaviour
{
public :
	void Start() override;
	void Update() override;

	float _speed = 10.f;

private :

};

