#pragma once

#include "UserWidget.h"

class CResultPanel : public CUserWidget
{
public:
	CResultPanel();
	virtual ~CResultPanel();

protected:
	virtual void Construct() final;
	virtual void Release() final;
};