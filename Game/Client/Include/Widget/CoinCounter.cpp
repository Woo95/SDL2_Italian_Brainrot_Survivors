#include "CoinCounter.h"
#include "AllWidgets.h"

CCoinCounter::CCoinCounter()
{
	Construct();
}

CCoinCounter::~CCoinCounter()
{
}

void CCoinCounter::Construct()
{
	CImage* coinIcon = CWidgetUtils::AllocateWidget<CImage>("CoinCounter_Image_CoinIcon");
	coinIcon->GetTransform()->SetRelativeScale(0.3f, 1.0f);
	coinIcon->GetTransform()->SetRelativePos(0.35f, 0.0f);
	coinIcon->GetTransform()->SetPivot(0.5f, 0.5f);
	coinIcon->SetTexture("Texture_UIAtlas");
	coinIcon->SetFrame("CoinIcon");
	AddChild(coinIcon);

	mCoinCount = CWidgetUtils::AllocateWidget<CTextBlock>("CoinCounter_Text_Count");
	mCoinCount->GetTransform()->SetRelativeScale(0.6f, 1.0f);
	mCoinCount->GetTransform()->SetRelativePos(-0.2f, 0.0f);
	mCoinCount->GetTransform()->SetPivot(0.5f, 0.5f);
	mCoinCount->SetAlignment(ETextBlock::Alignment::RIGHT);
	mCoinCount->SetCharWidth(15.0f);
	mCoinCount->SetFont("Font64_CourierPrime_Regular");
	mCoinCount->SetText("0");
	AddChild(mCoinCount);
}

void CCoinCounter::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CCoinCounter>(this);
}

void CCoinCounter::SetCountText(int count)
{
	mCoinCount->SetText(std::to_string(count));
}