#pragma once

#include "Object.h"

class CSpriteComponent;
class CRigidbody;

class CBat : public CObject
{
public:
	CBat();
	virtual ~CBat();

private:
	CSpriteComponent* mSprite = nullptr;
	CRigidbody* mRigidbody = nullptr;

	float mDestroyTime = 5.0f;

public:
	virtual bool Init() final;

private:
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

public:
	CRigidbody* GetRigidBody() { return mRigidbody; }

	void SetFlip(SDL_RendererFlip flip);
};