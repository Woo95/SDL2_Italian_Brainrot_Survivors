#pragma once

#include "Object.h"

class CEnemyStatusComponent;
class CSpriteComponent;
class CChaseComponent;
class CRigidbody;

class CEnemy abstract : public CObject
{
public:
	CEnemy();
	virtual ~CEnemy();

protected:
	CEnemyStatusComponent* mStatus;
	CSpriteComponent* mSprite;
	CChaseComponent* mChase;
	CRigidbody* mRigidbody;

public:
	virtual bool Init() override;
	virtual void Update(float deltaTime) override;

private:
	virtual void Release() = 0;

public:
	CChaseComponent* GetChase() const { return mChase; }
};