#pragma once

#include "SceneUI.h"

class CPauseUI : public CSceneUI
{
public:
	CPauseUI();
	virtual ~CPauseUI();

public:
	virtual bool Init() final;
};