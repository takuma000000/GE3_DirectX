#pragma once
#include "Framework.h"

// GE3クラス化(MyClass)
#include "Input.h"
#include "Object3dCommon.h"
#include "Model.h"
#include "ModelCommon.h"
#include "ModelManager.h"
#include "ImGuiManager.h"
#include "TextureManager.h"


class MyGame : public Framework
{
public://メンバ関数
	//初期化
	void Initialize() override;
	//終了
	void Finalize() override;
	//毎フレーム更新
	void Update() override;
	//描画
	void Draw() override;

private://メンバ変数

	//ポインタ...Input
	std::unique_ptr<Input> input = nullptr;
	//ポインタ...Object3dCommon
	std::unique_ptr<Object3dCommon> object3dCommon = nullptr;
	//ポインタ...ImGuiManager
	std::unique_ptr<ImGuiManager>  imguiManager = nullptr;

	D3D12_VIEWPORT viewport;
	D3D12_RECT scissorRect;

private:
	//フラグ
	bool endRequest_ = false; // 終了フラグ

};

