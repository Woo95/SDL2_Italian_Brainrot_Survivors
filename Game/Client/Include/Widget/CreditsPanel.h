#pragma once

#include "UserWidget.h"

class CCreditsPanel : public CUserWidget
{
public:
	CCreditsPanel();
	virtual ~CCreditsPanel();

protected:
	virtual void Construct() final;
	virtual void Release() final;
};