#pragma once

#include "Enemy.h"

class CSkeleton : public CEnemy
{
public:
	CSkeleton();
	virtual ~CSkeleton();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};