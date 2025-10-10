#include "KillCounter.h"
#include "AllWidgets.h"

CKillCounter::CKillCounter()
{
	Construct();
}

CKillCounter::~CKillCounter()
{
}

void CKillCounter::Construct()
{
    CImage* killIcon = CWidgetUtils::AllocateWidget<CImage>("KillCounter_Image_KillIcon");
    killIcon->GetTransform()->SetRelativeScale(0.3f, 1.0f);
    killIcon->GetTransform()->SetRelativePos(0.35f, 0.0f);
    killIcon->GetTransform()->SetPivot(0.5f, 0.5f);
    killIcon->SetTexture("Texture_UIAtlas");
    killIcon->SetFrame("KillIcon");
    AddChild(killIcon);

    mKillCount = CWidgetUtils::AllocateWidget<CTextBlock>("KillCounter_Text_Count");
    mKillCount->GetTransform()->SetRelativeScale(0.6f, 1.0f);
    mKillCount->GetTransform()->SetRelativePos(-0.2f, 0.0f);
    mKillCount->GetTransform()->SetPivot(0.5f, 0.5f);
    mKillCount->SetAlignment(ETextBlock::Alignment::RIGHT);
    mKillCount->SetCharWidth(15.0f);
    mKillCount->SetFont("Font64_CourierPrime_Regular");
    mKillCount->SetText("0");
    AddChild(mKillCount);
}

void CKillCounter::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CKillCounter>(this);
}

void CKillCounter::SetCountText(int count)
{
    mKillCount->SetText(std::to_string(count));
}