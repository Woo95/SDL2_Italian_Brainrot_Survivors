#include "BatWeaponComponent.h"
#include "AllComponents.h"
#include "../Object/Player.h"
#include "../Object/Bat.h"
#include "../../Scene/Scene.h"
#include "../../Manager/Data/GameData/GameDataManager.h"
#include "../../Manager/Data/GameData/ItemDataManager.h"
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

	const FWeaponData& weaponData = 
		CGameDataManager::GetInst()->GetItemDataManager()->GetWeaponData(EWeaponType::BAT);
	mWeaponAttack = weaponData.levelData[mLevel-1].weaponAttack;
	mProjectile = weaponData.levelData[mLevel-1].projectile;
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