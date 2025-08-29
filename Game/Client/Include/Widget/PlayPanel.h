#pragma once

#include "UserWidget.h"

class CProgressBar;
class CExpBar;
class CKillCounter;
class CTimeHUD;

class CPlayPanel : public CUserWidget
{
public:
	CPlayPanel();
	virtual ~CPlayPanel();

private:
	CProgressBar* mHealthBar   = nullptr;
	CExpBar*      mExpBar      = nullptr;
	CKillCounter* mKillCounter = nullptr;
	CTimeHUD*     mTimeHUD     = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	void SetHealthPercent(float percent);
	void SetExpPercent(float percent);
	void SetPlayerLevel(int level);
	void SetKillCounter(int count);
	void SetGameTime(float seconds);
};