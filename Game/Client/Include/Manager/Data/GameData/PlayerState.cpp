#include "PlayerState.h"
#include "GameDataManager.h"
#include "CharacterDataManager.h"
#include "PowerUpDataManager.h"

CPlayerState::CPlayerState()
{
}

CPlayerState::~CPlayerState()
{
}

const std::string& CPlayerState::GetName() const
{
    const FCharacterData& charData = CGameDataManager::GetInst()->GetCharacterDataManager()->GetCharacterData(mType);

    return charData.lastName;
}

bool CPlayerState::PurchasePowerUp(EPowerUpType type)
{
    const FPowerUpData& powerUpData = CGameDataManager::GetInst()->GetPowerUpDataManager()->GetPowerUpData(type);

    if (mMoneyBalance < powerUpData.price)
        return false;

	mMoneyBalance -= powerUpData.price;
    mPowerUps[(int)type] += 1;

	return true;
}

bool CPlayerState::RefundAllPowerUp()
{
    CPowerUpDataManager* PowerUpDataManager = CGameDataManager::GetInst()->GetPowerUpDataManager();

    for (int i = 0; i < (int)EPowerUpType::MAX; i++)
    {
        if (mPowerUps[i])
        {
            const EPowerUpType& type = static_cast<EPowerUpType>(i);

            mMoneyBalance += mPowerUps[i] * PowerUpDataManager->GetPowerUpData(type).price;
            mPowerUps[i] = 0;
        }
    }
    return true;
}