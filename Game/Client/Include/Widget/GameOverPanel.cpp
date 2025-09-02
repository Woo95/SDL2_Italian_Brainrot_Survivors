#include "GameOverPanel.h"
#include "AllWidgets.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"
#include "../Manager/SceneManager.h"

CGameOverPanel::CGameOverPanel()
{
	Construct();
}

CGameOverPanel::~CGameOverPanel()
{
}

void CGameOverPanel::Construct()
{
	CImage* background = CWidgetUtils::AllocateWidget<CImage>("GameOverPanel_Image_GameOverBG");
	background->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
	background->SetTexture("Texture_GameOverBG");
	background->SetFrame("GameOverBG");
	background->SetAlpha(100);
	AddChild(background);

	CButton* button = CreateButton("Quit", "RedButton", FVector2D(0.17f, 0.09f), "QUIT", FVector2D(0.5f, 0.6f));
	button->GetTransform()->SetRelativePos(FVector2D(0.5f, 0.7f));
	button->Set9SlicingCorner(FVector2D(10.0f, 7.0f));
	button->SetCornerRatio(2.0f);
	button->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
	button->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->ChangeRequest(ETransition::CLEAR_THEN_PUSH, ESceneState::RESULT);});
}

void CGameOverPanel::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CGameOverPanel>(this);
}

CButton* CGameOverPanel::CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize)
{
	CButton* button = CWidgetUtils::AllocateWidget<CButton>("GameOverPanel_Button_" + widgetName);
	button->GetTransform()->SetRelativeScale(buttonSize);
	button->GetTransform()->SetPivot(0.5f, 0.5f);
	button->SetTexture("Texture_UIAtlas");
	button->SetFrame(buttonFrame);
	AddChild(button);

	CTextBlock* text = CWidgetUtils::AllocateWidget<CTextBlock>("GameOverPanel_TextBlock_" + widgetName);
	button->AddChild(text);
	text->GetTransform()->SetRelativeScale(textSize);
	text->GetTransform()->SetPivot(0.5f, 0.5f);
	text->GetTransform()->SetRelativePos(0.0f, 0.0f);
	text->SetFont("Font64_CourierPrime_Regular");
	text->SetText(textLabel);

	return button;
}