#include "ScrollMapComponent.h"
#include "../../Manager/Data/Resource/AssetManager.h"
#include "../../Manager/Data/Resource/TextureManager.h"
#include "../../Manager/Data/Resource/SpriteManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Resource/Texture.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Camera.h"

CScrollMapComponent::CScrollMapComponent() :
	mCamera(nullptr),
	mTexture(nullptr),
	mFrame({})
{
	mTypeID = typeid(CScrollMapComponent).hash_code();
}

CScrollMapComponent::~CScrollMapComponent()
{
	mTexture = nullptr;
}

bool CScrollMapComponent::Init()
{
	if (!mTexture)
		return false;

	mCamera = CSceneManager::GetInst()->GetCurrentScene()->GetCamera();

	return CComponent::Init();
}

void CScrollMapComponent::Render(SDL_Renderer* renderer)
{
	SDL_Rect viewRect = mCamera->GetViewRect();
	viewRect.x = (int)roundf((float)viewRect.x);
	viewRect.y = (int)roundf((float)viewRect.y);

	const SDL_Rect& texRect = mTexture->GetTextureFrame();
	const FVector2D& mapScale = mTransform->GetWorldScale();

	// 텍스처 기준 카메라 좌상단 위치
	int offsetX = viewRect.x % (int)mapScale.x;
	int offsetY = viewRect.y % (int)mapScale.y;
	if (offsetX < 0) offsetX += (int)mapScale.x;
	if (offsetY < 0) offsetY += (int)mapScale.y;

	// 텍스처 크기 기준 변환 상수
	float texWidthPerWorld = (float)texRect.w / mapScale.x;
	float texHeightPerWorld = (float)texRect.h / mapScale.y;

	// 카메라 뷰가 실제 텍스쳐를 넘겼는지 플래그
	bool isOverflowX = offsetX + viewRect.w > (int)mapScale.x;
	bool isOverflowY = offsetY + viewRect.h > (int)mapScale.y;

	if (!isOverflowX && !isOverflowY)
	{
		SDL_Rect srcRect =
		{
			(int)roundf(offsetX * texWidthPerWorld),
			(int)roundf(offsetY * texHeightPerWorld),
			(int)roundf(viewRect.w * texWidthPerWorld),
			(int)roundf(viewRect.h * texHeightPerWorld)
		};
		SDL_Rect dstRect = { 0, 0, viewRect.w, viewRect.h };

		SDL_RenderCopy(renderer, mTexture->GetTexture(), &srcRect, &dstRect);
	}
	else
	{
		// outer는 텍스처 범위를 넘어선 초과 영역의 크기
		int outerW = isOverflowX ? (offsetX + viewRect.w - (int)mapScale.x) : 0;
		int outerH = isOverflowY ? (offsetY + viewRect.h - (int)mapScale.y) : 0;

		// inner는 텍스처 범위 안에 포함되는 영역의 크기
		int innerW = viewRect.w - outerW;
		int innerH = viewRect.h - outerH;

		if (innerH > 0) // 상단
		{
			if (innerW > 0) // 텍스처 왼쪽 내부
			{
				SDL_Rect srcRect =
				{
					(int)roundf(offsetX * texWidthPerWorld),
					(int)roundf(offsetY * texHeightPerWorld),
					(int)roundf(innerW * texWidthPerWorld),
					(int)roundf(innerH * texHeightPerWorld)
				};
				SDL_Rect dstRect = { 0, 0, innerW, innerH };

				SDL_RenderCopy(renderer, mTexture->GetTexture(), &srcRect, &dstRect);
			}
			if (outerW > 0) // 텍스처 오른쪽 외부
			{
				SDL_Rect srcRect =
				{
					0,
					(int)roundf(offsetY * texHeightPerWorld),
					(int)roundf(outerW * texWidthPerWorld),
					(int)roundf(innerH * texHeightPerWorld)
				};
				SDL_Rect dstRect = { innerW, 0, outerW, innerH };

				SDL_RenderCopy(renderer, mTexture->GetTexture(), &srcRect, &dstRect);
			}
		}
		if (outerH > 0) // 하단
		{
			if (innerW > 0) // 텍스처 왼쪽 내부
			{
				SDL_Rect srcRect =
				{
					(int)roundf(offsetX * texWidthPerWorld),
					0,
					(int)roundf(innerW * texWidthPerWorld),
					(int)roundf(outerH * texHeightPerWorld)
				};
				SDL_Rect dstRect = { 0, innerH, innerW, outerH };

				SDL_RenderCopy(renderer, mTexture->GetTexture(), &srcRect, &dstRect);
			}
			if (outerW > 0) // 텍스처 오른쪽 외부
			{
				SDL_Rect srcRect =
				{
					0,
					0,
					(int)roundf(outerW * texWidthPerWorld),
					(int)roundf(outerH * texHeightPerWorld)
				};
				SDL_Rect dstRect = { innerW, innerH, outerW, outerH };

				SDL_RenderCopy(renderer, mTexture->GetTexture(), &srcRect, &dstRect);
			}
		}
	}
	CComponent::Render(renderer);
}

void CScrollMapComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CScrollMapComponent>(this);
}

void CScrollMapComponent::SetTexture(const std::string& key)
{
	mTexture = CAssetManager::GetInst()->GetTextureManager()->GetTexture(key);
}

void CScrollMapComponent::SetFrame(const std::string& key)
{
	const SDL_Rect* const framePtr = CAssetManager::GetInst()->GetSpriteManager()->GetSpriteFrame(key);

	mFrame = *framePtr;
}