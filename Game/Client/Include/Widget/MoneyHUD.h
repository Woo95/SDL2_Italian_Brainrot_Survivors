#pragma once

#include "UserWidget.h"

class CTextBlock;

class CMoneyHUD : public CUserWidget
{
public:
	CMoneyHUD();
	virtual ~CMoneyHUD();

private:
	CTextBlock* mBalance = nullptr;

protected:
	virtual void Construct() override;
	virtual void Release() override;

public:
	void SetBalance(int balance);
};