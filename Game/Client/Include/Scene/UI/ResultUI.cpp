#include "ResultUI.h"
#include "../../Widget/AllWidgets.h"
#include "../../Manager/GameManager.h"
#include "../../Manager/SceneManager.h"
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
    const FVector2D& resolution = CGameManager::GetInst()->GetResolution();

    CImage* background = CWidgetUtils::AllocateWidget<CImage>("ResultUI_Image_ResultBG");
    background->GetTransform()->SetWorldScale(resolution);
    background->SetTexture("Texture_IntroBG");
    background->SetFrame("IntroBG");
    AddWidget(background);

    CResultPanel* resultPanel = CWidgetUtils::AllocateWidget<CResultPanel, 1>("ResultUI_ResultPanel");
    resultPanel->GetTransform()->SetWorldScale(resolution * FVector2D(0.75f, 0.75f));
    resultPanel->GetTransform()->SetWorldPos(resolution * FVector2D(0.5f, 0.425f));
    resultPanel->GetTransform()->SetPivot(0.5f, 0.5f);
    AddWidget(resultPanel);

    CButton* btnDone = CreateButton("Done", "BlueButton", resolution * FVector2D(0.17f, 0.09f), "DONE", FVector2D(0.45f, 0.55f));
    btnDone->GetTransform()->SetWorldPos(resolution * FVector2D(0.5f, 0.9f));
    btnDone->Set9SlicingCorner(FVector2D(10.0f, 7.0f));
    btnDone->SetCornerRatio(2.0f);
    btnDone->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    btnDone->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->ChangeRequest(ETransition::SWAP, ESceneState::MENU);});

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