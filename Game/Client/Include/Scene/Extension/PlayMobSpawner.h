#pragma once

#include "../../Core/Vector2D.h"

class CPlayMobSpawner
{
	friend class CPlayScene;

private:
	CPlayMobSpawner();
	~CPlayMobSpawner();

private:
	const float CONST_REGULAR_MOB_SPAWN_INTERVAL = 0.75f;
	const float CONST_PATTERN_MOB_SPAWN_INTERVAL = 30.0f;
	const float CONST_SUBBOSS_MOB_SPAWN_INTERVAL = 60.0f;

	float mRegularSpawnTime = 0.0f;
	float mPatternSpawnTime = 0.0f;
	float mSubBossSpawnTime = 0.0f;

private:
	bool Init();
	void Update(float deltaTime);
};