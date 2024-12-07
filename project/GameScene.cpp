#include "GameScene.h"

void GameScene::Initialize()
{
	audio = std::make_unique<AudioManager>();
	audio->Initialize();

	//XAudioのエンジンのインスタンスを生成
	audio->LoadSound("fanfare", "fanfare.wav");
	// 音声の再生
	audio->PlaySound("fanfare");

	//ファイルパス
	TextureManager::GetInstance()->LoadTexture("./resources/uvChecker.png");
	TextureManager::GetInstance()->LoadTexture("./resources/pokemon.png");

	//スプライト共通部の初期化
	//SpriteCommon::GetInstance()->Initialize(dx)

	/*sprite = std::make_unique<Sprite>();
	sprite->Initialize(SpriteCommon::GetInstance(), dxCommon.get(), "./resources/uvChecker.png");*/

	///--------------------------------------------

	/*object3d->Initialize(object3dCommon.get(), dxCommon.get());
	object3d->SetModel("axis.obj");

	anotherObject3d->Initialize(object3dCommon.get(), dxCommon.get());
	anotherObject3d->SetModel("plane.obj");*/

	//---------------------------------------------

	////Object3d共通部の初期化
	//camera = std::make_unique<Camera>();
	//camera->SetRotate({ 0.0f,0.0f,0.0f });
	//camera->SetTranslate({ 0.0f,0.0f,-30.0f });
	////object3dCommon->SetDefaultCamera(camera.get());
	//object3d->SetCamera(camera.get());
	//anotherObject3d->SetCamera(camera.get());
	////ImGui用のcamera設定
	//Vector3 cameraPosition = camera->GetTranslate();
	//Vector3 cameraRotation = camera->GetRotate();

}

void GameScene::Finalize()
{
}

void GameScene::Update()
{
}

void GameScene::Draw()
{
}
