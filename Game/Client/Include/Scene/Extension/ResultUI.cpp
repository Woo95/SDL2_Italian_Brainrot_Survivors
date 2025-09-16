#include "ResultUI.h"
#include "../../Engine.h"
#include "../../Widget/AllWidgets.h"
#include "../../Manager/EventManager.h"
#include "../../Manager/Data/Resource/AssetManager.h"
#include "../../Manager/Data/Resource/SoundManager.h"

CResultUI::CResultUI()
{
}

CResultUI::~CResultUI()
{
}

bool CResultUI::Init()
{
    const FVector2D& resolution = CEngine::GetInst()->GetResolution();

    CImage* background = CWidgetUtils::AllocateWidget<CImage>("ResultUI_Image_OverlayBG");
    background->GetTransform()->SetWorldScale(resolution);
    background->SetTexture("Texture_OverlayBG");
    background->SetFrame("OverlayBG");
    AddWidget(background);

    mResultPanel = CWidgetUtils::AllocateWidget<CResultPanel, 1>("ResultUI_ResultPanel");
    mResultPanel->GetTransform()->SetWorldScale(resolution * FVector2D(0.75f, 0.75f));
    mResultPanel->GetTransform()->SetWorldPos(resolution * FVector2D(0.5f, 0.425f));
    mResultPanel->GetTransform()->SetPivot(0.5f, 0.5f);
    AddWidget(mResultPanel);

    CButton* btnDone = CreateButton("Done", "BlueButton", resolution * FVector2D(0.17f, 0.09f), "DONE", FVector2D(0.45f, 0.55f));
    btnDone->GetTransform()->SetWorldPos(resolution * FVector2D(0.5f, 0.9f));
    btnDone->Set9SlicingCorner(FVector2D(10.0f, 7.0f));
    btnDone->SetCornerRatio(2.0f);
    btnDone->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    btnDone->AddCallback(EButton::InputEvent::RELEASE, []() {CEventManager::GetInst()->Broadcast(EEventType::GOTO_MENU_SCENE);});

    return true;
}

CButton* CResultUI::CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize)
{
    CButton* button = CWidgetUtils::AllocateWidget<CButton>("ResultUI_Button_" + widgetName);
    button->GetTransform()->SetWorldScale(buttonSize);
    button->GetTransform()->SetPivot(0.5f, 0.5f);
    button->SetTexture("Texture_UIAtlas");
    button->SetFrame(buttonFrame);
    AddWidget(button);

    CTextBlock* text = CWidgetUtils::AllocateWidget<CTextBlock>("ResultUI_TextBlock_" + widgetName);
    button->AddChild(text);
    text->GetTransform()->SetRelativeScale(textSize);
    text->GetTransform()->SetPivot(0.5f, 0.5f);
    text->GetTransform()->SetRelativePos(0.0f, 0.0f);
    text->SetFont("Font64_CourierPrime_Regular");
    text->SetText(textLabel);

    return button;
}