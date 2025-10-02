#pragma once

#include "Scene.h"
#include "../Core/Utils/SceneUtils.h"

class CPlayer;
class CMobSpawner;
class CLevelUpHandler;

class CPlayScene : public CScene
{
	friend class CSceneManager;

private:
	CPlayScene();
	virtual ~CPlayScene();

private:
	EPlaySubState mSubState = EPlaySubState::NONE;

	float mTime = 0.0f;
	CPlayer* mPlayer = nullptr;

	CMobSpawner* mMobSpawner = nullptr;
	CLevelUpHandler* mLevelUpHandler = nullptr;

public:
	virtual bool Enter(void* payload = nullptr) final;
	virtual bool Exit() final;

	virtual void Update(float deltaTime) final;

	virtual void LoadResources() final;

public:
	CPlayer* GetPlayer() const { return mPlayer; }

private:
	void SetSubState(EPlaySubState state);
	CPlayer* InstantiatePlayer();
	void BindEventListeners();
};