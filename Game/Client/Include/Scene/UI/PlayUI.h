#pragma once

#include "SceneUI.h"

class CProgressBar;
class CExpBar;
class CKillCounter;
class CTimeHUD;

class CPlayUI : public CSceneUI
{
public:
	CPlayUI();
	virtual ~CPlayUI();

private:
    CProgressBar* mHealthBar = nullptr;
    CExpBar* mExpBar = nullptr;
    CKillCounter* mKillCounter = nullptr;
    CTimeHUD* mTimeHUD = nullptr;

public:
	virtual bool Init() final;

public:
    void SetHealthPercent(float percent);
    void SetExpPercent(float percent);
    void SetPlayerLevel(int level);
    void SetKillCounter(int count);
    void SetGameTime(float seconds);
};