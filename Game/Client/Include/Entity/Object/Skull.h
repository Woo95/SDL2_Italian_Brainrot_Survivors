#pragma once

#include "Enemy.h"

class CSkull : public CEnemy
{
public:
	CSkull();
	virtual ~CSkull();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};