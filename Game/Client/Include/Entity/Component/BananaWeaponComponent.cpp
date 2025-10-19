#include "BananaWeaponComponent.h"
#include "AllComponents.h"
#include "../Object/Player.h"
#include "../Object/Banana.h"
#include "../../Scene/Scene.h"
#include "../../Manager/Data/GameData/GameDataManager.h"
#include "../../Manager/Data/GameData/ItemDataManager.h"

CBananaWeaponComponent::CBananaWeaponComponent()
{
	mWeaponType = EWeaponType::BANANA;
}

CBananaWeaponComponent::~CBananaWeaponComponent()
{
}

bool CBananaWeaponComponent::Init()
{
	mBanana = mObject->GetScene()->InstantiateObject<CBanana, 1>("Smelly_Banana", ELayer::Type::EFFECT);

	return CComponent::Init();
}

void CBananaWeaponComponent::Update(float deltaTime)
{
	CComponent::Update(deltaTime);

	mBanana->GetTransform()->SetWorldPos(mTransform->GetWorldPos());
}

void CBananaWeaponComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CBananaWeaponComponent>(this);
}

void CBananaWeaponComponent::Upgrade()
{
	if (mLevel >= CONST_MAX_WEAPON_LEVEL)
		return;

	mLevel++;

	const FWeaponData& weaponData = 
		CGameDataManager::GetInst()->GetItemDataManager()->GetWeaponData(EWeaponType::BANANA);
	mWeaponAttack = weaponData.levelData[mLevel-1].weaponAttack;
	mProjectile = weaponData.levelData[mLevel-1].projectile;

	mBanana->SetScale(mBanana->GetScale() * 1.08f);
	mBanana->SetDamage(((CPlayer*)mObject)->GetAttack() + mWeaponAttack);
}