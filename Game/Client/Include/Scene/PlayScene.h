#pragma once

#include "Scene.h"

class CPlayScene : public CScene
{
    friend class CSceneManager;

private:
    CPlayScene();
    ~CPlayScene();

public:
    virtual bool Enter() final;
    virtual bool Exit()  final;

    virtual void LoadResources() final;
};