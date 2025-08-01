#include "Portrait.h"
#include "AllWidgets.h"

CPortrait::CPortrait()
{
	Construct();
}

CPortrait::~CPortrait()
{
}

void CPortrait::Construct()
{
	mFrame = CWidgetUtils::AllocateWidget<CImage>("Portrait_Image_Frame");
	mFrame->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	mFrame->GetTransform()->SetPivot(0.5f, 0.5f);
	mFrame->SetTexture("Texture_UIAtlas");
	mFrame->SetFrame("PortraitBox");
	mFrame->Set9SlicingCorner(FVector2D(5.0f, 5.0f));
	mFrame->SetCornerRatio(1.5f);
	AddChild(mFrame);

	mPortrait = CWidgetUtils::AllocateWidget<CImage>("Portrait_Image_Character");
	mPortrait->GetTransform()->SetRelativeScale(FVector2D(0.85f, 0.85f));
	mPortrait->GetTransform()->SetPivot(0.5f, 0.5f);
	mPortrait->SetTexture("Texture_UIAtlas");
	mPortrait->SetFrame("Empty");
	mFrame->AddChild(mPortrait);
}

void CPortrait::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CPortrait>(this);
}

void CPortrait::SetPortrait(const std::string& portrait)
{
	mPortrait->SetFrame(portrait);
}