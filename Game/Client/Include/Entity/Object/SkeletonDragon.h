#pragma once

#include "Enemy.h"

class CSkeletonDragon : public CEnemy
{
public:
	CSkeletonDragon();
	virtual ~CSkeletonDragon();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};