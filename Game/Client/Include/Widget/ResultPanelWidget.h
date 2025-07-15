#pragma once

#include "UserWidget.h"

class CResultPanelWidget : public CUserWidget
{
public:
	CResultPanelWidget();
	virtual ~CResultPanelWidget();

protected:
	virtual void Construct() override;
	virtual void Release() override;
};