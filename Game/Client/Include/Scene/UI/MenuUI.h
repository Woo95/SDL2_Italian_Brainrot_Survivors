#pragma once

#include "SceneUI.h"

class CMenuUI : public CSceneUI
{
public:
	CMenuUI();
	virtual ~CMenuUI();

public:
	virtual bool Init() override;
};