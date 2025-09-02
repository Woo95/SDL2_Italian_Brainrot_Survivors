#include "PlayMobSpawner.h"
#include "Camera.h"

CPlayMobSpawner::CPlayMobSpawner()
{
}

CPlayMobSpawner::~CPlayMobSpawner()
{
}

bool CPlayMobSpawner::Init()
{
	mRegularSpawnTime = CONST_REGULAR_MOB_SPAWN_INTERVAL;
	mPatternSpawnTime = CONST_PATTERN_MOB_SPAWN_INTERVAL;
	mSubBossSpawnTime = CONST_SUBBOSS_MOB_SPAWN_INTERVAL;

	return true;
}

void CPlayMobSpawner::Update(float deltaTime)
{
	mRegularSpawnTime -= deltaTime;
	mPatternSpawnTime -= deltaTime;
	mSubBossSpawnTime -= deltaTime;

	// 매 n초마다 기본 몬스터 소환
	if (mRegularSpawnTime <= 0.0f)
	{
		mRegularSpawnTime = CONST_REGULAR_MOB_SPAWN_INTERVAL;

		// 시간 베이스로 몬스터 경험치 레벨 공격력 등등 상향

	}

	// 특정 패턴으로 소환 30초마다 (네모, 동그라미, 외각 동그라미(?))
	if (mPatternSpawnTime <= 0.0f)
	{
		mPatternSpawnTime = CONST_PATTERN_MOB_SPAWN_INTERVAL;

		// 시간 베이스로 몬스터 경험치 레벨 공격력 등등 상향
	}

	// 1분마다 서브 보스 소환 (서브 보스 4마리)
	if (mSubBossSpawnTime <= 0.0f)
	{
		mSubBossSpawnTime = CONST_SUBBOSS_MOB_SPAWN_INTERVAL;

		// 시간 베이스로 몬스터 경험치 레벨 공격력 등등 상향
	}
}