#pragma once
#include <memory>
#include "Object3d.h"
#include "Vector3.h"

#include "DirectXCommon.h"
#include "Object3dCommon.h"
#include "Object3d.h"
#include "Camera.h"

class Skydome {
public:
	void Initialize(Object3dCommon* object3dCommon, DirectXCommon* dxCommon);
	void Update();
	void Draw();
	void SetCamera(Camera* camera);

	// スケール、回転、位置の設定
	void SetScale(const Vector3& scale) { scale_ = scale; }
	void SetRotate(const Vector3& rotate) { rotate_ = rotate; }
	void SetTranslate(const Vector3& translate) { translate_ = translate; }

private:
	std::unique_ptr<Object3d> object3d_ = nullptr;

	Vector3 scale_ = { 50.0f, 50.0f, 50.0f };
	Vector3 rotate_ = { 0.0f, 0.0f, 0.0f };
	Vector3 translate_ = { 0.0f, 0.0f, 0.0f };

	DirectXCommon* dxCommon_ = nullptr;
	Object3dCommon* obj3dCo_ = nullptr;

};
