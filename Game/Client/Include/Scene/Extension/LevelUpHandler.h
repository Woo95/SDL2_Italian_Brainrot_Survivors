#pragma once

#include "../../Core/GameInfo.h"
#include "../../Core/Utils/GameDataUtils.h"

class CPlayScene;

class CLevelUpHandler
{
	friend class CPlayScene;

private:
	CLevelUpHandler() = delete;
	CLevelUpHandler(CPlayScene* scene);
	~CLevelUpHandler();

private:
	CPlayScene* mScene = nullptr;

	std::vector<FSelectableItem> mItemPool;

private:
	bool Init();

private:
	void CreateItemPool();

	void BindEventListener();
};