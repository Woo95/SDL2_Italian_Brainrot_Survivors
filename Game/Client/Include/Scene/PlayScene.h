#pragma once

#include "Scene.h"
#include "../Core/Utils/SceneUtils.h"

class CPlayTimer;
class CObject;

class CPlayScene : public CScene
{
	friend class CSceneManager;

private:
	CPlayScene();
	virtual ~CPlayScene();

private:
	CPlayTimer* mPlayTimer;

	EPlaySubState mSubState;

public:
	virtual bool Enter() final;
	virtual bool Exit()  final;

	virtual void Update(float deltaTime) final;

	virtual void LoadResources() final;

public:
	void SetSubState(EPlaySubState state);

private:
	CObject* InstantiatePlayer();
};