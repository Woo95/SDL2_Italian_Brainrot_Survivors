#pragma once

#include "UserWidget.h"

class CResultPanel : public CUserWidget
{
public:
	CResultPanel();
	virtual ~CResultPanel();

protected:
	virtual void Construct() override;
	virtual void Release() override;
};