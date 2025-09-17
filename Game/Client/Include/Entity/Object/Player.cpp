#include "Player.h"
#include "../Component/AllComponents.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/EventManager.h"

CPlayer::CPlayer() :
	mStatus(nullptr),
	mInventory(nullptr),
	mMovement(nullptr),
	mSprite(nullptr),
	mRigidbody(nullptr),
	mInput(nullptr)
{
}

CPlayer::~CPlayer()
{
	BindEventListeners();

	mInput->DeleteFunctionFromBinder("W_MoveUp",    this);
	mInput->DeleteFunctionFromBinder("A_MoveLeft",  this);
	mInput->DeleteFunctionFromBinder("S_MoveDown",  this);
	mInput->DeleteFunctionFromBinder("D_MoveRight", this);

	mInput->DeleteFunctionFromBinder("UP_MoveUp",       this);
	mInput->DeleteFunctionFromBinder("DOWN_MoveDown",   this);
	mInput->DeleteFunctionFromBinder("LEFT_MoveLeft",   this);
	mInput->DeleteFunctionFromBinder("RIGHT_MoveRight", this);
}

bool CPlayer::Init()
{
	mStatus = AllocateComponent<CPlayerStatusComponent, 1>("Status_Player");
	mRootComponent->AddChild(mStatus);

	mInventory = AllocateComponent<CInventoryComponent, 1>("Inventory_Player");
	mRootComponent->AddChild(mInventory);

	mMovement = AllocateComponent<CMovementComponent, 1>("Movement_Player");
	mRootComponent->AddChild(mMovement);

	mRigidbody = AllocateComponent<CRigidbody, 50>("Rigidbody_Player");
	mRootComponent->AddChild(mRigidbody);

	BindInput();

	return CObject::Init();
}

void CPlayer::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CPlayer>(this);
}

std::vector<FItem> CPlayer::GetLevelUpPool() const
{
	std::vector<FItem> pool;
	// 가능한 파워업을 옵션에 추가
	for (int i = 0; i < (int)EPowerUpType::MAX; i++)
	{
		EPowerUpType type = static_cast<EPowerUpType>(i);
		int level = mInventory->GetPowerUpLevel(type);
		if (level >= CONST_MAX_POWERUP_LEVEL)
			continue;

		if (mInventory->HasEmptySlot(EItemCategory::POWERUP) || (mInventory->HasItem(EItemCategory::POWERUP, (int)type) && level < CONST_MAX_POWERUP_LEVEL))
		{
			pool.emplace_back(EItemCategory::POWERUP, (signed char)type, level);
		}
	}
	// 가능한 무기를 옵션에 추가
	for (int i = 0; i < (int)EWeaponType::MAX; i++)
	{
		EWeaponType type = static_cast<EWeaponType>(i);
		int level = mInventory->GetWeaponLevel(type);
		if (level >= CONST_MAX_WEAPON_LEVEL)
			continue;

		if (mInventory->HasEmptySlot(EItemCategory::WEAPON) || (mInventory->HasItem(EItemCategory::WEAPON, (int)type) && level < CONST_MAX_WEAPON_LEVEL))
		{
			pool.emplace_back(EItemCategory::WEAPON, (signed char)type, level);
		}
	}
	// 옵션 섞기
	for (int i = 0; i < pool.size(); i++)
	{
		int randIdx = std::rand() % pool.size();
		std::swap(pool[i], pool[randIdx]);
	}

	// 선택 옵션이 없을 경우
	if (pool.empty())
	{
		pool.emplace_back(EItemCategory::CONSUMABLE, 0, 0);
		pool.emplace_back(EItemCategory::CONSUMABLE, 1, 0);
	}

	return pool;
}

void CPlayer::BindInput()
{
	mInput = AllocateComponent<CInputComponent, 1>("Input_Player");

	mInput->AddFunctionToBinder("W_MoveUp",    this, [this]() { MoveDir(FVector2D::UP);    });
	mInput->AddFunctionToBinder("A_MoveLeft",  this, [this]() { MoveDir(FVector2D::LEFT);  });
	mInput->AddFunctionToBinder("S_MoveDown",  this, [this]() { MoveDir(FVector2D::DOWN);  });
	mInput->AddFunctionToBinder("D_MoveRight", this, [this]() { MoveDir(FVector2D::RIGHT); });

	mInput->AddInputToBinder("W_MoveUp",    SDL_SCANCODE_W, EKeyAction::HOLD);
	mInput->AddInputToBinder("A_MoveLeft",  SDL_SCANCODE_A, EKeyAction::HOLD);
	mInput->AddInputToBinder("S_MoveDown",  SDL_SCANCODE_S, EKeyAction::HOLD);
	mInput->AddInputToBinder("D_MoveRight", SDL_SCANCODE_D, EKeyAction::HOLD);


	mInput->AddFunctionToBinder("UP_MoveUp",       this, [this]() { MoveDir(FVector2D::UP);    });
	mInput->AddFunctionToBinder("DOWN_MoveDown",   this, [this]() { MoveDir(FVector2D::DOWN);  });
	mInput->AddFunctionToBinder("LEFT_MoveLeft",   this, [this]() { MoveDir(FVector2D::LEFT);  });
	mInput->AddFunctionToBinder("RIGHT_MoveRight", this, [this]() { MoveDir(FVector2D::RIGHT); });

	mInput->AddInputToBinder("UP_MoveUp",       SDL_SCANCODE_UP,    EKeyAction::HOLD);
	mInput->AddInputToBinder("DOWN_MoveDown",   SDL_SCANCODE_DOWN,  EKeyAction::HOLD);
	mInput->AddInputToBinder("LEFT_MoveLeft",   SDL_SCANCODE_LEFT,  EKeyAction::HOLD);
	mInput->AddInputToBinder("RIGHT_MoveRight", SDL_SCANCODE_RIGHT, EKeyAction::HOLD);

	mRootComponent->AddChild(mInput);
}

