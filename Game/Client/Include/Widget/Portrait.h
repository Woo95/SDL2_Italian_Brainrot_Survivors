#pragma once

#include "UserWidget.h"

class CImage;
class CProgressBar;
class CTextBlock;

class CPortrait : public CUserWidget
{
public:
	CPortrait();
	virtual ~CPortrait();

private:
	CImage* mFrame;
	CImage* mPortrait;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	void SetPortrait(const std::string& portrait);
};