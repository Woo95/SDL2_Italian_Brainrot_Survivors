#include "MobSpawner.h"
#include "Camera.h"
#include "../Scene.h"
#include "../../Entity/Object/AllObjects.h"
#include "../../Entity/Component/AllComponents.h"

CMobSpawner::CMobSpawner(CScene* scene, CCamera* camera)
{
	mScene = scene;
	// 스프라이트 크기 고려하여 영역을 확장 
	mExtendCamRes = camera->GetResolution() * 1.15f;
}

CMobSpawner::~CMobSpawner()
{
}

bool CMobSpawner::Init()
{
	mRegSpawnAmount   = CONST_REGULAR_MOB_SPAWN_AMOUNT;
	mRegularSpawnTime = CONST_REGULAR_MOB_SPAWN_INTERVAL;
	mSubBossSpawnTime = CONST_SUBBOSS_MOB_SPAWN_INTERVAL;

	mDespawnThreshold = mExtendCamRes.Length();

	// Set-Up Mob Pools //
	mRegularMobPool.emplace_back([this]() -> CEnemy* { return this->CreateMob<CReaper, 1>("Enemy_Boss_Reaper"); });
	mSubBossMobPool.emplace_back([this]() -> CEnemy* { return this->CreateMob<CReaper, 1>("Enemy_Boss_Reaper"); });

	return true;
}

void CMobSpawner::Update(float deltaTime)
{
	if (!mPlayer)
		return;

	mRegularSpawnTime -= deltaTime;
	mSubBossSpawnTime -= deltaTime;

	SpawnMob();
	RespawnMob();
}

template <typename T, int initialCapacity>
T* CMobSpawner::CreateMob(const std::string& name)
{
	return mScene->InstantiateObject<T, initialCapacity>(name);
}

void CMobSpawner::SpawnMob()
{
	if (mRegularSpawnTime <= 0.0f)
	{
		mRegularSpawnTime = CONST_REGULAR_MOB_SPAWN_INTERVAL;

		// SPAWN REGULAR MOB
		int idx = rand() % (mUnlockedRegIdx + 1);
		CEnemy* mob = mRegularMobPool[idx]();
		mob->GetTransform()->SetWorldPos(FVector2D::ZERO);
		mob->GetTransform()->SetWorldPos(GetRandomSpawnPos());
		mob->GetChase()->SetTarget(mPlayer->GetTransform());
		mSpawnedMobs.emplace_back(mob);

		// INDEX CONTROL
		mRegSpawnAmount--;
		if (mRegSpawnAmount <= 0)
		{
			mRegSpawnAmount = CONST_REGULAR_MOB_SPAWN_AMOUNT;
			mUnlockedRegIdx = std::min(mUnlockedRegIdx + 1, (int)mRegularMobPool.size() - 1);
		}
	}

	if (mSubBossSpawnTime <= 0.0f)
	{
		mSubBossSpawnTime = CONST_SUBBOSS_MOB_SPAWN_INTERVAL;

		// SPAWN SUB BOSS
		CEnemy* mob = mSubBossMobPool[mUnlockedBosIdx]();
		mob->GetTransform()->SetWorldPos(GetRandomSpawnPos());
		mob->GetChase()->SetTarget(mPlayer->GetTransform());
		mSpawnedMobs.emplace_back(mob);

		// INDEX CONTROL
		mUnlockedBosIdx = std::min(mUnlockedBosIdx + 1, (int)mSubBossMobPool.size() - 1);
	}
}

void CMobSpawner::RespawnMob()
{
	for (size_t i = mSpawnedMobs.size(); i > 0; i--)
	{
		CObject* mob = mSpawnedMobs[i - 1];

		if (!mob->GetActive())
		{
			std::swap(mSpawnedMobs[i - 1], mSpawnedMobs.back());
			mSpawnedMobs.pop_back();

			continue;
		}

		FVector2D delta = mob->GetTransform()->GetWorldPos() - mPlayer->GetTransform()->GetWorldPos();
		if (delta.Length() >= mDespawnThreshold)
		{
			mob->GetTransform()->SetWorldPos(mPlayer->GetTransform()->GetWorldPos() - delta);
		}
	}
}

FVector2D CMobSpawner::GetRandomSpawnPos() const
{
	const FVector2D& playerPos = mPlayer->GetTransform()->GetWorldPos();

	float scale = 1.3f;
	float halfW = mExtendCamRes.x * 0.5f * scale;
	float halfH = mExtendCamRes.y * 0.5f * scale;

	FVector2D pos = FVector2D::ZERO;
	switch (std::rand() % 4)
	{
	case 0: // 왼쪽
		pos.x = GetRandomRange(playerPos.x - halfW, playerPos.x - mExtendCamRes.x * 0.5f);
		pos.y = GetRandomRange(playerPos.y + halfH, playerPos.y - mExtendCamRes.y * 0.5f);
		break;
	case 1: // 오른쪽
		pos.x = GetRandomRange(playerPos.x + mExtendCamRes.x * 0.5f, playerPos.x + halfW);
		pos.y = GetRandomRange(playerPos.y + mExtendCamRes.y * 0.5f, playerPos.y - halfH);
		break;
	case 2: // 위
		pos.x = GetRandomRange(playerPos.x - halfW, playerPos.x + mExtendCamRes.x * 0.5f);
		pos.y = GetRandomRange(playerPos.y - mExtendCamRes.y * 0.5f, playerPos.y - halfH);
		break;
	case 3: // 아래
		pos.x = GetRandomRange(playerPos.x - mExtendCamRes.x * 0.5f, playerPos.x + halfW);
		pos.y = GetRandomRange(playerPos.y + halfH, playerPos.y + mExtendCamRes.y * 0.5f);
		break;
	}
	return pos;
}