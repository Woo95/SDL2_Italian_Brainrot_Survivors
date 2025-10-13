#include "BatWeaponComponent.h"
#include "../Component/AllComponents.h"
#include "../../Entity/Object/Player.h"
#include "../../Entity/Object/Bat.h"
#include "../../Scene/Scene.h"
#include "../../Manager/Data/Resource/AssetManager.h"
#include "../../Manager/Data/Resource/SoundManager.h"

CBatWeaponComponent::CBatWeaponComponent()
{
	mWeaponType = EWeaponType::BAT;

	mCooldownTimer = CONST_COOLDOWN_TIMER;
}

CBatWeaponComponent::~CBatWeaponComponent()
{
}

void CBatWeaponComponent::Update(float deltaTime)
{
	CComponent::Update(deltaTime);

	mCooldownTimer -= deltaTime;
	if (mCooldownTimer <= 0.0f)
	{
		Attack();
		mCooldownTimer = CONST_COOLDOWN_TIMER;
		mFiredProjectile = 0;
		mProjectileTimer = 0.0f;
	}

	if (mFiredProjectile < mProjectile)
	{
		mProjectileTimer -= deltaTime;
		if (mProjectileTimer <= 0.0f)
		{
			Attack();
			mFiredProjectile++;
			mProjectileTimer = CONST_PROJECTILE_TIMER;
		}
	}
}

void CBatWeaponComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CBatWeaponComponent>(this);
}

void CBatWeaponComponent::Upgrade()
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
		mWeaponAttack += 2.0f;
		break;
	case 3:
		mWeaponAttack += 3.0f;
		mProjectile += 1;
		break;
	case 4:
		mWeaponAttack += 2.0f;
		break;
	case 5:
		mWeaponAttack += 3.0f;
		mProjectile += 1;
		break;
	case 6:
		mWeaponAttack += 4.0f;
		break;
	case 7:
		mWeaponAttack += 4.0f;
		break;
	case 8:
		mWeaponAttack += 5.0f;
		mProjectile += 1;
		break;
	default:
		break;
	}
}

void CBatWeaponComponent::Attack()
{
	CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_Bat")->Play();

	CBat* bat = mObject->GetScene()->InstantiateObject<CBat, 4>("Swing_Bat", ELayer::Type::EFFECT);
	bat->SetDamage(((CPlayer*)mObject)->GetAttack() + mWeaponAttack);

	CPlayer* player = (CPlayer*)mObject;
	FVector2D moveDir = player->GetMovement()->GetCurrMoveDir();

	bat->GetTransform()->SetWorldPos(player->GetTransform()->GetWorldPos());
	bat->SetFlip(player->GetSprite()->GetFlip());

	if (moveDir.x < 0.0f)
	{
		moveDir.x = -40000.0f;
	}
	else if (moveDir.x > 0.0f)
	{
		moveDir.x = 40000.0f;
	}

	if (moveDir.y == 0.0f) moveDir.y = -50000.0f;
	else if (moveDir.y < 0.0f) moveDir.y *= 85000.0f;
	else if (moveDir.y > 0.0f) moveDir.y *= -25000.0f;

	bat->GetRigidBody()->AddImpulse(moveDir);
}