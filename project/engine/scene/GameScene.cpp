#include "GameScene.h"

void GameScene::Initialize()
{
	// ──────────────── NULLチェック ────────────────
	assert(this != nullptr && "this is nullptr in GameScene::Initialize");
	assert(dxCommon != nullptr && "dxCommon is nullptr in GameScene::Initialize");

	// ──────────────── 各種初期化処理 ───────────────
	InitializeAudio();   // サウンドのロード＆再生
	LoadTextures();      // テクスチャのロード
	InitializeSprite();  // スプライトの作成＆初期化
	LoadModels();        // 3Dモデルのロード
	InitializeObjects(); // 3Dオブジェクトの作成＆初期化
	InitializeCamera();  // カメラの作成＆設定
}

void GameScene::Finalize()
{
	// テクスチャマネージャーの終了
	TextureManager::GetInstance()->Finalize();

	// 終了処理
	AudioManager::GetInstance()->Finalize();

	// 3Dモデルマネージャーの終了
	ModelManager::GetInstance()->Finalize();
}

void GameScene::Update()
{
	// ────────────────────────────────────────
	// 各オブジェクトの更新処理
	// ────────────────────────────────────────
	camera->Update();
	sprite->Update();
	object3d->Update();
	anotherObject3d->Update();

	// ────────────────────────────────────────
	// 移動・回転（加算）・スケール更新
	// ────────────────────────────────────────

	//*-*-*-*-*-*-*-*-*-*-*
	// object3d
	//*-*-*-*-*-*-*-*-*-*-*
	UpdateObjectTransform(object3d, { 3.0f, -4.0f, 0.0f }, { 0.0f,0.0f,0.0f }, { 1.0f, 1.0f, 1.0f });

	//*-*-*-*-*-*-*-*-*-*-*
	// anotherObject3d
	//*-*-*-*-*-*-*-*-*-*-*

	// 回転
	Vector3 anotherRotate = anotherObject3d->GetRotate();
	anotherRotate.x += 0.1f;

	UpdateObjectTransform(anotherObject3d, { 3.0f, 4.0f, 0.0f }, anotherRotate, { 1.0f, 1.0f, 1.0f });
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

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// ゲーム内のサウンドをロード＆再生する
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void GameScene::InitializeAudio()
{
	//AudioManager::GetInstance()->LoadSound("fanfare", "fanfare.wav");
	//AudioManager::GetInstance()->PlaySound("fanfare");
}

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// 必要なテクスチャをロードする
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void GameScene::LoadTextures()
{
	//ファイルパス
	TextureManager::GetInstance()->LoadTexture("./resources/uvChecker.png");
	TextureManager::GetInstance()->LoadTexture("./resources/pokemon.png");
	TextureManager::GetInstance()->LoadTexture("./resources/circle.png");
}

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// スプライトを作成し、初期化する
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void GameScene::InitializeSprite()
{
	sprite = std::make_unique<Sprite>();
	sprite->Initialize(SpriteCommon::GetInstance(), dxCommon, "./resources/uvChecker.png");
}

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// 必要な3Dモデルをロードする
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void GameScene::LoadModels()
{
	ModelManager::GetInstance()->LoadModel("axis.obj", dxCommon);
}

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// 3Dオブジェクトを作成し、初期化する
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void GameScene::InitializeObjects()
{
	object3d = std::make_unique<Object3d>();
	object3d->Initialize(Object3dCommon::GetInstance(), dxCommon);
	object3d->SetModel("axis.obj");

	anotherObject3d = std::make_unique<Object3d>();
	anotherObject3d->Initialize(Object3dCommon::GetInstance(), dxCommon);
	anotherObject3d->SetModel("plane.obj");
}

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// カメラを作成し、各オブジェクトに適用する
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void GameScene::InitializeCamera()
{
	//Object3d共通部の初期化
	camera = std::make_unique<Camera>();
	camera->SetRotate({ 0.0f,0.0f,0.0f });
	camera->SetTranslate({ 0.0f,0.0f,-30.0f });

	object3d->SetCamera(camera.get());
	anotherObject3d->SetCamera(camera.get());
}

// ──────────────────────────────────────────────
// ● 指定した Object3d の Transform を更新する
// ──────────────────────────────────────────────
// - 更新対象の Object3d の座標・回転・スケールを設定）
// ──────────────────────────────────────────────
/**
 * @param obj       [in/out] 更新対象の Object3d
 * @param translate [in]     新しい座標
 * @param rotate    [in]     新しい回転角（加算処理なし）
 * @param scale     [in]     スケール値（直接上書き）
 */
void GameScene::UpdateObjectTransform(std::unique_ptr<Object3d>& obj, const Vector3& translate, const Vector3& rotate, const Vector3& scale)
{
	obj->SetTranslate(translate);
	obj->SetRotate(rotate);
	obj->SetScale(scale);
}
