#pragma once
#include "Struct.h"

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
	uint32 _width = 0;
	uint32 _height = 0;

private :
	// Device & SwapChain
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
	ComPtr<IDXGISwapChain> _swapChain;

	// RTV
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	// Misc
	D3D11_VIEWPORT _viewport = {0};
	float _clearColor[4] = {0.f, 0.f, 0.f, 0.f};

	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

	void RenderBegin();
	void RenderEnd();

private :
	// Geometry
	vector<Vertex> _vertices;
	ComPtr<ID3D11Buffer> _vertexBuffer;

	vector<uint32> _indices;
	ComPtr<ID3D11Buffer> _indexBuffer;

	ComPtr<ID3D11InputLayout> _inputLayout;

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
