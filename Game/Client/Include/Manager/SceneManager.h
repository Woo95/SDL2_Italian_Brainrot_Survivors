#pragma once

#include "../Core/GameInfo.h"
#include "../Core/Utils/SceneUtils.h"

class CScene;

class CSceneManager
{
	friend class CGameManager;

private:
	CSceneManager();
	~CSceneManager();

private:
	std::vector<CScene*> mScenes;

	struct FTransitionInfo
	{
		ETransition transition   = ETransition::NONE;
		ESceneState pendingState = ESceneState::NONE;
	} mPending;

	static CSceneManager* mInst;

public:
	CScene* GetCurrentScene() const { return mScenes.empty() ? nullptr : mScenes.back(); }
	void ChangeRequest(ETransition transition, ESceneState state)
	{
		mPending.transition = transition;
		mPending.pendingState = state;
	}

private:
	bool Init();
	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Render(SDL_Renderer* renderer);

	void ChangeApply();
	void PushScene();
	void PopScene();
	void SwapScene();
	void ClearScenes();
	CScene* GetSceneFromState(ESceneState state);

public:
	static CSceneManager* GetInst()
	{
		if (!mInst)
			mInst = new CSceneManager;
		return mInst;
	}
private:
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};