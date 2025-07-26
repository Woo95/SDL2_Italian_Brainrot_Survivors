#include "PlayerState.h"
#include "GameDataManager.h"
#include "PowerUpDataManager.h"

CPlayerState::CPlayerState()
{

}

CPlayerState::~CPlayerState()
{

}

bool CPlayerState::PurchasePowerUp(EPowerUpType type)
{
    const FPowerUpData& powerUpData = CGameDataManager::GetInst()->GetPowerUpDataManager()->GetPowerUpData(type);

    if (mMoneyBalance < powerUpData.price)
        return false;

    mMoneyBalance -= powerUpData.price;

    mOwnedPowerUp[(int)type] = true;

    return true;
}

bool CPlayerState::RefundAllPowerUp()
{
    CPowerUpDataManager* PowerUpDataManager = CGameDataManager::GetInst()->GetPowerUpDataManager();

    for (int i = 0; i < (int)EPowerUpType::MAX; i++)
    {
        if (mOwnedPowerUp[i])
        {
            const EPowerUpType& type = static_cast<EPowerUpType>(i);

            mMoneyBalance += PowerUpDataManager->GetPowerUpData(type).price;
            mOwnedPowerUp[i] = false;
        }
    }
    return true;
}