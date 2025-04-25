#pragma once

#include "UserWidget.h"

class CImage;
class CTextBlock;

class CMoneyHUDWidget : public CUserWidget
{
public:
	CMoneyHUDWidget();
	virtual ~CMoneyHUDWidget();

private:
	CImage* mBackgroundBox;
	CImage* mMoneyIcon;
	CTextBlock* mBalanceText;

protected:
	virtual void Construct() override;
	virtual void Release() override;

public:
	void SetBalance(int balance);
};