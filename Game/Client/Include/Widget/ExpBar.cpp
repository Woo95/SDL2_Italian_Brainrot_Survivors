#include "ExpBar.h"
#include "AllWidgets.h"

CExpBar::CExpBar()
{
	Construct();
}

CExpBar::~CExpBar()
{
}

void CExpBar::Construct()
{
	mExpProgress = CWidgetUtils::AllocateWidget<CProgressBar>("ExpBar_ProgressBar_Exp");
	mExpProgress->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
	mExpProgress->GetTransform()->SetPivot(0.5f, 0.5f);
	mExpProgress->SetTexture("Texture_UIAtlas");
	mExpProgress->SetFrame("StatusBar");
	mExpProgress->SetColor(EProgBar::State::BACK, 0, 0, 0);
	mExpProgress->SetColor(EProgBar::State::FILL, 50, 50, 255);
	mExpProgress->SetPercent(0.0f);
	AddChild(mExpProgress);

	mFrame = CWidgetUtils::AllocateWidget<CImage>("ExpBar_Image_Frame");
	mFrame->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	mFrame->GetTransform()->SetPivot(0.5f, 0.5f);
	mFrame->SetTexture("Texture_UIAtlas");
	mFrame->SetFrame("ExpBox");
	mFrame->Set9SlicingCorner(FVector2D(7.0f, 7.0f));
	mFrame->SetCornerRatio(1.0f);
	AddChild(mFrame);

	CTextBlock* levelPrefix = CWidgetUtils::AllocateWidget<CTextBlock>("ExpBar_TextBlock_LevelPrefix");
	levelPrefix->GetTransform()->SetRelativeScale(0.02f, 0.9f);
	levelPrefix->GetTransform()->SetRelativePos(0.445f, 0.0f);
	levelPrefix->GetTransform()->SetPivot(0.0f, 0.5f);
	levelPrefix->SetAlignment(ETextBlock::Alignment::LEFT);
	levelPrefix->SetCharWidth(10.0f);
	levelPrefix->SetFont("Font64_CourierPrime_Regular");
	levelPrefix->SetText("LV");
	AddChild(levelPrefix);

	mLevel = CWidgetUtils::AllocateWidget<CTextBlock>("ExpBar_TextBlock_Level");
	mLevel->GetTransform()->SetRelativeScale(0.025f, 0.9f);
	mLevel->GetTransform()->SetRelativePos(0.47f, 0.0f);
	mLevel->GetTransform()->SetPivot(0.0f, 0.5f);
	mLevel->SetAlignment(ETextBlock::Alignment::LEFT);
	mLevel->SetCharWidth(10.0f);
	mLevel->SetFont("Font64_CourierPrime_Regular");
	mLevel->SetText("1");
	AddChild(mLevel);
}

void CExpBar::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CExpBar>(this);
}