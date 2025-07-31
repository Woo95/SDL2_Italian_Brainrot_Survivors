#include "ResultPanel.h"
#include "Image.h"
#include "TextBlock.h"

CResultPanel::CResultPanel()
{
	Construct();
}

CResultPanel::~CResultPanel()
{
}

void CResultPanel::Construct()
{
    CImage* outerPanel = CWidgetUtils::AllocateWidget<CImage>("Image_ResultPanelBox");
    outerPanel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    outerPanel->GetTransform()->SetPivot(FVector2D(0.5f, 0.5f));
    outerPanel->SetTexture("Texture_UIAtlas");
    outerPanel->SetFrame("PanelBox");
    outerPanel->Set9SlicingCorner(FVector2D(15.f, 15.f));
    outerPanel->SetCornerRatio(1.25f);
    AddChild(outerPanel);

    CTextBlock* category = CWidgetUtils::AllocateWidget<CTextBlock>("Text_ResultsCategory");
    category->GetTransform()->SetRelativeScale(FVector2D(0.16f, 0.075f));
    category->GetTransform()->SetRelativePos(FVector2D(0.0f, -0.4f));
    category->GetTransform()->SetPivot(0.5f, 0.5f);
    category->SetAlignment(ETextBlock::Alignment::CENTER);
    category->SetCharWidth(50.f);
    category->SetFont("Font64_CourierPrime_Regular");
    category->SetText("Results");
    AddChild(category);
}

void CResultPanel::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CResultPanel>(this);
}