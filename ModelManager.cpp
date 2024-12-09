#include "ModelManager.h"
#include "ModelCommon.h"
#include "Model.h"
#include "DirectXCommon.h"

ModelManager* ModelManager::instance = nullptr;

ModelManager* ModelManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new ModelManager;
	}
	return instance;
}

void ModelManager::Finalize()
{
	delete instance;
	instance = nullptr;
}

void ModelManager::Initialize(DirectXCommon* dxCommon)
{
	//ポインタ...ModelCommon
	std::unique_ptr<ModelCommon> modelCommon = nullptr;
	//Object3d共通部の初期化
	modelCommon = std::make_unique<ModelCommon>();
	modelCommon->Initialize(dxCommon);
}

void ModelManager::LoadModel(const std::string& filePath, DirectXCommon* dxCommon)
{
	dxCommon_ = dxCommon;

	//読み込み済みモデルを検索
	if (models.contains(filePath)) {
		//読み込み済みなら早期return
		return;
	}
	//モデルの生成とファイル読み込み、初期化
	std::unique_ptr<Model> model = std::make_unique<Model>();
	model->Initialize(modelCommon, dxCommon_, "resources", filePath);

	//モデルをmapコンテナに格納する
	models.insert(std::make_pair(filePath, std::move(model)));
}

Model* ModelManager::FindModel(const std::string& filePath)
{
	//読み込み済みモデルを検索
	if (models.contains(filePath)) {
		//読み込みモデルを戻り値としてreturn
		return models.at(filePath).get();
	}

	//ファイル名一致なし
	return nullptr;
}
