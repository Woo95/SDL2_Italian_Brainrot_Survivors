#pragma once

#include "Object.h"

class CSpriteComponent;
class CCollider;

// EnvironmentObject
class CEvnObj : public CObject
{
public:
	CEvnObj();
	virtual ~CEvnObj();

private:
	CSpriteComponent* mSprite;
	CCollider* mCollider;

public:
	virtual bool Init() final;
	virtual void Update(float deltaTime) final;

private:
	virtual void Release() final;

public:
	void SetColliderWorldScale(float x, float y);
	void SetSpriteTexture(const std::string& key);
	void SetSpriteWorldScale(float x, float y);
};