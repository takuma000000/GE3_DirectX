#include "GameScene.h"

void GameScene::Initialize()
{
	audio = std::make_unique<AudioManager>();
	audio->Initialize();

	//XAudioのエンジンのインスタンスを生成
	audio->LoadSound("Alarm01", "Alarm01.wav");
	// 音声の再生
	audio->PlaySound("Alarm01");

	//ファイルパス
	TextureManager::GetInstance()->LoadTexture("./resources/uvChecker.png");
	TextureManager::GetInstance()->LoadTexture("./resources/pokemon.png");

	//スプライト共通部の初期化
	SpriteCommon::GetInstance()->Initialize(DirectXCommon::GetInstance());

	sprite = std::make_unique<Sprite>();
	sprite->Initialize(SpriteCommon::GetInstance(), DirectXCommon::GetInstance(), "./resources/uvChecker.png");

	///--------------------------------------------

	object3d->Initialize(Object3dCommon::GetInstance(), DirectXCommon::GetInstance());
	object3d->SetModel("axis.obj");

	anotherObject3d->Initialize(Object3dCommon::GetInstance(), DirectXCommon::GetInstance());
	anotherObject3d->SetModel("plane.obj");

	//---------------------------------------------

	//Object3d共通部の初期化
	camera = std::make_unique<Camera>();
	camera->SetRotate({ 0.0f,0.0f,0.0f });
	camera->SetTranslate({ 0.0f,0.0f,-30.0f });
	//object3dCommon->SetDefaultCamera(camera.get());
	object3d->SetCamera(camera.get());
	anotherObject3d->SetCamera(camera.get());
	//ImGui用のcamera設定
	Vector3 cameraPosition = camera->GetTranslate();
	Vector3 cameraRotation = camera->GetRotate();

}

void GameScene::Finalize()
{

	////*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	////				解放
	////*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	// Object3dの解放
	delete object3d;
	// 終了処理
	audio->Finalize();
}

void GameScene::Update()
{
	sprite->ImGuiDebug();

	camera->Update();
	sprite->Update();
	object3d->Update();
	anotherObject3d->Update();

	//object3d*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

	//translate
	Vector3 translate = object3d->GetTranslate();
	translate = { 3.0f,-4.0f,0.0f };
	object3d->SetTranslate(translate);
	//rotate
	Vector3 rotate = object3d->GetRotate();
	rotate += { 0.0f, 0.0f, 0.1f };
	object3d->SetRotate(rotate);
	//scale
	Vector3 scale = object3d->GetScale();
	scale = { 1.0f, 1.0f, 1.0f };
	object3d->SetScale(scale);

	//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-


	//anotherObject3d-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	//translate
	Vector3 anotherTranslate = anotherObject3d->GetTranslate();
	anotherTranslate = { 3.0f,4.0f,0.0f };
	anotherObject3d->SetTranslate(anotherTranslate);
	//ratate
	Vector3 anotherRotate = anotherObject3d->GetRotate();
	anotherRotate += { 0.1f, 0.0f, 0.0f };
	anotherObject3d->SetRotate(anotherRotate);
	//scale
	Vector3 anotherScale = anotherObject3d->GetScale();
	anotherScale = { 1.0f, 1.0f, 1.0f };
	anotherObject3d->SetScale(anotherScale);

	//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
}

void GameScene::Draw()
{
	SpriteCommon::GetInstance()->DrawSetCommon();
	sprite->Draw();  // textureSrvHandleGPU は必要に応じて設定
	object3d->Draw(DirectXCommon::GetInstance());
	anotherObject3d->Draw(DirectXCommon::GetInstance());
}
