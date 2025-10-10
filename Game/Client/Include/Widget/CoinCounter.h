#pragma once

#include "UserWidget.h"

class CImage;
class CTextBlock;

class CCoinCounter : public CUserWidget
{
public:
	CCoinCounter();
	virtual ~CCoinCounter();

private:
	CTextBlock* mCoinCount = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	void SetCountText(int count);
};