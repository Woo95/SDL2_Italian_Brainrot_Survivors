#pragma once

#include "Enemy.h"

class CSkeletonPanther : public CEnemy
{
public:
	CSkeletonPanther();
	virtual ~CSkeletonPanther();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};