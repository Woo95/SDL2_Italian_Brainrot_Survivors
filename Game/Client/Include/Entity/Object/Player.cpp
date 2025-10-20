#include "Player.h"
#include "AllObjects.h"
#include "../Component/AllComponents.h"
#include "../../Manager/InputManager.h"
#include "../../Resource/Animation.h"
#include "../../Manager/Data/Resource/AssetManager.h"
#include "../../Manager/Data/Resource/SoundManager.h"

CPlayer::CPlayer()
{
	mHealTimer = CONST_HEAL_TIMER;
}

CPlayer::~CPlayer()
{
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
	mMovement = AllocateComponent<CMovementComponent, 1>("Movement_Player");
	mRootComponent->AddChild(mMovement);

	mHitVfx = AllocateComponent<CVFXComponent, 50>("VFX_Player");
	mHitVfx->SetTexture("Texture_VfxAtlas");
	mHitVfx->SetAnimation("PlayerHitVFX");
	mHitVfx->GetAnimation()->SetState(EAnimationState::VFX);
	mHitVfx->GetTransform()->SetWorldScale(35.f, 45.0f);
	mHitVfx->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mHitVfx);

	mRigidbody = AllocateComponent<CRigidbody, 50>("Rigidbody_Player");
	mRootComponent->AddChild(mRigidbody);

	mPickUpZone = AllocateComponent<CCircleCollider>("Collider_PickUpZone");
	mPickUpZone->SetProfile("PlayerItemDetector");
	mPickUpZone->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mPickUpZone);

	mInput = AllocateComponent<CInputComponent, 1>("Input_Player");
	mRootComponent->AddChild(mInput);

	BindInput();

	mMovement->SetSpeed(GetMoveSpeed());
	mStatus->SetMaxHP(GetMaxHP());
	mStatus->SetHP(GetMaxHP());
	mPickUpZone->GetTransform()->SetWorldScale(FVector2D(GetPickupRange(), GetPickupRange()));

	return CObject::Init();
}

void CPlayer::Update(float deltaTime)
{
	CObject::Update(deltaTime);

	mHealTimer -= deltaTime;
	if (mHealTimer <= 0.0f)
	{
		mHealTimer = CONST_HEAL_TIMER;
		Heal(GetRecoveryHP());
	}
}

void CPlayer::TakeDamage(float amount)
{
	if (!CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PlayerHit")->IsPlaying())
		CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PlayerHit")->Play();

	mHitVfx->PlayVFX(mHitbox->GetHitPoint());

	float damage = std::max(0.0f, amount * GetDefense());
	mStatus->AddHP(-damage);
}

void CPlayer::Heal(float amount)
{
	mStatus->AddHP(amount);
}

void CPlayer::AddExp(float exp)
{
	mStatus->AddExp(exp * GetGrowthExp());
}

void CPlayer::AddKill()
{
	mStatus->AddKill();
}

void CPlayer::AddGold(int money)
{
	mStatus->AddGold((int)(money * GetGreed()));
}

void CPlayer::AddPowerUp(EPowerUpType type)
{
	mInventory->AddPowerUp(type);

	switch (type)
	{
	case EPowerUpType::MAX_HEALTH:
		mStatus->SetMaxHP(GetMaxHP());
		break;
	case EPowerUpType::MOVE_SPEED:
		mMovement->SetSpeed(GetMoveSpeed());
		break;
	case EPowerUpType::MAGNET:
		mPickUpZone->GetTransform()->SetWorldScale(FVector2D(GetPickupRange(), GetPickupRange()));
		break;
	default:
		break;
	}
}

void CPlayer::AddWeapon(EWeaponType type)
{
	FWeapon* weapon = mInventory->GetWeapon(type);
	if (!weapon)
	{
		CWeaponComponent* weaponComponent = nullptr;
		switch (type)
		{
		case EWeaponType::BUBBLE:
			weaponComponent = AllocateComponent<CBubbleWeaponComponent, 1>("BubbleWeapon_Tralala");
			break;
		case EWeaponType::BAT:
			weaponComponent = AllocateComponent<CBatWeaponComponent, 1>("BatWeapon_Sahur");
			break;
		case EWeaponType::BANANA:
			weaponComponent = AllocateComponent<CBananaWeaponComponent, 1>("BananaWeapon_Bananini");
			break;
		}
		mRootComponent->AddChild(weaponComponent);
		weaponComponent->Init();
		mInventory->AddWeapon(type, weaponComponent);
	}
	else
	{
		mInventory->AddWeapon(type, weapon->ptr);
	}
	
}

void CPlayer::AddConsumable(EConsumableType type)
{
	switch (type)
	{
	case EConsumableType::COIN_BAG:
		AddGold(100);
		break;
	case EConsumableType::CHICKEN:
		Heal(50.0f);
		break;
	}
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
	const float itemArmor = 1.0f - itemLevel * mStatus->GetStatModifier(EPowerUpType::ARMOR);

	return itemArmor;
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

float CPlayer::GetMoveSpeed() const
{
	int itemLevel = mStatus->GetMenuPowerUpLvl(EPowerUpType::MOVE_SPEED) + mInventory->GetPowerUpLevel(EPowerUpType::MOVE_SPEED);
	const float itemMoveSpeed = mStatus->GetBaseMoveSpeed() * itemLevel * mStatus->GetStatModifier(EPowerUpType::MOVE_SPEED);

	return mStatus->GetBaseMoveSpeed() + itemMoveSpeed;
}

float CPlayer::GetPickupRange() const
{
	int itemLevel = mStatus->GetMenuPowerUpLvl(EPowerUpType::MAGNET) + mInventory->GetPowerUpLevel(EPowerUpType::MAGNET);
	const float itemPickupRange = mStatus->GetBasePickUpRange() * itemLevel * mStatus->GetStatModifier(EPowerUpType::MAGNET);

	return mStatus->GetBasePickUpRange() + itemPickupRange;
}

float CPlayer::GetGrowthExp() const
{
	int itemLevel = mStatus->GetMenuPowerUpLvl(EPowerUpType::GROWTH) + mInventory->GetPowerUpLevel(EPowerUpType::GROWTH);
	const float itemGrowth = 1 + itemLevel * mStatus->GetStatModifier(EPowerUpType::GROWTH);

	return itemGrowth;
}

float CPlayer::GetGreed() const
{
	int itemLevel = mStatus->GetMenuPowerUpLvl(EPowerUpType::GREED) + mInventory->GetPowerUpLevel(EPowerUpType::GREED);
	const float itemGreed = 1 + itemLevel * mStatus->GetStatModifier(EPowerUpType::GREED);

	return itemGreed;
}

void CPlayer::BindInput()
{
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
}

void CPlayer::MoveDir(const FVector2D& dir)
{
	mMovement->AddMoveDir(dir);

	OnMoveDirChanged(dir);
}