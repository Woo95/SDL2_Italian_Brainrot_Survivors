#pragma once

#include "../../Core/GameInfo.h"
#include "../../Core/Vector2D.h"

class CScene;
class CPlayer;
class CEnemy;

class CMobSpawner
{
	friend class CPlayScene;

private:
	CMobSpawner() = delete;
	CMobSpawner(CScene* scene);
	~CMobSpawner();

private:
	// Scene & Player
	CScene*  mScene  = nullptr;
	CPlayer* mPlayer = nullptr;

	// Spawn related variables
	std::vector<CEnemy*> mSpawnedMobs;

	int mRegSpawnAmount = 0;
	int mUnlockedRegIdx = 0;
	int mUnlockedBosIdx = 0;

	// Spawn timers and thresholds
	float mRegularSpawnTime = 0.0f;
	float mSubBossSpawnTime = 0.0f;
	float mDespawnThreshold = 0.0f;

	// Constants
	const int   CONST_REGULAR_MOB_SPAWN_AMOUNT   = 35;
	const float CONST_REGULAR_MOB_SPAWN_INTERVAL = 0.75f;
	const float CONST_SUBBOSS_MOB_SPAWN_INTERVAL = 50.0f;

private:
	bool Init();
	void Update(float deltaTime);

private:
	void SpawnMob();
	void RespawnMob();

	FVector2D GetRandomSpawnPos(float scale) const;
	float GetRandomRange(float min, float max) const
	{
		return min + (float)std::rand() / (RAND_MAX + 1.0f) * (max - min);
	}

	void SetPlayer(CPlayer* player)
	{
		mPlayer = player;
	}

	void BindEventListeners();
};