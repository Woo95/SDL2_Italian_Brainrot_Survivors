#pragma once

#include "Object.h"

class CChaseComponent;
class CSpriteComponent;

class CEnemy abstract : public CObject
{
public:
	CEnemy();
	virtual ~CEnemy();

protected:
	CChaseComponent* mChase;
	CSpriteComponent* mSprite;

public:
	virtual bool Init() override;
	virtual void Update(float deltaTime) override;

private:
	virtual void Release() = 0;

public:
	CChaseComponent* GetChase() const { return mChase; }
};