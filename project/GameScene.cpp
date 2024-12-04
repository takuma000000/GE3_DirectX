#include "GameScene.h"

void GameScene::Initialize()
{
	audio = std::make_unique<AudioManager>();
	audio->Initialize();

	//XAudioのエンジンのインスタンスを生成
	audio->LoadSound("fanfare", "fanfare.wav");
	// 音声の再生
	audio->PlaySound("fanfare");

	//テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon.get(), srvManager.get());
	//ファイルパス
	TextureManager::GetInstance()->LoadTexture("./resources/uvChecker.png");
	TextureManager::GetInstance()->LoadTexture("./resources/pokemon.png");

	sprite = std::make_unique<Sprite>();
	sprite->Initialize(spriteCommon.get(), dxCommon.get(), "./resources/uvChecker.png");

	///--------------------------------------------

	object3d->Initialize(object3dCommon.get(), dxCommon.get());
	object3d->SetModel("axis.obj");

	anotherObject3d->Initialize(object3dCommon.get(), dxCommon.get());
	anotherObject3d->SetModel("plane.obj");

	//---------------------------------------------

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
