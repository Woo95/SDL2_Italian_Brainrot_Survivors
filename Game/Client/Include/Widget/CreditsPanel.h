#pragma once

#include "UserWidget.h"

class CCreditsPanel : public CUserWidget
{
public:
	CCreditsPanel();
	virtual ~CCreditsPanel();

protected:
	virtual void Construct() override;
	virtual void Release() override;
};