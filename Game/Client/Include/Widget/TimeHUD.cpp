#include "TimeHUD.h"
#include "AllWidgets.h"

CTimeHUD::CTimeHUD()
{
	Construct();
}

CTimeHUD::~CTimeHUD()
{
}

void CTimeHUD::Construct()
{
	mTimer = CWidgetUtils::AllocateWidget<CTextBlock>("TimeHUD_TextBlock_Timer");
	mTimer->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	mTimer->GetTransform()->SetPivot(0.5f, 0.5f);
	mTimer->SetAlignment(ETextBlock::Alignment::CENTER);
	mTimer->SetCharWidth(50.0f);
	mTimer->SetFont("Font64_CourierPrime_Regular");
	mTimer->SetText("00:00");
	AddChild(mTimer);
}

void CTimeHUD::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CTimeHUD>(this);
}

void CTimeHUD::SetTimeText(float totalSeconds)
{
	int minutes = static_cast<int>(totalSeconds) / 60;
	int seconds = static_cast<int>(totalSeconds) % 60;

	std::string minStr = (minutes < 10 ? "0" : "") + std::to_string(minutes);
	std::string secStr = (seconds < 10 ? "0" : "") + std::to_string(seconds);

	mTimer->SetText(minStr + ":" + secStr);
}