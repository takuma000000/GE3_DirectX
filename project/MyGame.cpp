#include "MyGame.h"

#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_6.h>

void MyGame::Initialize()
{
	///*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

	//ゲームプレイシーンの作成
	scene_ = new GameScene();
	//ゲームプレイシーンの初期化
	scene_->Initialize();

	///*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-


	//基底クラスの初期化処理
	Framework::Initialize();

	//基盤システムの初期化*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

	//WindowsAPIの初期化
	windowsAPI = std::make_unique<WindowsAPI>();
	windowsAPI->Initialize();

	//入力の初期化
	input = std::make_unique<Input>();
	input->Initialize(windowsAPI.get());

	//DirectXの初期化
	dxCommon = std::make_unique<DirectXCommon>();
	dxCommon->Initialize(windowsAPI.get());

	srvManager = std::make_unique<SrvManager>();
	srvManager->Initialize(dxCommon.get());

	//Object3d共通部の初期化
	object3dCommon = std::make_unique<Object3dCommon>();
	object3dCommon->Initialize(dxCommon.get());

	//テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon.get(), srvManager.get());

	ModelManager::GetInstance()->Initialize(dxCommon.get());
	ModelManager::GetInstance()->LoadModel("axis.obj", dxCommon.get());

	imguiManager = std::make_unique<ImGuiManager>();
	imguiManager->Initialize(windowsAPI.get(), dxCommon.get());

	//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
}

void MyGame::Finalize()
{
	////*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	////				解放
	////*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	// 3Dモデルマネージャーの終了
	ModelManager::GetInstance()->Finalize();

	// テクスチャマネージャーの終了
	TextureManager::GetInstance()->Finalize();

	// 終了処理
	imguiManager->Finalize();
	windowsAPI->Finalize();

	//シーンの終了処理
	scene_->Finalize();
	//シーンの解放
	delete scene_;

	//基底クラスの終了処理
	Framework::Finalize();
}

void MyGame::Update()
{

	//基底クラスの更新処理
	Framework::Update();
	//シーンの更新処理
	scene_->Update();

	if (windowsAPI->ProcessMessage()) {
		endRequest_ = true;
	}

	// ** ImGui処理開始 **
	imguiManager->Begin();

	// ** ImGui処理終了 **
	imguiManager->End();

	////開発用UIの処理。実際に開発用のUIを出す場合はここをゲーム固有の処理に置き換える
	////ImGui::ShowDemoWindow();

	////ImGuiの内部コマンドを生成する
	//ImGui::Render();

	viewport = dxCommon->GetViewport();
	scissorRect = dxCommon->GetRect();

}

void MyGame::Draw()
{
	//Draw
	dxCommon->PreDraw();
	object3dCommon->DrawSetCommon();
	srvManager->PreDraw();

	//シーン描画
	scene_->Draw();

	//描画
	dxCommon->GetCommandList()->RSSetViewports(1, &viewport);
	dxCommon->GetCommandList()->RSSetScissorRects(1, &scissorRect);

	// ** ImGui描画 **
	imguiManager->Draw();

	dxCommon->PostDraw();
}
