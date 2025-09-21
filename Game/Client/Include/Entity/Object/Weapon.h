#pragma once

#include "Object.h"
#include "../../Core/Utils/GameDataUtils.h"

class CSpriteComponent;
class CVFXComponent;

class CWeapon abstract : public CObject
{
public:
	CWeapon() = default;
	virtual ~CWeapon() = default;

protected:
	EWeaponType mWeaponType = EWeaponType::NONE;
	int mLevel = 0;

	CSpriteComponent* mSprite = nullptr;
	CVFXComponent* mVFX = nullptr;

public:
	virtual void AddWeaponLevel() = 0;

private:
	virtual void Release() = 0;

public:
	const EWeaponType& GetWeaponType() const { return mWeaponType; }
	int GetWeaponLevel() const { return mLevel; }
};