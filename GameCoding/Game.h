#pragma once

class GameObject;
class Pipeline;
class SamplerState;
class BlendState;
class RasterizerState;
class Texture;
class PixelShader;
class VertexShader;
class InputLayout;
class IndexBuffer;
class VertexBuffer;
struct VertexTextureData;
class Graphics;

class Game
{
public :
	Game(HWND hwnd);
	~Game();

	void Init();
	void Update();
	void Render();

private :
	HWND _hwnd;

	shared_ptr<Graphics> _graphics;
	shared_ptr<Pipeline> _pipeline;
	shared_ptr<GameObject> _monster;
	shared_ptr<GameObject> _camera;

};