void CPlayer::MoveDir(const FVector2D& dir)
{
	mMovement->AddMoveDir(dir);

	OnMoveDirChanged(dir);
}

float CPlayer::GetAttack() const
{
	int itemLevel = mStatus->GetMenuPowerUpLvl(EPowerUpType::MIGHT) + mInventory->GetPowerUpLevel(EPowerUpType::MIGHT);
	const float itemAttack = mStatus->GetBaseAttack() * itemLevel * mStatus->GetStatModifier(EPowerUpType::MIGHT);

	return mStatus->GetBaseAttack() + itemAttack;
}

float CPlayer::GetDefense() const
{
	int itemLevel = mStatus->GetMenuPowerUpLvl(EPowerUpType::ARMOR) + mInventory->GetPowerUpLevel(EPowerUpType::ARMOR);
	const float itemArmor = itemLevel * mStatus->GetStatModifier(EPowerUpType::ARMOR);

	return mStatus->GetBaseDefense() + itemArmor;
}

float CPlayer::GetMaxHP() const
{
	int itemLevel = mStatus->GetMenuPowerUpLvl(EPowerUpType::MAX_HEALTH) + mInventory->GetPowerUpLevel(EPowerUpType::MAX_HEALTH);
	const float itemMaxHP = mStatus->GetBaseMaxHP() * itemLevel * mStatus->GetStatModifier(EPowerUpType::MAX_HEALTH);

	return mStatus->GetBaseMaxHP() + itemMaxHP;
}

float CPlayer::GetRecoveryHP() const
{
	int itemLevel = mStatus->GetMenuPowerUpLvl(EPowerUpType::RECOVERY) + mInventory->GetPowerUpLevel(EPowerUpType::RECOVERY);
	const float itemRecovery = itemLevel * mStatus->GetStatModifier(EPowerUpType::RECOVERY);

	return itemRecovery;
}

float CPlayer::GetAttackSpeed() const
{
	int itemLevel = mStatus->GetMenuPowerUpLvl(EPowerUpType::ATTACK_SPEED) + mInventory->GetPowerUpLevel(EPowerUpType::ATTACK_SPEED);
	const float itemAttackSpeed = mStatus->GetBaseAttackSpeed() * itemLevel * mStatus->GetStatModifier(EPowerUpType::ATTACK_SPEED);

	return mStatus->GetBaseAttackSpeed() + itemAttackSpeed;
}

float CPlayer::GetMoveSpeed() const
{
	int itemLevel = mStatus->GetMenuPowerUpLvl(EPowerUpType::MOVE_SPEED) + mInventory->GetPowerUpLevel(EPowerUpType::MOVE_SPEED);
	const float itemMoveSpeed = mStatus->GetBaseMoveSpeed() * itemLevel * mStatus->GetStatModifier(EPowerUpType::MOVE_SPEED);

	return mStatus->GetBaseMoveSpeed() + itemMoveSpeed;
}

float CPlayer::GetPickupRange() const
{
	int itemLevel = mStatus->GetMenuPowerUpLvl(EPowerUpType::MAGNET) + mInventory->GetPowerUpLevel(EPowerUpType::MAGNET);
	const float itemPickupRange = mStatus->GetBasePickupRange() * itemLevel * mStatus->GetStatModifier(EPowerUpType::MAGNET);

	return mStatus->GetBasePickupRange() + itemPickupRange;
}

float CPlayer::GetGrwothExp() const
{
	int itemLevel = mStatus->GetMenuPowerUpLvl(EPowerUpType::GROWTH) + mInventory->GetPowerUpLevel(EPowerUpType::GROWTH);
	const float itemGrowth = itemLevel * mStatus->GetStatModifier(EPowerUpType::GROWTH);

	return mStatus->GetBaseGrowthExp() + itemGrowth;
}

void CPlayer::BindEventListeners()
{
	CEventManager* EM = CEventManager::GetInst();

	EM->AddListener(EEventType::PLAYER_LEVEL_UP_SELECTED, [this](void* item)
	{
		FItem selectedItem = *(FItem*)item;
		switch (selectedItem.category)
		{
		case EItemCategory::POWERUP:
			mInventory->AddPowerUp((EPowerUpType)selectedItem.type);
			break;
		case EItemCategory::WEAPON:
			mInventory->AddWeapon((EWeaponType)selectedItem.type);
			break;
		case EItemCategory::CONSUMABLE:
			if ((EConsumableType)selectedItem.type == EConsumableType::COIN_BAG)
			{
				mStatus->AddGold(100);
			}
			else if ((EConsumableType)selectedItem.type == EConsumableType::CHICKEN)
			{
				mStatus->AddHP(50);
			}
			break;
		}
		mStatus->ProcessPendingLevelUp(0.05f);
	});
}