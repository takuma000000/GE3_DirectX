#pragma once
#include "MyMath.h"
#include <string>
#include <vector>
#include "DirectXCommon.h"

class Object3dCommon;

struct Vector2 {
	float x;
	float y;
};

struct Vector4 {
	float x;
	float y;
	float z;
	float w;
};

//頂点データ
struct VertexData {
	Vector4 position;
	Vector2 texcoord;
	Vector3 normal;
};

struct MaterialData {
	std::string textureFilePath;
};

struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
};

//マテリアルデータ
struct Material {
	Vector4	color;
	int32_t enableLighting;
	float padding[3];
	Matrix4x4 uvTransform;
};

class Object3d
{


public://メンバ関数
	void Initialize(Object3dCommon* object3dCommon, DirectXCommon* dxCommon);

private:
	Object3dCommon* object3dCommon = nullptr;
	DirectXCommon* dxCommon_;
	//Objファイルのデータ
	ModelData modelData;

	//.mtlファイル読み込み
	static MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);
	//.objファイル読み込み
	static ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

	//頂点リソースを作る
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	//頂点リソースにデータを書き込む
	VertexData* vertexData = nullptr;
	//頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

};

