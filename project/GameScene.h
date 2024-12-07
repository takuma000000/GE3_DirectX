#pragma once
#include "AudioManager.h"
#include "engine/2d/Sprite.h"
#include "Object3d.h"
#include "TextureManager.h"
#include "SpriteCommon.h"
#include "Camera.h"

class GameScene
{
public://メンバ関数

	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム更新
	void Update();
	//描画
	void Draw();

private:

	//Audio
	std::unique_ptr<AudioManager> audio = nullptr;
	//ポインタ...Sprite
	std::unique_ptr<Sprite> sprite = nullptr;
	//ポインタ...SpriteCommon
	//std::unique_ptr<SpriteCommon> spriteCommon = nullptr;

	//Object3dの初期化
	Object3d* object3d = new Object3d();
	//AnotherObject3d ( もう一つのObject3d )
	Object3d* anotherObject3d = new Object3d();


};

