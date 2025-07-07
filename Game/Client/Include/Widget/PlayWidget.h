#pragma once

#include "UserWidget.h"

class CButton;

class CPlayWidget : public CUserWidget
{
public:
	CPlayWidget();
	virtual ~CPlayWidget();

protected:
	virtual void Construct() override;
	virtual void Release() override;
};