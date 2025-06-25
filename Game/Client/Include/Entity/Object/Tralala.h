#pragma once

#include "Player.h"

class CCollider;

class CTralala : public CPlayer
{
public:
	CTralala();
	virtual ~CTralala();

private:
	CCollider* mFootCollider;

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
	virtual void OnMoveDirChanged(const FVector2D& dir) final;
};