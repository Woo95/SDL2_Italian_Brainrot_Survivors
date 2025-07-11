#include "OptionPanelWidget.h"
#include "AllWidgets.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"

COptionPanelWidget::COptionPanelWidget()
{
    Construct();
}

COptionPanelWidget::~COptionPanelWidget()
{
}

void COptionPanelWidget::Construct()
{
    SetInteractable(true);

    CImage* outerPanel = CWidgetUtils::AllocateWidget<CImage>("Image_OptionPanelBox");
    outerPanel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    outerPanel->SetTexture("Texture_UIAtlas");
    outerPanel->SetFrame("PanelBox");
    outerPanel->Set9SlicingCorner(FVector2D(15.f, 15.f));
    outerPanel->SetCornerRatio(1.25f);
    AddChild(outerPanel);

    CImage* innerPanel = CWidgetUtils::AllocateWidget<CImage>("Image_OptionPanelBox2");
    innerPanel->GetTransform()->SetRelativeScale(FVector2D(0.175f, 1.0f));
    innerPanel->SetTexture("Texture_UIAtlas");
    innerPanel->SetFrame("PanelBox");
    innerPanel->Set9SlicingCorner(FVector2D(15.f, 15.f));
    innerPanel->SetCornerRatio(1.25f);
    AddChild(innerPanel);

    CImage* soundIcon = CWidgetUtils::AllocateWidget<CImage>("Image_OptionPanelBox");
    soundIcon->GetTransform()->SetRelativeScale(FVector2D(0.1f, 0.12f));
    soundIcon->GetTransform()->SetRelativePos(FVector2D(0.04f, 0.05f));
    soundIcon->SetTexture("Texture_UIAtlas");
    soundIcon->SetFrame("SoundIcon");
    AddChild(soundIcon);

    CTextBlock* category = CWidgetUtils::AllocateWidget<CTextBlock>("Text_OptionCategory");
    category->GetTransform()->SetRelativeScale(FVector2D(0.22f, 0.075f));
    category->GetTransform()->SetRelativePos(0.5f + (innerPanel->GetTransform()->GetRelativeScale().x - category->GetTransform()->GetRelativeScale().x) * 0.5f,
        soundIcon->GetTransform()->GetRelativePos().y);
    category->SetAlignment(ETextBlock::Alignment::CENTER);
    category->SetCharWidth(50.f);
    category->SetFont("Font64_CourierPrime_Regular");
    category->SetText("Sound");
    AddChild(category);

    CTextBlock* sounds = CWidgetUtils::AllocateWidget<CTextBlock>("Text_OptionSFX");
    sounds->GetTransform()->SetRelativeScale(FVector2D(0.15f, 0.055f));
    sounds->GetTransform()->SetRelativePos(FVector2D(innerPanel->GetTransform()->GetRelativeScale().x * 1.5f,
            category->GetTransform()->GetRelativePos().y + category->GetTransform()->GetRelativeScale().y * 1.9f));
    sounds->SetAlignment(ETextBlock::Alignment::CENTER);
    sounds->SetCharWidth(25.f);
    sounds->SetFont("Font64_CourierPrime_Regular");
    sounds->SetText("Sounds");
    AddChild(sounds);

    CSlider* sliderSFX = CWidgetUtils::AllocateWidget<CSlider>("Slider_SFX");
    sliderSFX->GetTransform()->SetRelativeScale(FVector2D(0.27f, 0.095f));
    sliderSFX->GetTransform()->SetRelativePos(sounds->GetTransform()->GetRelativePos().x * 2.35f, sounds->GetTransform()->GetRelativePos().y - sounds->GetTransform()->GetRelativeScale().y * 0.38f);
    sliderSFX->SetTexture("Texture_UIAtlas");
    sliderSFX->SetFrame("Slider");
    sliderSFX->SetPercent(CAssetManager::GetInst()->GetSoundManager()->GetVolume<CSFX>());
    sliderSFX->SetTrackRect({ 0, 0, 0, 3 });
    sliderSFX->SetThumbRect({ 0, 0, 52, 52 });
    sliderSFX->AddCallback(ESlider::InputEvent::HOLD, [](float percent) {CAssetManager::GetInst()->GetSoundManager()->SetVolume<CSFX>(percent);});
    AddChild(sliderSFX);

    CTextBlock* music = CWidgetUtils::AllocateWidget<CTextBlock>("Text_OptionBGM");
    music->GetTransform()->SetRelativeScale(FVector2D(0.15f, 0.055f));
    music->GetTransform()->SetRelativePos(sounds->GetTransform()->GetRelativePos().x, sounds->GetTransform()->GetRelativePos().y * 1.7f);
    music->SetAlignment(ETextBlock::Alignment::CENTER);
    music->SetCharWidth(25.f);
    music->SetFont("Font64_CourierPrime_Regular");
    music->SetText("Music");
    AddChild(music);

    CSlider* sliderBGM = CWidgetUtils::AllocateWidget<CSlider>("Slider_BGM");
    sliderBGM->GetTransform()->SetRelativeScale(FVector2D(0.27f, 0.095f));
    sliderBGM->GetTransform()->SetRelativePos(music->GetTransform()->GetRelativePos().x * 2.35f, music->GetTransform()->GetRelativePos().y - music->GetTransform()->GetRelativeScale().y * 0.38f);
    sliderBGM->SetTexture("Texture_UIAtlas");
    sliderBGM->SetFrame("Slider");
    sliderBGM->SetPercent(CAssetManager::GetInst()->GetSoundManager()->GetVolume<CBGM>());
    sliderBGM->SetTrackRect({ 0, 0, 0, 3 });
    sliderBGM->SetThumbRect({ 0, 0, 52, 52 });
    sliderBGM->AddCallback(ESlider::InputEvent::HOLD, [](float percent) {CAssetManager::GetInst()->GetSoundManager()->SetVolume<CBGM>(percent);});
    AddChild(sliderBGM);
}

void COptionPanelWidget::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<COptionPanelWidget>(this);
}