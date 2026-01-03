#pragma once

class Transform;
class GameObject;

enum class ComponentType : uint8
{
	Transform,
	MeshRenderer,
	Camera,
	Animator,

	Script,

	End,
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(ComponentType::End) - 1
};

class Component
{
public :
	Component(ComponentType type);
	virtual ~Component();

	virtual void Awake() abstract;
	virtual void Start() abstract;

	virtual void Update() abstract;
	virtual void LateUpdate() abstract;
	virtual void FixedUpdate() abstract;

	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();

	ComponentType GetType() const { return _type; }

protected :
	ComponentType _type;
	weak_ptr<GameObject> _gameObject;

private :
	friend class GameObject;
	void SetGameObject(shared_ptr<GameObject> gameObject) { _gameObject = gameObject; }
};

