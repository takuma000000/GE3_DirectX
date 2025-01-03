#include "GameScene.h"

void GameScene::Initialize()
{

	assert(this != nullptr && "this is nullptr in GameScene::Initialize");
	assert(dxCommon != nullptr && "dxCommon is nullptr in GameScene::Initialize");

	//AudioManager::GetInstance()->LoadSound("fanfare", "fanfare.wav");
	//AudioManager::GetInstance()->PlaySound("fanfare");
	
	//ファイルパス
	TextureManager::GetInstance()->LoadTexture("./resources/uvChecker.png");
	TextureManager::GetInstance()->LoadTexture("./resources/pokemon.png");

	sprite = std::make_unique<Sprite>();
	sprite->Initialize(SpriteCommon::GetInstance(), dxCommon, "./resources/uvChecker.png");

	ModelManager::GetInstance()->LoadModel("axis.obj", dxCommon);

	object3d->Initialize(Object3dCommon::GetInstance(), dxCommon);
	object3d->SetModel("axis.obj");

	anotherObject3d->Initialize(Object3dCommon::GetInstance(), dxCommon);
	anotherObject3d->SetModel("plane.obj");

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
	// テクスチャマネージャーの終了
	TextureManager::GetInstance()->Finalize();

	// 終了処理
	AudioManager::GetInstance()->Finalize();

	// Object3dの解放
	delete object3d;
	delete anotherObject3d;

	// 3Dモデルマネージャーの終了
	ModelManager::GetInstance()->Finalize();
}

void GameScene::Update()
{
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
	//Draw
	SpriteCommon::GetInstance()->DrawSetCommon();
	Object3dCommon::GetInstance()->DrawSetCommon();

	sprite->Draw();  // textureSrvHandleGPU は必要に応じて設定
	object3d->Draw(dxCommon);
	anotherObject3d->Draw(dxCommon);
}
