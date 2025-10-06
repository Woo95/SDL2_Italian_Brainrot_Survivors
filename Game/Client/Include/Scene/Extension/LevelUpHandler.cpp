#include "LevelUpHandler.h"
#include "../PlayScene.h"
#include "../../Entity/Object/AllObjects.h"
#include "../../Entity/Component/AllComponents.h"
#include "../../Manager/EventManager.h"

CLevelUpHandler::CLevelUpHandler(CPlayScene* scene)
{
	mScene = scene;
}

CLevelUpHandler::~CLevelUpHandler()
{
}

bool CLevelUpHandler::Init()
{
	BindEventListener();

	return true;
}

void CLevelUpHandler::CreateItemPool()
{
	mItemPool.clear();
	CInventoryComponent* inventory = mScene->GetPlayer()->GetInventory();

	// 가능한 파워업을 옵션에 추가
	for (int i = 0; i < (int)EPowerUpType::MAX; i++)
	{
		EPowerUpType type = static_cast<EPowerUpType>(i);
		int level = inventory->GetPowerUpLevel(type);

		if (level >= CONST_MAX_POWERUP_LEVEL)
			continue;

		if (inventory->HasEmptySlot(EItemCategory::POWERUP) || inventory->GetPowerUp(type))
		{
			mItemPool.emplace_back(FSelectableItem(EItemCategory::POWERUP, (signed char)type, level));
		}
	}

	// 가능한 무기를 옵션에 추가
	for (int i = 0; i < (int)EWeaponType::MAX; i++)
	{
		EWeaponType type = static_cast<EWeaponType>(i);
		int level = inventory->GetWeaponLevel(type);

		if (level >= CONST_MAX_WEAPON_LEVEL)
			continue;

		if (inventory->HasEmptySlot(EItemCategory::WEAPON) || inventory->GetWeapon(type))
		{
			mItemPool.emplace_back(FSelectableItem(EItemCategory::WEAPON, (signed char)type, level));
		}
	}

	// 옵션 섞기
	for (int i = 0; i < mItemPool.size(); i++)
	{
		int randIdx = std::rand() % mItemPool.size();
		std::swap(mItemPool[i], mItemPool[randIdx]);
	}
	// 옵션 3개만 유지
	if (mItemPool.size() > 3)
		mItemPool.resize(3);

	// 선택 옵션이 없을 경우
	if (mItemPool.empty())
	{
		mItemPool.emplace_back(FSelectableItem(EItemCategory::CONSUMABLE, 0, 0));
		mItemPool.emplace_back(FSelectableItem(EItemCategory::CONSUMABLE, 1, 0));
	}
}

void CLevelUpHandler::BindEventListener()
{
	CEventManager* EM = CEventManager::GetInst();

	EM->AddListener(EEventType::PLAYER_LEVEL_UP_BEGIN, [this](void*)
	{
		CreateItemPool();
		CEventManager::GetInst()->Broadcast(EEventType::PLAYER_LEVEL_UP_CHOICE, &mItemPool);
	});
	EM->AddListener(EEventType::PLAYER_LEVEL_UP_SELECT, [this](void* item)
	{
		FSelectableItem* selectedItem = (FSelectableItem*)item;
		switch (selectedItem->category)
		{
		case EItemCategory::POWERUP:
			mScene->GetPlayer()->AddPowerUp((EPowerUpType)selectedItem->type);
			break;
		case EItemCategory::WEAPON:
			mScene->GetPlayer()->AddWeapon((EWeaponType)selectedItem->type);
			break;
		case EItemCategory::CONSUMABLE:
			mScene->GetPlayer()->AddConsumable((EConsumableType)selectedItem->type);
			break;
		}
		mScene->GetPlayer()->GetStatus()->ProcessPendingLevelUp(0.05f);
	});
}