#pragma once
#include "DirectXCommon.h"
#include "SrvManager.h"

class ParticleManager
{
public:
	//シングルトン
	static ParticleManager* GetInstance();

	//初期化
	void Initialize(DirectXCommon* dxCommon, SrvManager* srvManager);
	//終了
	void Finalize();
	//更新
	void Update();
	//描画
	void Draw();
private:

	////シングルトン-----------------------------------------------

	static ParticleManager* instance;

	//コンストラクタ、デストラクタの隠蔽
	ParticleManager() = default;
	~ParticleManager() = default;
	//コピーインストラクタの封印
	ParticleManager(ParticleManager&) = delete;
	//コピー代入演算子の封印
	ParticleManager& operator=(ParticleManager&) = delete;

	////---------------------------------------------------------

	//DirectXCommon
	DirectXCommon* dxCommon_ = nullptr;
	SrvManager* srvManager_ = nullptr;
};

