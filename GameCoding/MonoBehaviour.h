#pragma once
#include "Component.h"
class MonoBehaviour : public Component
{
	using Super = Component;

public :
	MonoBehaviour();
	~MonoBehaviour();

	void Start() override;
	void Awake() override;
	void Update() override;
	void LateUpdate() override;
	void FixedUpdate() override;
};

