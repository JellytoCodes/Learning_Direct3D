#pragma once
#include "InstancingBuffer.h"
#include "Types.h"

class GameObject;

class InstancingManager
{
	DECLARE_SINGLE(InstancingManager);

public :
	void Render(vector<shared_ptr<GameObject>>& gameObjects);
	void ClearData();

private :
	void RenderMeshRenderer(vector<shared_ptr<GameObject>>& gameObjects);
	void RenderModelRenderer(vector<shared_ptr<GameObject>>& gameObjects);
	void RenderAnimRenderer(vector<shared_ptr<GameObject>>& gameObjects);

	void AddData(InstanceID instanceID, InstancingData& data);


	map<InstanceID, shared_ptr<InstancingBuffer>> _buffers;
};

