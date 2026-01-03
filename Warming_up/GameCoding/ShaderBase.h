#pragma once

enum class ShaderScope : uint32
{
	SS_None = 0,
	SS_VertexShader = (1 << 0),
	SS_PixelShader = (1 << 1),
};

class ShaderBase
{
public :
	ShaderBase(ComPtr<ID3D11Device> device);
	virtual ~ShaderBase();

	virtual void Create(const wstring& path, const string& name, const string& version) abstract;

	ComPtr<ID3DBlob> GetBlob() { return _blob;}

protected :
	void LoadShaderFromFile(const wstring& path, const string& name, const string& version);

	wstring _path;
	string _name;

	ComPtr<ID3D11Device> _device;
	ComPtr<ID3DBlob> _blob;
};

class VertexShader : public ShaderBase
{
	using Super = ShaderBase;

public :
	VertexShader(ComPtr<ID3D11Device> device);
	~VertexShader();

	void Create(const wstring& path, const string& name, const string& version) override;

	ComPtr<ID3D11VertexShader> GetComPtr() const { return _vertexShader; }
protected :

	ComPtr<ID3D11VertexShader> _vertexShader;
};

class PixelShader : public ShaderBase
{
	using Super = ShaderBase;

public :
	PixelShader(ComPtr<ID3D11Device> device);
	~PixelShader();

	void Create(const wstring& path, const string& name, const string& version) override;

	ComPtr<ID3D11PixelShader> GetComPtr() const { return _pixelShader; }
protected :

	ComPtr<ID3D11PixelShader> _pixelShader;
};