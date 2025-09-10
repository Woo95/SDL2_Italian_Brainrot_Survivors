#pragma once

#include "Scene.h"
#include "../Core/Utils/SceneUtils.h"

class CMobSpawner;
class CPlayer;

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

public:
	virtual bool Enter() final;
	virtual bool Exit()  final;

	virtual void Update(float deltaTime) final;

	virtual void LoadResources() final;

public:
	void SetSubState(EPlaySubState state);

private:
	CPlayer* InstantiatePlayer();
	void BindEventListeners();
};