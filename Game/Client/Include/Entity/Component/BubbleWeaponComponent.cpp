#include "BubbleWeaponComponent.h"
#include "../Component/AllComponents.h"
#include "../../Entity/Object/Player.h"
#include "../../Entity/Object/Bubble.h"
#include "../../Scene/Scene.h"
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

	switch (mLevel)
	{
	case 1:
		mWeaponAttack += 1.0f;
		mProjectile += 1;
		break;
	case 2:
		mWeaponAttack += 1.0f;
		break;
	case 3:
		mWeaponAttack += 1.0f;
		mProjectile += 1;
		break;
	case 4:
		mWeaponAttack += 2.0f;
		break;
	case 5: 
		mWeaponAttack += 2.0f;
		mProjectile += 1; 
		break;
	case 6:
		mWeaponAttack += 3.0f;
		break;
	case 7:
		mWeaponAttack += 3.0f;
		break;
	case 8:
		mWeaponAttack += 4.0f;
		mProjectile += 2;
		break;
	default:
		break;
	}
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