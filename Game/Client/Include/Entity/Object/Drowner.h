#pragma once

#include "Enemy.h"

class CDrowner : public CEnemy
{
public:
	CDrowner();
	virtual ~CDrowner();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};