#pragma once

#include "GameInfo.h"

class CDataLoader
{
	friend class CGameManager;

private:
	CDataLoader();
	~CDataLoader();

private:
	bool Init();

	std::vector<std::string> Split(const std::string& line, char delimiter);

	void LoadAllEntityFrameData();
	void LoadAllEntityAnimationData();
	void LoadAllWidgetData();

	void LoadAllCharacterInfo();
};