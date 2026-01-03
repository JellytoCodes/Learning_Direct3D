#pragma once
class Graphics;
class Scene;

class SceneManager
{
public :
	SceneManager(shared_ptr<Graphics> graphics);

	void Init();
	void Update();
	void LoadScene(wstring sceneName);

	void Render();

	shared_ptr<Scene> GetActiveScene() { return _activeScene; }
	shared_ptr<Scene> LoadTestScene();

private :
	shared_ptr<Scene> _activeScene;

	shared_ptr<Graphics> _graphics;
};

