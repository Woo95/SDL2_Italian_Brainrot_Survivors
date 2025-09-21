#include "BatWeapon.h"
#include "../Component/AllComponents.h"

CBatWeapon::CBatWeapon() :
	mProjectile(1),
	mCooldown(1.0f),
	mWeaponAttack(1.0f),
	mWeaponRange(1.0f)
{
	mWeaponType = EWeaponType::BAT;
}

CBatWeapon::~CBatWeapon()
{
}

bool CBatWeapon::Init()
{
	//mSprite = AllocateComponent<CSpriteComponent>("Sprite_Sahur");
	//mSprite->SetTexture("Texture_Sahur");
	//mSprite->SetAnimation("Sahur");
	//mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	//mSprite->GetTransform()->SetWorldScale(FVector2D(38.0f, 45.0f) * 1.5f);
	//mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	//mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
	//mRootComponent->AddChild(mSprite);


	return CObject::Init();
}

void CBatWeapon::Update(float deltaTime)
{
	// TODO
}

void CBatWeapon::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CBatWeapon>(this);
}

void CBatWeapon::AddWeaponLevel()
{
	if (mLevel < CONST_MAX_WEAPON_LEVEL)
		mLevel++;

	switch (mLevel)
	{
	case 2:
		mProjectile += 1;
		break;
	case 3:
		mWeaponAttack += 1;
		break;
	case 4:
		mWeaponAttack += 2;
		mWeaponRange *= 1.1f;
		break;
	case 5:
		mWeaponAttack += 3;
		break;
	case 6:
		mWeaponAttack += 4;
		mWeaponRange *= 1.1f;
		break;
	case 7:
		mWeaponAttack += 5;
		break;
	case 8:
		mProjectile += 5;
		break;
	default:
		break;
	}
}