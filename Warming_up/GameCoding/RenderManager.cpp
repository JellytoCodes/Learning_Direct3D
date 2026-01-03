#include "pch.h"
#include "RenderManager.h"

#include "Animator.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "Camera.h"
#include "GameObject.h"
#include "Graphics.h"
#include "IndexBuffer.h"
#include "MeshRenderer.h"
#include "SamplerState.h"
#include "Pipeline.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Transform.h"
#include "Mesh.h"

RenderManager::RenderManager(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	: _device(device), _deviceContext(deviceContext)
{
	_cameraBuffer = make_shared<ConstantBuffer<CameraData>>(device, deviceContext);
	_cameraBuffer->Create();

	_transformBuffer = make_shared<ConstantBuffer<TransformData>>(device, deviceContext);
	_transformBuffer->Create();

	_rasterizerState = make_shared<RasterizerState>(device);
	_rasterizerState->Create();

	_blendState = make_shared<BlendState>(device);
	_blendState->Create();

	_samplerState = make_shared<SamplerState>(device);
	_samplerState->Create();

	_animationBuffer = make_shared<ConstantBuffer<AnimationData>>(device, deviceContext);
	_animationBuffer->Create();
}

RenderManager::~RenderManager()
{
	
}

void RenderManager::Init()
{
	_pipeline = make_shared<Pipeline>(_deviceContext);
}

void RenderManager::Update(shared_ptr<Graphics> graphics)
{
	graphics->RenderBegin();


	PushCameraData();
	GatherRenderableObjects();
	RenderObjects();

	graphics->RenderEnd();
}

void RenderManager::PushCameraData()
{
	_cameraData.matView = Camera::S_MatView;
	_cameraData.matProjection = Camera::S_MatProjection;

	_cameraBuffer->CopyData(_cameraData);
}

void RenderManager::PushTransformData()
{
	_transformBuffer->CopyData(_transformData);
}

void RenderManager::PushAnimationData()
{
	_animationBuffer->CopyData(_animationData);
}

void RenderManager::GatherRenderableObjects()
{
	_renderObjects.clear();

	auto& gameObjects = SCENE->GetActiveScene()->GetGameObjects();
	for (const shared_ptr<GameObject>& gameObject : gameObjects)
	{
		shared_ptr<MeshRenderer> meshRenderer= gameObject->GetMeshRenderer();
		if (meshRenderer) _renderObjects.push_back(gameObject);
	}
}

void RenderManager::RenderObjects()
{
	for (const shared_ptr<GameObject>& gameObject : _renderObjects)
	{
		shared_ptr<MeshRenderer> meshRenderer= gameObject->GetMeshRenderer();
		if (meshRenderer == nullptr)  continue;

		shared_ptr<Transform> transform = gameObject->GetTransform();
		if (transform == nullptr) continue;

		// SRT
		_transformData.matWorld = transform->GetWorldMatrix();
		PushTransformData();

		shared_ptr<Animator> animator = gameObject->GetAnimator();
		if (animator)
		{
			const Keyframe& keyframe = animator->GetCurrentKeyframe();
			_animationData.spriteOffset = keyframe.offset;
			_animationData.spriteSize = keyframe.size;
			_animationData.textureSize = animator->GetCurrentAnimation()->GetTextureSize();
			_animationData.useAnimation = 1.f;
			PushAnimationData();

			_pipeline->SetConstantBuffer(2, ShaderScope::SS_VertexShader, _animationBuffer);
			_pipeline->SetTexture(0, ShaderScope::SS_PixelShader, animator->GetCurrentAnimation()->GetTexture());
		}
		else
		{
			_animationData.spriteOffset = Vec2(0.f, 0.f);
			_animationData.spriteSize = Vec2(0.f, 0.f);
			_animationData.textureSize = Vec2(0.f, 0.f);
			_animationData.useAnimation = 0.f;

			PushAnimationData();
			_pipeline->SetConstantBuffer(2, ShaderScope::SS_VertexShader, _animationBuffer);
			_pipeline->SetTexture(0, ShaderScope::SS_PixelShader, meshRenderer->GetTexture());
		}

		PipelineInfo info;
		info._inputLayout = meshRenderer->GetInputLayout();
		info._vertexShader = meshRenderer->GetVertexShader();
		info._pixelShader = meshRenderer->GetPixelShader();
		info._rasterizerState = _rasterizerState;
		info._blendState = _blendState;

		_pipeline->UpdatePipeline(info);
		
		_pipeline->SetVertexBuffer(meshRenderer->GetMesh()->GetVertexBuffer());
		_pipeline->SetIndexBuffer(meshRenderer->GetMesh()->GetIndexBuffer());
		
		_pipeline->SetConstantBuffer(0, ShaderScope::SS_VertexShader, _cameraBuffer);
		_pipeline->SetConstantBuffer(1, ShaderScope::SS_VertexShader, _transformBuffer);

		_pipeline->SetSamplerState(0, ShaderScope::SS_PixelShader, _samplerState);

		_pipeline->DrawIndexed(meshRenderer->GetMesh()->GetIndexBuffer()->GetCount(), 0, 0);
	}
}
