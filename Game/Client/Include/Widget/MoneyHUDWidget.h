#pragma once

#include "UserWidget.h"

class CTextBlock;

class CMoneyHUDWidget : public CUserWidget
{
public:
	CMoneyHUDWidget();
	virtual ~CMoneyHUDWidget();

private:
	CTextBlock* mBalanceText = nullptr;

protected:
	virtual void Construct() override;
	virtual void Release() override;

public:
	void SetBalance(int balance);
};