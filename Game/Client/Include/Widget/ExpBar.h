#pragma once

#include "UserWidget.h"

class CImage;
class CProgressBar;
class CTextBlock;

class CExpBar : public CUserWidget
{
public:
	CExpBar();
	virtual ~CExpBar();

private:
	CImage* mFrame;
	CProgressBar* mExpProgress;
	CTextBlock* mLevel;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	CProgressBar* GetExpProgressBar() const { return mExpProgress; }
	CTextBlock* GetLevelTextBlock() const { return mLevel; }
};