#pragma once

#include "UserWidget.h"

class CImage;
class CTextBlock;

class CKillCounter : public CUserWidget
{
public:
	CKillCounter();
	virtual ~CKillCounter();

private:
	CTextBlock* mKillCount;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	CTextBlock* GetKillCountTextBlock() const { return mKillCount; }
};