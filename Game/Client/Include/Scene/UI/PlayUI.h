#pragma once

#include "SceneUI.h"

class CPlayWidget;

class CPlayUI : public CSceneUI
{
public:
	CPlayUI();
	virtual ~CPlayUI();

private:
	CPlayWidget* mPlay = nullptr;

public:
	virtual bool Init() override;
};