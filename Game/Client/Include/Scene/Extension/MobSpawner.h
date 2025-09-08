#pragma once

#include "../../Core/GameInfo.h"
#include "../../Core/Vector2D.h"

class CScene;
class CCamera;
class CObject;
class CEnemy;

class CMobSpawner
{
	friend class CPlayScene;

private:
	CMobSpawner() = delete;
	CMobSpawner(CScene* scene, CCamera* camera);
	~CMobSpawner();

private:
	CScene* mScene;

	// Player & Camera
	FVector2D mExtendCamRes = FVector2D::ZERO;
	CObject* mPlayer = nullptr;

	// Mob Pools
	std::vector<std::function<CEnemy*()>> mRegularMobPool;
	std::vector<std::function<CEnemy*()>> mSubBossMobPool;
	std::vector<CEnemy*> mSpawnedMobs;

	int mRegSpawnAmount = 0;
	int mUnlockedRegIdx = 0;
	int mUnlockedBosIdx = 0;

	// Spawn timers and thresholds
	float mRegularSpawnTime = 0.0f;
	float mSubBossSpawnTime = 0.0f;
	float mDespawnThreshold = 0.0f;

	// Constants
	const int   CONST_REGULAR_MOB_SPAWN_AMOUNT   = 30;
	const float CONST_REGULAR_MOB_SPAWN_INTERVAL = 1.0f;
	const float CONST_SUBBOSS_MOB_SPAWN_INTERVAL = 50.0f;

private:
	bool Init();
	void Update(float deltaTime);

private:
	template <typename T, int initialCapacity>
	T* CreateMob(const std::string& name);
	void SpawnMob();
	void RespawnMob();

	FVector2D GetRandomSpawnPos() const;
	float GetRandomRange(float min, float max) const
	{
		return min + (float)std::rand() / (RAND_MAX + 1.0f) * (max - min);
	}

	void SetPlayer(CObject* player)
	{
		mPlayer = player;
	}
};