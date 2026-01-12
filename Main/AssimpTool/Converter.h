#pragma once
#include "AsTypes.h"

class Converter
{
public :
	Converter();
	~Converter();

	void							ReadAssetFile(wstring file);
	void							ExportModelData(wstring savePath);
	void							ExportMaterialData(wstring savePath);
	void							ExportAnimationData(wstring savePath, uint32 index = 0);

private :
	void							ReadModelData(aiNode* node, int32 index, int32 parent);
	void							ReadMeshData(aiNode* node, int32 bone);
	void							ReadSkinData();
	void							WriteModelFile(wstring finalPath);

	void							ReadMaterialData();
	void							WriteMaterialData(wstring finalPath);
	string							WriteTexture(string saveFolder, string file);

	shared_ptr<asAnimation>			ReadAnimationData(aiAnimation* srcAnimation);
	shared_ptr<asAnimationNode>		ParseAnimationNode(shared_ptr<asAnimation> animation, aiNodeAnim* srcNode);
	void							ReadKeyframeData(shared_ptr<asAnimation> animation, aiNode* srcNode, map<string, shared_ptr<asAnimationNode>>& cache);
	void							WriteAnimationData(shared_ptr<asAnimation> animation, wstring finalPath);

	uint32							GetBoneIndex(const string& name);

	// Importer는 aiScene을 소유하고 aiScene은 하위 객체들을 소유한다.
	// 이에 따라 Importer가 하위 객체들의 생명주기를 관리하기 때문에 스마트 포인터를 사용하게 되면 이중 해제 오류가 발생한다.
	shared_ptr<Assimp::Importer> _importer;
	const aiScene* _scene;

	wstring _assetPath		= L"../Resources/Assets/";
	wstring _modelPath		= L"../Resources/Models/";
	wstring _texturePath	= L"../Resources/Textures/";

	vector<shared_ptr<asBone>>		_bones;
	vector<shared_ptr<asMesh>>		_meshes;
	vector<shared_ptr<asMaterial>>	_materials;
};
