#include "PlayerProfile.h"
#include "GameDataManager.h"
#include "CharacterDataManager.h"
#include "PowerUpDataManager.h"

CPlayerProfile::CPlayerProfile()
{
}

CPlayerProfile::~CPlayerProfile()
{
}

const std::string& CPlayerProfile::GetName() const
{
    const FCharacterData& charData = CGameDataManager::GetInst()->GetCharacterDataManager()->GetCharacterData(mType);

    return charData.lastName;
}

bool CPlayerProfile::PurchaseMenuPowerUp(EPowerUpType type)
{
    const FPowerUpData& powerUpData = CGameDataManager::GetInst()->GetPowerUpDataManager()->GetPowerUpData(type);

    if (mMoneyBalance < powerUpData.price)
        return false;

	mMoneyBalance -= powerUpData.price;
    mMenuPowerUps[(int)type] += 1;

	return true;
}

bool CPlayerProfile::RefundAllMenuPowerUp()
{
    CPowerUpDataManager* PowerUpDataManager = CGameDataManager::GetInst()->GetPowerUpDataManager();

    for (int i = 0; i < (int)EPowerUpType::MAX; i++)
    {
        if (mMenuPowerUps[i])
        {
            const EPowerUpType& type = static_cast<EPowerUpType>(i);

            mMoneyBalance += mMenuPowerUps[i] * PowerUpDataManager->GetPowerUpData(type).price;
            mMenuPowerUps[i] = 0;
        }
    }
    return true;
}