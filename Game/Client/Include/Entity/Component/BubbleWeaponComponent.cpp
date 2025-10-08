#include "BubbleWeaponComponent.h"
#include "../Component/AllComponents.h"
#include "../../Entity/Object/Player.h"
#include "../../Entity/Object/Bubble.h"
#include "../../Scene/Scene.h"

CBubbleWeaponComponent::CBubbleWeaponComponent()
{
	mWeaponType = EWeaponType::BUBBLE;

	mShootDirs[0] = FVector2D(1.f, 0.f);
	mShootDirs[1] = FVector2D(-1.f, 0.f);
	mShootDirs[2] = FVector2D(0.f, 1.f);
	mShootDirs[3] = FVector2D(0.f, -1.f);
	mShootDirs[4] = FVector2D(0.707f, 0.707f);
	mShootDirs[5] = FVector2D(-0.707f, -0.707f);
	mShootDirs[6] = FVector2D(-0.707f, 0.707f);
	mShootDirs[7] = FVector2D(0.707f, -0.707f);

	mCooldownTimer = CONST_COOLDOWN_TIMER;
}

CBubbleWeaponComponent::~CBubbleWeaponComponent()
{
}

bool CBubbleWeaponComponent::Init()
{
	return CComponent::Init();
}

void CBubbleWeaponComponent::Update(float deltaTime)
{
	CComponent::Update(deltaTime);

	mCooldownTimer -= deltaTime;
	if (mCooldownTimer <= 0.0f)
	{
		for (int i = 0; i < mProjectile; i++)
		{
			Attack(mShootDirs[i]);
		}
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
		mProjectile += 2;
		break;
	case 2: mWeaponAttack += 1.0f; break;
	case 3:
		mWeaponAttack += 1.0f;
		mProjectile += 2;
		break;
	case 4:
		mWeaponAttack += 2.0f;
		break;
	case 5: 
		mWeaponAttack += 2.0f;
		mProjectile += 2; 
		break;
	case 6: mWeaponAttack += 3.0f; break;
	case 7: mWeaponAttack += 3.0f; break;
	case 8:
		mWeaponAttack += 4.0f;
		mProjectile += 2;
		break;
	default: break;
	}
}

void CBubbleWeaponComponent::Attack(const FVector2D& dir)
{
	CBubble* bubble = mObject->GetScene()->InstantiateObject<CBubble, 5>("Bullet_Bubble", ELayer::Type::EFFECT);

	bubble->GetTransform()->SetWorldPos(mObject->GetTransform()->GetWorldPos());

	bubble->SetMoveDir(dir);
}