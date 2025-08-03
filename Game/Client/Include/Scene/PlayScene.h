#pragma once

#include "Scene.h"

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

public:
	virtual bool Enter() final;
	virtual bool Exit()  final;

	virtual void Update(float deltaTime) final;

	virtual void LoadResources() final;

private:
	CObject* InstantiatePlayer();
};