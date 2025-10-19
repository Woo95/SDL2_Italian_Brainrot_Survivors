#include "ResultPanel.h"
#include "AllWidgets.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/PlayerProfile.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/UIManager.h"

CResultPanel::CResultPanel()
{
	Construct();
}

CResultPanel::~CResultPanel()
{
}

void CResultPanel::Construct()
{
    CImage* outerPanel = CWidgetUtils::AllocateWidget<CImage>("ResultPanel_Image_Panel");
    outerPanel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    outerPanel->GetTransform()->SetPivot(FVector2D(0.5f, 0.5f));
    outerPanel->SetTexture("Texture_UIAtlas");
    outerPanel->SetFrame("PanelBox");
    outerPanel->Set9SlicingCorner(FVector2D(15.0f, 15.0f));
    outerPanel->SetCornerRatio(1.25f);
    AddChild(outerPanel);

    CTextBlock* category = CWidgetUtils::AllocateWidget<CTextBlock>("ResultPanel_TextBlock_Category");
    category->GetTransform()->SetRelativeScale(FVector2D(0.16f, 0.075f));
    category->GetTransform()->SetRelativePos(FVector2D(0.0f, -0.4f));
    category->GetTransform()->SetPivot(0.5f, 0.5f);
    category->SetAlignment(ETextBlock::Alignment::CENTER);
    category->SetCharWidth(50.f);
    category->SetFont("Font64_CourierPrime_Regular");
    category->SetText("Results");
    AddChild(category);

	//////////////////////////////////////////////////////////////////////////////////////////
	/* LEFT SIDE */

	CTextBlock* survived = CWidgetUtils::AllocateWidget<CTextBlock>("ResultPanel_TextBlock_Survived");
	survived->GetTransform()->SetRelativeScale(FVector2D(0.25f, 0.05f));
	survived->GetTransform()->SetRelativePos(FVector2D(-0.45f, -0.25f));
	survived->SetAlignment(ETextBlock::Alignment::LEFT);
	survived->SetCharWidth(15.f);
	survived->SetFont("Font64_CourierPrime_Regular");
	survived->SetText("Survived: ");
	AddChild(survived);

	CTextBlock* goldEarned = CWidgetUtils::AllocateWidget<CTextBlock>("ResultPanel_TextBlock_GoldEarned");
	goldEarned->GetTransform()->SetRelativeScale(FVector2D(0.25f, 0.05f));
	goldEarned->GetTransform()->SetRelativePos(FVector2D(-0.45f, -0.15f));
	goldEarned->SetAlignment(ETextBlock::Alignment::LEFT);
	goldEarned->SetCharWidth(15.f);
	goldEarned->SetFont("Font64_CourierPrime_Regular");
	goldEarned->SetText("Gold Earned: ");
	AddChild(goldEarned);

	CTextBlock* levelReached = CWidgetUtils::AllocateWidget<CTextBlock>("ResultPanel_TextBlock_LevelReached");
	levelReached->GetTransform()->SetRelativeScale(FVector2D(0.25f, 0.05f));
	levelReached->GetTransform()->SetRelativePos(FVector2D(-0.45f, -0.05f));
	levelReached->SetAlignment(ETextBlock::Alignment::LEFT);
	levelReached->SetCharWidth(15.f);
	levelReached->SetFont("Font64_CourierPrime_Regular");
	levelReached->SetText("Level reached: ");
	AddChild(levelReached);

	CTextBlock* enemiesKilled = CWidgetUtils::AllocateWidget<CTextBlock>("ResultPanel_TextBlock_EnemiesKilled");
	enemiesKilled->GetTransform()->SetRelativeScale(FVector2D(0.25f, 0.05f));
	enemiesKilled->GetTransform()->SetRelativePos(FVector2D(-0.45f, 0.05f));
	enemiesKilled->SetAlignment(ETextBlock::Alignment::LEFT);
	enemiesKilled->SetCharWidth(15.f);
	enemiesKilled->SetFont("Font64_CourierPrime_Regular");
	enemiesKilled->SetText("Enemies Killed: ");
	AddChild(enemiesKilled);

	mSurvivedStat = CWidgetUtils::AllocateWidget<CTextBlock>("ResultPanel_TextBlock_SurvivedStat");
	mSurvivedStat->GetTransform()->SetRelativeScale(FVector2D(0.1f, 0.05f));
	mSurvivedStat->GetTransform()->SetRelativePos(FVector2D(-0.12f, -0.25f));
	mSurvivedStat->SetAlignment(ETextBlock::Alignment::RIGHT);
	mSurvivedStat->SetCharWidth(15.f);
	mSurvivedStat->SetFont("Font64_CourierPrime_Regular");
	mSurvivedStat->SetText("00:00");
	AddChild(mSurvivedStat);

	mGoldEarnedStat = CWidgetUtils::AllocateWidget<CTextBlock>("ResultPanel_TextBlock_GoldEarnedStat");
	mGoldEarnedStat->GetTransform()->SetRelativeScale(FVector2D(0.1f, 0.05f));
	mGoldEarnedStat->GetTransform()->SetRelativePos(FVector2D(-0.12f, -0.15f));
	mGoldEarnedStat->SetAlignment(ETextBlock::Alignment::RIGHT);
	mGoldEarnedStat->SetCharWidth(15.f);
	mGoldEarnedStat->SetFont("Font64_CourierPrime_Regular");
	mGoldEarnedStat->SetText("0");
	AddChild(mGoldEarnedStat);

	mLevelReachedStat = CWidgetUtils::AllocateWidget<CTextBlock>("ResultPanel_TextBlock_LevelReachedStat");
	mLevelReachedStat->GetTransform()->SetRelativeScale(FVector2D(0.1f, 0.05f));
	mLevelReachedStat->GetTransform()->SetRelativePos(FVector2D(-0.12f, -0.05f));
	mLevelReachedStat->SetAlignment(ETextBlock::Alignment::RIGHT);
	mLevelReachedStat->SetCharWidth(15.f);
	mLevelReachedStat->SetFont("Font64_CourierPrime_Regular");
	mLevelReachedStat->SetText("0");
	AddChild(mLevelReachedStat);

	mEnemiesKilledStat = CWidgetUtils::AllocateWidget<CTextBlock>("ResultPanel_TextBlock_EnemiesKilledStat");
	mEnemiesKilledStat->GetTransform()->SetRelativeScale(FVector2D(0.1f, 0.05f));
	mEnemiesKilledStat->GetTransform()->SetRelativePos(FVector2D(-0.12f, 0.05f));
	mEnemiesKilledStat->SetAlignment(ETextBlock::Alignment::RIGHT);
	mEnemiesKilledStat->SetCharWidth(15.f);
	mEnemiesKilledStat->SetFont("Font64_CourierPrime_Regular");
	mEnemiesKilledStat->SetText("0");
	AddChild(mEnemiesKilledStat);

	CImage* middleLine = CWidgetUtils::AllocateWidget<CImage>("ResultPanel_Image_MiddleLine");
	middleLine->GetTransform()->SetRelativeScale(FVector2D(0.001f, 0.55f));
	middleLine->GetTransform()->SetPivot(0.5f, 0.5f);
	middleLine->SetTexture("Texture_UIAtlas");
	middleLine->SetFrame("ResultMidLine");
	AddChild(middleLine);

	//////////////////////////////////////////////////////////////////////////////////////////
	/* RIGHT SIDE */

	CPlayerProfile* playerProfile = CGameDataManager::GetInst()->GetPlayerProfile();

	CUIManager* UM = CAssetManager::GetInst()->GetUIManager();
	FVector2D playerScale(static_cast<float>((*(UM->GetUIFrames(playerProfile->GetName())))[0].w),
		static_cast<float>((*(UM->GetUIFrames(playerProfile->GetName())))[0].h));

	CImage* playerImage = CWidgetUtils::AllocateWidget<CImage>("ResultPanel_Image_Player");
	playerImage->GetTransform()->SetRelativeScale(playerScale * FVector2D(0.004f, 0.0055f));
	playerImage->GetTransform()->SetRelativePos(FVector2D(0.25f, -0.12f));
	playerImage->GetTransform()->SetPivot(FVector2D(0.5f, 0.5f));
	playerImage->SetTexture("Texture_Player");
	playerImage->SetFrame(playerProfile->GetName());
	AddChild(playerImage);

	CTextBlock* playerName = CWidgetUtils::AllocateWidget<CTextBlock>("ResultPanel_Text_Player");
	playerName->GetTransform()->SetRelativeScale(FVector2D(0.1f, 0.05f));
	playerName->GetTransform()->SetRelativePos(FVector2D(0.25f, 0.06f));
	playerName->GetTransform()->SetPivot(FVector2D(0.5f, 0.5f));
	playerName->SetAlignment(ETextBlock::Alignment::CENTER);
	playerName->SetCharWidth(15.f);
	playerName->SetFont("Font64_CourierPrime_Regular");
	playerName->SetText(playerProfile->GetName());
	AddChild(playerName);
}

void CResultPanel::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CResultPanel>(this);
}

void CResultPanel::UpdateSurvivedTime(float time)
{
	int minutes = static_cast<int>(time) / 60;
	int seconds = static_cast<int>(time) % 60;

	std::string minStr = (minutes < 10 ? "0" : "") + std::to_string(minutes);
	std::string secStr = (seconds < 10 ? "0" : "") + std::to_string(seconds);

	mSurvivedStat->SetText(minStr + ":" + secStr);
}

void CResultPanel::UpdateGoldEarned(int gold)
{
	mGoldEarnedStat->SetText(std::to_string(gold));
}

void CResultPanel::UpdateLevelReached(int level)
{
	mLevelReachedStat->SetText(std::to_string(level));
}

void CResultPanel::UpdateEnemiesKilled(int kill)
{
	mEnemiesKilledStat->SetText(std::to_string(kill));
}