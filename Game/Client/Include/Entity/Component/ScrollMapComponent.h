#pragma once

#include "Component.h"

class CCamera;
class CTexture;

class CScrollMapComponent : public CComponent
{
public:
	CScrollMapComponent();
	virtual ~CScrollMapComponent();

private:
	CCamera* mCamera;

	std::shared_ptr<CTexture> mTexture;
	SDL_Rect mFrame;

private:
	virtual bool Init() final;
	virtual void Render(SDL_Renderer* renderer) final;
	virtual void Release() final;

public:
	void SetTexture(const std::string& key);
	void SetFrame(const std::string& key);
};