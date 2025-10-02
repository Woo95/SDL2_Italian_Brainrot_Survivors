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

	std::vector<FItem> mItemPool;
	
private:
	bool Init();

private:
	void CreateItemPool();

	void BindEventListener();
	void HandlePowerUp(EPowerUpType type);
	void HandleWeapon(EWeaponType type);
	void HandleConsumable(EConsumableType type);
};