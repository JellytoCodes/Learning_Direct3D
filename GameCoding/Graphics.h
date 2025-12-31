#pragma once

class Graphics
{
public :
	Graphics(HWND hwnd);
	~Graphics();

	void RenderBegin();
	void RenderEnd();

	ComPtr<ID3D11Device> GetDevice() const { return _device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() const { return _deviceContext; }

private :
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
	ComPtr<IDXGISwapChain> _swapChain;

	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	D3D11_VIEWPORT _viewport = {0};
	float _clearColor[4] = {0.f, 0.f, 0.f, 0.f};

	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;
};

