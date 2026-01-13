#include "pch.h"
#include "InstancingManager.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"
#include "ModelAnimator.h"

void InstancingManager::Render(vector<shared_ptr<GameObject>>& gameObjects)
{
	ClearData();

	RenderMeshRenderer(gameObjects);
	RenderModelRenderer(gameObjects);
	RenderAnimRenderer(gameObjects);
}

void InstancingManager::ClearData()
{
	for (auto& pair : _buffers)
	{
		shared_ptr<InstancingBuffer>& buffer = pair.second;
		buffer->ClearData();
	}
}

void InstancingManager::RenderMeshRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->GetMeshRenderer() == nullptr) continue;

		const InstanceID instanceID = gameObject->GetMeshRenderer()->GetInstanceID();
		cache[instanceID].push_back(gameObject);
	}

	for (auto& pair : cache)
	{
		const vector<shared_ptr<GameObject>>& vec = pair.second;
		{
			const InstanceID id = pair.first;

			for (int32 i = 0 ; i < vec.size() ; i++)
			{
				const shared_ptr<GameObject>& gameObject = vec[i];
				InstancingData data;
				data.world = gameObject->GetTransform()->GetWorldMatrix();

				AddData(id, data);
			}

			// 그려주기
			shared_ptr<InstancingBuffer>& buffer = _buffers[id];
			vec[0]->GetMeshRenderer()->RenderInstancing(buffer);
		}
		
	}
}

void InstancingManager::RenderModelRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->GetModelRenderer() == nullptr) continue;

		const InstanceID instanceID = gameObject->GetModelRenderer()->GetInstanceID();
		cache[instanceID].push_back(gameObject);
	}

	for (auto& pair : cache)
	{
		const vector<shared_ptr<GameObject>>& vec = pair.second;
		{
			const InstanceID id = pair.first;

			for (int32 i = 0 ; i < vec.size() ; i++)
			{
				const shared_ptr<GameObject>& gameObject = vec[i];
				InstancingData data;
				data.world = gameObject->GetTransform()->GetWorldMatrix();

				AddData(id, data);
			}

			shared_ptr<InstancingBuffer>& buffer = _buffers[id];
			vec[0]->GetModelRenderer()->RenderInstancing(buffer);
		}
	}
}

void InstancingManager::RenderAnimRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->GetAnimator() == nullptr) continue;

		const InstanceID instanceID = gameObject->GetAnimator()->GetInstanceID();
		cache[instanceID].push_back(gameObject);
	}

	for (auto& pair : cache)
	{
		shared_ptr<InstancedTweenDesc> tweenDesc = make_shared<InstancedTweenDesc>();

		const vector<shared_ptr<GameObject>>& vec = pair.second;
		{
			const InstanceID id = pair.first;

			for (int32 i = 0 ; i < vec.size() ; i++)
			{
				const shared_ptr<GameObject>& gameObject = vec[i];
				InstancingData data;
				data.world = gameObject->GetTransform()->GetWorldMatrix();

				AddData(id, data);

				// INSTANCING
				gameObject->GetAnimator()->UpdateTweenData();
				tweenDesc->tweens[i] = gameObject->GetAnimator()->GetTweenDesc();
			}

			RENDER->PushTweenData(*tweenDesc.get());

			shared_ptr<InstancingBuffer>& buffer = _buffers[id];
			vec[0]->GetAnimator()->RenderInstancing(buffer);
		}
	}
}

void InstancingManager::AddData(InstanceID instanceID, InstancingData& data)
{
	if (_buffers.find(instanceID) == _buffers.end()) _buffers[instanceID] = make_shared<InstancingBuffer>();

	_buffers[instanceID]->AddData(data);
}
