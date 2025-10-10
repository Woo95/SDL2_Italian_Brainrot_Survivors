#include "BananaWeaponComponent.h"
#include "../Component/AllComponents.h"
#include "../../Entity/Object/Player.h"
#include "../../Entity/Object/Banana.h"
#include "../../Scene/Scene.h"

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

	switch (mLevel)
	{
	case 1:
		mWeaponAttack += 1.0f;
		break;
	case 2:
		mWeaponAttack += 1.0f;
		mBanana->SetScale(mBanana->GetScale() * 1.08f);
		break;
	case 3:
		mWeaponAttack += 1.0f;
		mBanana->SetScale(mBanana->GetScale() * 1.08f);
		break;
	case 4:
		mWeaponAttack += 2.0f;
		mBanana->SetScale(mBanana->GetScale() * 1.08f);
		break;
	case 5:
		mWeaponAttack += 2.0f;
		mBanana->SetScale(mBanana->GetScale() * 1.08f);
		break;
	case 6:
		mWeaponAttack += 3.0f;
		mBanana->SetScale(mBanana->GetScale() * 1.08f);
		break;
	case 7:
		mWeaponAttack += 3.0f;
		mBanana->SetScale(mBanana->GetScale() * 1.08f);
		break;
	case 8:
		mWeaponAttack += 4.0f;
		mBanana->SetScale(mBanana->GetScale() * 1.075f);
		break;
	default:
		break;
	}
	mBanana->SetDamage(((CPlayer*)mObject)->GetAttack() + mWeaponAttack);
}