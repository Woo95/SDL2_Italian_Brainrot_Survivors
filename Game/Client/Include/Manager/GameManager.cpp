#include "GameManager.h"
#include "../Core/Timer.h"
#include "../Core/Input.h"
#include "MemoryPoolManager.h"
#include "Data/PathManager.h"
#include "Data/Resource/AssetManager.h"
#include "Data/GameData/GameDataManager.h"
#include "../Core/DataLoader.h"
#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "SceneManager.h"

CGameManager* CGameManager::mInst = nullptr;

CGameManager::CGameManager() :
	mWindow(nullptr),
	mRenderer(nullptr),
	mLoop(true)
{
}

CGameManager::~CGameManager()
{
    CSceneManager::DestroyInst();
    
    CPhysicsManager::DestroyInst();

    CCollisionManager::DestroyInst();

    CInput::DestroyInst();

    CGameDataManager::DestroyInst();

    CAssetManager::DestroyInst();

    CPathManager::DestroyInst();

    CMemoryPoolManager::DestroyInst();

    SDL_DestroyRenderer(mRenderer);

    SDL_DestroyWindow(mWindow);

    SDL_Quit();
}

bool CGameManager::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    mWindow = SDL_CreateWindow("Italian Brainrot Survivors", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 800, SDL_WINDOW_SHOWN);
    if (!mWindow)
        return false;

    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    if (!mRenderer)
        return false;

    CTimer::Init();

    if (!CInput::GetInst()->Init())
        return false;

    if (!CPathManager::GetInst()->Init())
        return false;

    CDataLoader dataLoader;
    if (!dataLoader.Init())
        return false;

    if (!CCollisionManager::GetInst()->Init())
        return false;

    if (!CSceneManager::GetInst()->Init())
        return false;

    return true;
}

void CGameManager::Run()
{
	SDL_Event event;

	while (mLoop)
	{
		// 이벤트가 있을 경우...
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			mLoop = false;

		Update();

		LateUpdate();

		Render();
	}
}

void CGameManager::Update()
{
    CTimer::Update();

    CInput::GetInst()->Update();

    CSceneManager::GetInst()->Update(CTimer::GetDeltaTime());
}

void CGameManager::LateUpdate()
{
    CSceneManager::GetInst()->LateUpdate(CTimer::GetDeltaTime());
}

void CGameManager::Render()
{
    // 현재 렌더 색상 검정으로 설정
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    // 현재 색상으로 화면 지우기
    SDL_RenderClear(mRenderer);

    CSceneManager::GetInst()->Render(mRenderer);

    // 렌더링한 내용을 화면에 표시
    SDL_RenderPresent(mRenderer);
}