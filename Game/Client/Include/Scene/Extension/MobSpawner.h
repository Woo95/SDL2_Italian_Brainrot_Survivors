#pragma once

#include <vector>
#include "../../Core/Vector2D.h"

class CCamera;
class CObject;

class CMobSpawner
{
	friend class CPlayScene;

private:
	CMobSpawner() = delete;
	CMobSpawner(CCamera* camera);
	~CMobSpawner();

private:
	// -- Player & Camera --
	FVector2D mExtendCamRes = FVector2D::ZERO;
	CObject* mPlayer = nullptr;

	// -- Mob Pools --
	std::vector<CObject*> mRegularMobPool;
	std::vector<CObject*> mSubBossMobPool;
	std::vector<CObject*> mSpawnedMobs;

	int mRegSpawnAmount = 0;
	int mUnlockedRegIdx = 0;
	int mUnlockedBosIdx = 0;

	// Spawn timers and thresholds
	float mRegularSpawnTime = 0.0f;
	float mSubBossSpawnTime = 0.0f;
	float mDespawnThreshold = 0.0f;

	// -- Constants --
	const int   CONST_REGULAR_MOB_SPAWN_AMOUNT   = 30;
	const float CONST_REGULAR_MOB_SPAWN_INTERVAL = 1.0f;
	const float CONST_SUBBOSS_MOB_SPAWN_INTERVAL = 50.0f;

private:
	bool Init();
	void Update(float deltaTime);

	void SpawnMob();
	void RespawnMob();

private:
	FVector2D GetRandomSpawnPos() const;
	inline float GetRandomRange(float min, float max) const
	{
		return min + (float)std::rand() / (RAND_MAX + 1.0f) * (max - min);
	}

	void SetPlayer(CObject* player)
	{
		mPlayer = player;
	}
};