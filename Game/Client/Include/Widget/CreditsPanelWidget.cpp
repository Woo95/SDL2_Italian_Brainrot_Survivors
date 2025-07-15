#include "CreditsPanelWidget.h"
#include "AllWidgets.h"

CCreditsPanelWidget::CCreditsPanelWidget()
{
	Construct();
}

CCreditsPanelWidget::~CCreditsPanelWidget()
{
}

void CCreditsPanelWidget::Construct()
{
	SetInteractable(true);

    CImage* outerPanel = CWidgetUtils::AllocateWidget<CImage>("Image_CreditsPanelBox");
    outerPanel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    outerPanel->SetTexture("Texture_UIAtlas");
    outerPanel->SetFrame("PanelBox");
    outerPanel->Set9SlicingCorner(FVector2D(15.f, 15.f));
    outerPanel->SetCornerRatio(1.25f);
    AddChild(outerPanel);

    CTextBlock* category = CWidgetUtils::AllocateWidget<CTextBlock>("Text_CreditsCategory");
    category->GetTransform()->SetRelativeScale(outerPanel->GetTransform()->GetRelativeScale() * FVector2D(0.3f, 0.065f));
    category->GetTransform()->SetRelativePos(outerPanel->GetTransform()->GetRelativePos() + 
        FVector2D(outerPanel->GetTransform()->GetRelativeScale().x * 0.5f - category->GetTransform()->GetRelativeScale().x * 0.5f, outerPanel->GetTransform()->GetRelativeScale().y * 0.0325f));
    category->SetAlignment(ETextBlock::Alignment::CENTER);
    category->SetCharWidth(50.f);
    category->SetFont("Font64_CourierPrime_Regular");
    category->SetText("Credits");
    AddChild(category);

    CTextBlock* context1 = CWidgetUtils::AllocateWidget<CTextBlock>("Text_CreditsContext1");
    context1->GetTransform()->SetRelativeScale(FVector2D(0.6f, 0.04f));
    context1->GetTransform()->SetRelativePos(FVector2D(0.02f, 0.1f));
    context1->SetAlignment(ETextBlock::Alignment::CENTER);
    context1->SetCharWidth(50.f);
    context1->SetFont("Font64_CourierPrime_Regular");
    context1->SetText("GAME FRAMEWORK & PROGRAMMING");
    AddChild(context1);

    CTextBlock* context2 = CWidgetUtils::AllocateWidget<CTextBlock>("Text_CreditsContext2");
    context2->GetTransform()->SetRelativeScale(FVector2D(0.25f, 0.04f));
    context2->GetTransform()->SetRelativePos(context1->GetTransform()->GetRelativePos().x,
        context1->GetTransform()->GetRelativePos().y + context1->GetTransform()->GetRelativeScale().y);
    context2->SetAlignment(ETextBlock::Alignment::LEFT);
    context2->SetCharWidth(50.f);
    context2->SetFont("Font64_CourierPrime_Regular");
    context2->SetText("- Chaewan Woo");
    AddChild(context2);

    CTextBlock* context3 = CWidgetUtils::AllocateWidget<CTextBlock>("Text_CreditsContext3");
    context3->GetTransform()->SetRelativeScale(FVector2D(0.5f, 0.04f));
    context3->GetTransform()->SetRelativePos(FVector2D(0.02f, 0.25f));
    context3->SetAlignment(ETextBlock::Alignment::CENTER);
    context3->SetCharWidth(50.f);
    context3->SetFont("Font64_CourierPrime_Regular");
    context3->SetText("ITALIAN BRAINROT ASSETS");
    AddChild(context3);

    CTextBlock* context4 = CWidgetUtils::AllocateWidget<CTextBlock>("Text_CreditsContext4");
    context4->GetTransform()->SetRelativeScale(FVector2D(0.225f, 0.04f));
    context4->GetTransform()->SetRelativePos(context3->GetTransform()->GetRelativePos().x, 
        context3->GetTransform()->GetRelativePos().y + context3->GetTransform()->GetRelativeScale().y);
    context4->SetAlignment(ETextBlock::Alignment::LEFT);
    context4->SetCharWidth(50.f);
    context4->SetFont("Font64_CourierPrime_Regular");
    context4->SetText("- Yulim Lee");
    AddChild(context4);

    CTextBlock* context5 = CWidgetUtils::AllocateWidget<CTextBlock>("Text_CreditsContext5");
    context5->GetTransform()->SetRelativeScale(FVector2D(0.95f, 0.04f));
    context5->GetTransform()->SetRelativePos(FVector2D(0.02f, 0.4f));
    context5->SetAlignment(ETextBlock::Alignment::LEFT);
    context5->SetCharWidth(50.f);
    context5->SetFont("Font64_CourierPrime_Regular");
    context5->SetText("Some assets are from Vampire Survivors Poncle.");
    AddChild(context5);

    CTextBlock* context6 = CWidgetUtils::AllocateWidget<CTextBlock>("Text_CreditsContext6");
    context6->GetTransform()->SetRelativeScale(FVector2D(0.95f, 0.04f));
    context6->GetTransform()->SetRelativePos(context5->GetTransform()->GetRelativePos().x,
        context5->GetTransform()->GetRelativePos().y + context5->GetTransform()->GetRelativeScale().y);
    context6->SetAlignment(ETextBlock::Alignment::LEFT);
    context6->SetCharWidth(50.f);
    context6->SetFont("Font64_CourierPrime_Regular");
    context6->SetText("Not affiliated with Poncle. Non-commercial use.");
    AddChild(context6);
}

void CCreditsPanelWidget::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CCreditsPanelWidget>(this);
}