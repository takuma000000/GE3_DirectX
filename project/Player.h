#pragma once
#include <memory>
#include "Object3d.h"
#include "Vector3.h"
#include "DirectXCommon.h"
#include "Object3dCommon.h"
#include "Sprite.h"
#include "Camera.h"
#include "Input.h"
#include <windows.h>

#include <vector>
#include "PlayerBullet.h"

class Player {
public:

	void Initialize(Object3dCommon* object3dCommon, DirectXCommon* dxCommon, Camera* camera, Input* input, SpriteCommon* spriteCommon);
	void Update();
	void Draw();

	void FireBullet();

	Vector3 GetTargetDirection() const; // 新規追加

	// スケール、回転、位置の設定
	void SetScale(const Vector3& scale) { transform_.scale = scale; }
	void SetRotate(const Vector3& rotate) { transform_.rotate = rotate; }
	void SetTranslate(const Vector3& translate) { transform_.translate = translate; }

	void SetCamera(Camera* camera);

	Vector3 ScreenToWorld(const POINT& screenPos) const;

	void DrawImGui();

	void SetSpriteCommon(SpriteCommon* spriteCommon); // Sprite共通部の設定

	// 弾の取得
	const std::vector<std::unique_ptr<PlayerBullet>>& GetBullets() const { return bullets_; }


private:
	Transform transform_;

	std::unique_ptr<Object3d> object3d_ = nullptr;

	DirectXCommon* dxCommon_ = nullptr;
	Object3dCommon* obj3dCo_ = nullptr;
	Camera* camera_ = nullptr;
	Input* input_ = nullptr;
	WindowsAPI* windo = nullptr;

	std::vector<std::unique_ptr<PlayerBullet>> bullets_;

	std::unique_ptr<Sprite> mouseSprite_;            // マウス位置を示すSprite
	SpriteCommon* spriteCommon_ = nullptr;           // Sprite共通部
};