#pragma once

#include "UserWidget.h"

class CTextBlock;

class CTimeHUD : public CUserWidget
{
public:
	CTimeHUD();
	virtual ~CTimeHUD();

private:
	CTextBlock* mTimer = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	void SetTimeText(float totalSeconds);
};