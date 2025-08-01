#pragma once

#include "SceneUI.h"

class CProgressBar;
class CExpBar;
class CKillCounter;

class CPlayUI : public CSceneUI
{
public:
	CPlayUI();
	virtual ~CPlayUI();

private:
    CProgressBar* mHealthBar = nullptr;
    CExpBar* mExpBar = nullptr;
    CKillCounter* mKillCounter = nullptr;

public:
	virtual bool Init() final;

public:
    void SetHealthPercent(float percent);
    void SetExpPercent(float percent);
    void SetLevel(int level);
    void SetKillCount(int count);
};