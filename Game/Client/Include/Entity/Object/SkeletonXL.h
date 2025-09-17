#pragma once

#include "Enemy.h"

class CSkeletonXL : public CEnemy
{
public:
	CSkeletonXL();
	virtual ~CSkeletonXL();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};