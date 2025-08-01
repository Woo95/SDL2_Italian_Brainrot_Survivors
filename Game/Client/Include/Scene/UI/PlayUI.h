#pragma once

#include "SceneUI.h"

class CPlayUI : public CSceneUI
{
public:
	CPlayUI();
	virtual ~CPlayUI();

public:
	virtual bool Init() final;
};