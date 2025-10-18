#include "ResultScene.h"
#include "Extension/ResultUI.h"
#include "../Manager/SceneManager.h"
#include "../Manager/EventManager.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/PlayerProfile.h"
#include "../Widget/AllWidgets.h"

CResultScene::CResultScene()
{
	mSceneUI = new CResultUI;
}

CResultScene::~CResultScene()
{
	SAFE_DELETE(mSceneUI);
}

bool CResultScene::Enter(void* payload)
{
	BindEventListeners();

	mSceneUI->Init();

	FResultData* resultData = static_cast<FResultData*>(payload);
	CGameDataManager::GetInst()->GetPlayerProfile()->AddBalance(resultData->goldEarned);
	((CResultUI*)mSceneUI)->GetResultPanel()->UpdateSurvivedTime(resultData->survivedTime);
	((CResultUI*)mSceneUI)->GetResultPanel()->UpdateGoldEarned(resultData->goldEarned);
	((CResultUI*)mSceneUI)->GetResultPanel()->UpdateLevelReached(resultData->levelReached);
	((CResultUI*)mSceneUI)->GetResultPanel()->UpdateEnemiesKilled(resultData->killCount);
	delete resultData;

	return true;
}

bool CResultScene::Exit()
{
	CEventManager::GetInst()->ClearListener();

	return true;
}

void CResultScene::LoadResources()
{
	LoadTexture("Texture_OverlayBG", "OverlayBG.png");
	LoadTexture("Texture_UIAtlas", "UIAtlas.png");

	std::string charName = CGameDataManager::GetInst()->GetPlayerProfile()->GetName();
	LoadTexture("Texture_" + charName, (charName + ".png").c_str());

	LoadFont("Font64_CourierPrime_Regular", "CourierPrime_Regular.ttf", 64);

	LoadSFX("SFX_PressOut", "sfx_pressOut.wav");
}

void CResultScene::BindEventListeners()
{
	CEventManager* EM = CEventManager::GetInst();

	// 씬 전환 관련
	EM->AddListener(EEventType::GOTO_MENU_SCENE, [this](void*)
	{
		CSceneManager::GetInst()->ChangeRequest(ETransition::SWAP, ESceneState::MENU);
	});
}