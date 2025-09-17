#include "MobSpawner.h"
#include "Camera.h"
#include "../Scene.h"
#include "../../Core/Utils/GameDataUtils.h"
#include "../../Entity/Object/AllObjects.h"
#include "../../Entity/Component/AllComponents.h"
#include "../../Manager/EventManager.h"

CMobSpawner::CMobSpawner(CScene* scene)
{
	mScene = scene;
}

CMobSpawner::~CMobSpawner()
{
}

bool CMobSpawner::Init()
{
	BindEventListeners();

	mRegSpawnAmount   = CONST_REGULAR_MOB_SPAWN_AMOUNT;
	mRegularSpawnTime = CONST_REGULAR_MOB_SPAWN_INTERVAL;
	mSubBossSpawnTime = CONST_SUBBOSS_MOB_SPAWN_INTERVAL;

	mDespawnThreshold = mScene->GetCamera()->GetResolution().Length() * 0.75f;

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

void CMobSpawner::SpawnMob()
{
	if (mRegularSpawnTime <= 0.0f)
	{
		mRegularSpawnTime = CONST_REGULAR_MOB_SPAWN_INTERVAL;

		// SPAWN REGULAR MOB
		int idx = rand() % (mUnlockedRegIdx + 1);
		CEventManager::GetInst()->Broadcast(EEventType::REGULAR_MOB_SPAWN, &idx);

		// INDEX CONTROL
		mRegSpawnAmount--;
		if (mRegSpawnAmount <= 0)
		{
			mRegSpawnAmount = CONST_REGULAR_MOB_SPAWN_AMOUNT;
			mUnlockedRegIdx = std::min(mUnlockedRegIdx + 1, (int)ERegularMobType::MAX - 1);
		}
	}

	if (mSubBossSpawnTime <= 0.0f)
	{
		mSubBossSpawnTime = CONST_SUBBOSS_MOB_SPAWN_INTERVAL;

		// SPAWN SUB BOSS
		CEventManager::GetInst()->Broadcast(EEventType::SUBBOSS_MOB_SPAWN, &mUnlockedBosIdx);

		// INDEX CONTROL
		mUnlockedBosIdx = std::min(mUnlockedBosIdx + 1, (int)ESubBossMobType::MAX - 1);
	}
}

void CMobSpawner::RespawnMob()
{
	for (size_t i = mSpawnedMobs.size(); i > 0; i--)
	{
		CEnemy* mob = mSpawnedMobs[i - 1];

		if (!mob->GetActive())
		{
			std::swap(mSpawnedMobs[i - 1], mSpawnedMobs.back());
			mSpawnedMobs.pop_back();

			continue;
		}

		FVector2D delta = mob->GetTransform()->GetWorldPos() - mPlayer->GetTransform()->GetWorldPos();
		if (delta.Length() >= mDespawnThreshold)
		{
			mob->GetTransform()->SetWorldPos(GetRandomSpawnPos(1.1f));
		}
	}
}

FVector2D CMobSpawner::GetRandomSpawnPos(float scale) const
{
	const FVector2D& playerPos = mPlayer->GetTransform()->GetWorldPos();

	float halfW = mScene->GetCamera()->GetResolution().x * 0.5f;
	float halfH = mScene->GetCamera()->GetResolution().y * 0.5f;
	float scaledHalfW = halfW * scale;
	float scaledHalfH = halfH * scale;

	FVector2D pos = FVector2D::ZERO;
	switch (std::rand() % 4)
	{
	case 0: // 왼쪽
		pos.x = GetRandomRange(playerPos.x - scaledHalfW, playerPos.x - halfW);
		pos.y = GetRandomRange(playerPos.y + scaledHalfH, playerPos.y - halfH);
		break;
	case 1: // 오른쪽
		pos.x = GetRandomRange(playerPos.x + halfW, playerPos.x + scaledHalfW);
		pos.y = GetRandomRange(playerPos.y + halfH, playerPos.y - scaledHalfH);
		break;
	case 2: // 위
		pos.x = GetRandomRange(playerPos.x - scaledHalfW, playerPos.x + halfW);
		pos.y = GetRandomRange(playerPos.y - halfH, playerPos.y - scaledHalfH);
		break;
	case 3: // 아래
		pos.x = GetRandomRange(playerPos.x - halfW, playerPos.x + scaledHalfW);
		pos.y = GetRandomRange(playerPos.y + scaledHalfH, playerPos.y + halfH);
		break;
	}
	return pos;
}

void CMobSpawner::BindEventListeners()
{
	CEventManager* EM = CEventManager::GetInst();

	// 몬스터 스포너 관련
	EM->AddListener(EEventType::REGULAR_MOB_SPAWN, [this](void* data)
	{
		ERegularMobType type = (ERegularMobType)(*(int*)data);

		CEnemy* mob = nullptr;
		switch (type)
		{
		case ERegularMobType::SKELETON:
			mob = mScene->InstantiateObject<CSkeleton, 25>("Enemy_Mob_Skeleton");
			break;
		case ERegularMobType::SKELETON_KNIFE:
			mob = mScene->InstantiateObject<CSkeletonKnife, 25>("Enemy_Mob_SkeletonKnife");
			break;
		case ERegularMobType::SKULL:
			mob = mScene->InstantiateObject<CSkull, 25>("Enemy_Mob_Skull");
			break;
		case ERegularMobType::SKELETON_PANTHER:
			mob = mScene->InstantiateObject<CSkeletonPanther, 25>("Enemy_Mob_SkeletonPanther");
			break;
		case ERegularMobType::SKELETON_XL:
			mob = mScene->InstantiateObject<CSkeletonXL, 25>("Enemy_Mob_SkeletonXL");
			break;
		case ERegularMobType::SKELETON_MAD:
			mob = mScene->InstantiateObject<CSkeletonMad, 25>("Enemy_Mob_SkeletonMad");
			break;
		case ERegularMobType::SKELETON_ANGEL:
			mob = mScene->InstantiateObject<CSkeletonAngel, 25>("Enemy_Mob_SSkeletonAngel");
			break;
		case ERegularMobType::SKELETON_NINJA:
			mob = mScene->InstantiateObject<CSkeletonNinja, 25>("Enemy_Mob_SkeletonNinja");
			break;
		case ERegularMobType::SKELETON_DRAGON:
			mob = mScene->InstantiateObject<CSkeletonDragon, 25>("Enemy_Mob_SkeletonDragon");
			break;
		}

		if (mob)
		{
			mob->GetTransform()->SetWorldPos(GetRandomSpawnPos(1.2f));
			mob->GetChase()->SetTarget(mPlayer->GetTransform());
			mSpawnedMobs.emplace_back(mob);
		}
	});
	EM->AddListener(EEventType::SUBBOSS_MOB_SPAWN, [this](void* data)
	{
		ESubBossMobType type = (ESubBossMobType)(*(int*)data);

		CEnemy* mob = nullptr;
		switch (type)
		{
		case ESubBossMobType::REAPER:
			mob = mScene->InstantiateObject<CReaper, 1>("Enemy_Boss_Reaper");
			break;
		case ESubBossMobType::DROWNER:
			mob = mScene->InstantiateObject<CDrowner, 1>("Enemy_Boss_Drowner");
			break;
		case ESubBossMobType::TRICKSTER:
			mob = mScene->InstantiateObject<CTrickster, 1>("Enemy_Boss_Trickster");
			break;
		case ESubBossMobType::STALKER:
			mob = mScene->InstantiateObject<CStalker, 1>("Enemy_Boss_Stalker");
			break;
		case ESubBossMobType::MADDENER:
			mob = mScene->InstantiateObject<CMaddener, 1>("Enemy_Boss_Maddener");
			break;
		case ESubBossMobType::ENDER:
			mob = mScene->InstantiateObject<CEnder, 1>("Enemy_Boss_Ender");
			break;
		}

		if (mob)
		{
			mob->GetTransform()->SetWorldPos(GetRandomSpawnPos(1.2f));
			mob->GetChase()->SetTarget(mPlayer->GetTransform());
			mSpawnedMobs.emplace_back(mob);
		}
	});
}
