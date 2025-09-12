#include "PlayerProfile.h"
#include "GameDataManager.h"
#include "CharacterDataManager.h"
#include "ItemDataManager.h"

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
    const FPowerUpData& powerUpData = CGameDataManager::GetInst()->GetItemDataManager()->GetPowerUpData(type);

    if (mMoneyBalance < powerUpData.price)
        return false;

	mMoneyBalance -= powerUpData.price;
    mMenuPowerUps[(int)type] += 1;

	return true;
}

bool CPlayerProfile::RefundAllMenuPowerUp()
{
    CItemDataManager* itemDataManager = CGameDataManager::GetInst()->GetItemDataManager();

    for (int i = 0; i < (int)EPowerUpType::MAX; i++)
    {
        if (mMenuPowerUps[i])
        {
            const EPowerUpType& type = static_cast<EPowerUpType>(i);

            mMoneyBalance += mMenuPowerUps[i] * itemDataManager->GetPowerUpData(type).price;
            mMenuPowerUps[i] = 0;
        }
    }
    return true;
}