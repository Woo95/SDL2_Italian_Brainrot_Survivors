#include "BubbleWeaponComponent.h"
#include "AllComponents.h"
#include "../Object/Player.h"
#include "../Object/Bubble.h"
#include "../../Scene/Scene.h"
#include "../../Manager/Data/GameData/GameDataManager.h"
#include "../../Manager/Data/GameData/ItemDataManager.h"
#include "../../Manager/Data/Resource/AssetManager.h"
#include "../../Manager/Data/Resource/SoundManager.h"

CBubbleWeaponComponent::CBubbleWeaponComponent()
{
	mWeaponType = EWeaponType::BUBBLE;

	mCooldownTimer = CONST_COOLDOWN_TIMER;

	mShootDirs[0] = FVector2D(1.f, 0.f);
	mShootDirs[1] = FVector2D(0.924f, -0.383f);
	mShootDirs[2] = FVector2D(0.924f, 0.383f);
	mShootDirs[3] = FVector2D(0.707f, -0.707f);
	mShootDirs[4] = FVector2D(0.707f, 0.707f);
}

CBubbleWeaponComponent::~CBubbleWeaponComponent()
{
}

void CBubbleWeaponComponent::Update(float deltaTime)
{
	CComponent::Update(deltaTime);

	mCooldownTimer -= deltaTime;
	if (mCooldownTimer <= 0.0f)
	{
		Attack();
		mCooldownTimer = CONST_COOLDOWN_TIMER;
	}
}

void CBubbleWeaponComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CBubbleWeaponComponent>(this);
}

void CBubbleWeaponComponent::Upgrade()
{
	if (mLevel >= CONST_MAX_WEAPON_LEVEL)
		return;

	mLevel++;

	const FWeaponData& weaponData =
		CGameDataManager::GetInst()->GetItemDataManager()->GetWeaponData(EWeaponType::BUBBLE);
	mWeaponAttack = weaponData.levelData[mLevel-1].weaponAttack;
	mProjectile = weaponData.levelData[mLevel-1].projectile;
}

void CBubbleWeaponComponent::Attack()
{
	CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_Bubble")->Play();

	for (int i = 0; i < mProjectile; i++)
	{
		FVector2D dir = mShootDirs[i];

		if (((CPlayer*)mObject)->GetSprite()->GetFlip() != SDL_FLIP_HORIZONTAL)
			dir.x *= -1;

		CBubble* bubble = mObject->GetScene()->InstantiateObject<CBubble, 20>("Bullet_Bubble", ELayer::Type::EFFECT);
		bubble->SetDamage(((CPlayer*)mObject)->GetAttack() + mWeaponAttack);
		bubble->GetTransform()->SetWorldPos(mObject->GetTransform()->GetWorldPos());
		bubble->SetMoveDir(dir);
	}
}