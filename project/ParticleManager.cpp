#include "ParticleManager.h"

ParticleManager* ParticleManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new ParticleManager;
	}
	return instance;
}

void ParticleManager::Initialize(DirectXCommon* dxCommon, SrvManager* srvManager)
{
	//引数受け取り
	dxCommon_ = dxCommon;
	srvManager_ = srvManager;
}

void ParticleManager::Finalize()
{
	delete instance;
	instance = nullptr;
}

void ParticleManager::Update()
{
}

void ParticleManager::Draw()
{
}
