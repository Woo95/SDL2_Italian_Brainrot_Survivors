#include "TextBlock.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/FontManager.h"
#include "../Resource/Font.h"
#include "../Manager/MemoryPoolManager.h"

CTextBlock::CTextBlock()
{
}

CTextBlock::~CTextBlock()
{
	if (mShadowTexture)
	{
		SDL_DestroyTexture(mShadowTexture);
		mShadowTexture = nullptr;
	}
	if (mTexture)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
	mFont = nullptr;
}

void CTextBlock::Render(SDL_Renderer* Renderer, const FVector2D& topLeft)
{
	SDL_Rect renderRect = mRect;

	if (mHasShadow)
	{
		UpdateTextTexture(Renderer, mUpdateShadowTexture, mShadowTexture, mShadowColor);

		renderRect.x += (int)(mShadowOffset.x + topLeft.x);
		renderRect.y += (int)(mShadowOffset.y + topLeft.y);

		SDL_RenderCopy(Renderer, mShadowTexture, nullptr, &renderRect);

		renderRect.x -= (int)(mShadowOffset.x + topLeft.x);
		renderRect.y -= (int)(mShadowOffset.y + topLeft.y);
	}
	UpdateTextTexture(Renderer, mUpdateTexture, mTexture, mColor);
	SDL_RenderCopy(Renderer, mTexture, nullptr, &renderRect);

	CWidget::Render(Renderer, topLeft);
}

void CTextBlock::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CTextBlock>(this);
}

void CTextBlock::UpdateTextTexture(SDL_Renderer* Renderer, bool& updateTexture, SDL_Texture*& texture, SDL_Color color)
{
	if (updateTexture)
	{
		if (texture)
		{
			SDL_DestroyTexture(texture);
			texture = nullptr;
		}
		// 텍스트를 CPU 메모리에 SDL_Surface로 생성
		SDL_Surface* surface = TTF_RenderText_Blended(mFont.get()->GetFont(), mText.c_str(), color);

		// SDL_Surface를 GPU에서 사용할 수 있는 SDL_Texture로 변환
		texture = SDL_CreateTextureFromSurface(Renderer, surface);

		SDL_FreeSurface(surface);

		updateTexture = false;
	}
}

void CTextBlock::SetFont(const std::string& key)
{
	mFont = CAssetManager::GetInst()->GetFontManager()->GetFont(key);
}

void CTextBlock::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	mColor.r = r;
	mColor.g = g;
	mColor.b = b;

	mUpdateTexture = true;
}

void CTextBlock::SetShadowColor(Uint8 r, Uint8 g, Uint8 b)
{
	mShadowColor.r = r;
	mShadowColor.g = g;
	mShadowColor.b = b;

	mUpdateShadowTexture = true;
}

void CTextBlock::SetShadowOffset(float x, float y)
{
	mShadowOffset.x = x;
	mShadowOffset.y = y;
}