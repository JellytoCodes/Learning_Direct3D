#pragma once
#include "pch.h"

class Game
{
public :
	Game();
	~Game();

public :
	void Init(HWND hwnd);
	void Update();
	void Render();

private :
	HWND _hwnd;

	shared_ptr<Graphics> _graphics;

private :
	// Geometry
	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	vector<uint32> _indices;
	shared_ptr<IndexBuffer> _indexBuffer;

	shared_ptr<InputLayout> _inputLayout;

	void CreateGeometry();
	void CreateInputLayout();

	// VS
	ComPtr<ID3D11VertexShader> _vertexShader;
	ComPtr<ID3DBlob> _vsBlob;

	void CreateVS();

	// RS
	ComPtr<ID3D11RasterizerState> _rasterizerState;

	void CreateRasterizerState();

	// PS
	ComPtr<ID3D11PixelShader> _pixelShader;
	ComPtr<ID3DBlob> _psBlob;

	void CreatePS();

	// SRV (Shader Resource View)
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView2;

	ComPtr<ID3D11SamplerState> _samplerState;
	ComPtr<ID3D11BlendState> _blendState;

	void CreateSRV();
	void CreateSamplerState();
	void CreateBlendState();

	// Helper
	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);

private :
	// SRT 
	TransformData _transformData;
	ComPtr<ID3D11Buffer> _constantBuffer;

	Vec3 _localPosition = {0.f, 0.f, 0.f};
	Vec3 _localRotation = {0.f, 0.f, 0.f};
	Vec3 _localScale = {1.f, 1.f, 1.f};

	void CreateConstantBuffer();
};
