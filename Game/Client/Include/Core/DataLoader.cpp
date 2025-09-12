#include "DataLoader.h"
#include <fstream> // for file input/output
#include <sstream> // for stringstream
#include "../Manager/Data/PathManager.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SpriteManager.h"
#include "../Manager/Data/Resource/AnimationManager.h"
#include "../Resource/Animation.h"
#include "../Manager/Data/Resource/UIManager.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/CharacterDataManager.h"
#include "../Manager/Data/GameData/ItemDataManager.h"

CDataLoader::CDataLoader()
{
}

CDataLoader::~CDataLoader()
{
}

bool CDataLoader::Init()
{
	LoadAllEntityFrameData();
	LoadAllEntityAnimationData();

	LoadAllWidgetData();

	LoadAllCharacterData();
	LoadAllPowerUpData();
	LoadAllWeaponData();

	return true;
}

std::vector<std::string> CDataLoader::Split(const std::string& line, char delimiter)
{
	std::stringstream stream(line);

	std::vector<std::string> row;
	std::string cell;

	while (std::getline(stream, cell, delimiter))
	{
		row.emplace_back(cell);
	}
	return row;
}

void CDataLoader::LoadAllEntityFrameData()
{
	std::string filePath = CPathManager::GetInst()->FindPath(DATA_PATH);
	filePath += "Entity\\Frame.csv";

	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Cannot open file at: " << filePath << "\n";
		return;
	}

	CSpriteManager* SM = CAssetManager::GetInst()->GetSpriteManager();

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		if (line[0] == '#')
			continue;

		std::vector<std::string> row = Split(line, ',');

		const std::string& key = row[0];

		{
			int x = std::stoi(row[1].substr(1));
			int y = std::stoi(row[2]);
			int w = std::stoi(row[3]);
			int h = std::stoi(row[4].substr(0, row[4].length() - 1));

			SM->mSprites[key] = SDL_Rect{ x,y,w,h };
		}
		row.clear();
	}
	file.close();
}

void CDataLoader::LoadAllEntityAnimationData()
{
	std::string filePath = CPathManager::GetInst()->FindPath(DATA_PATH);
	filePath += "Entity\\Animation.csv";

	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Cannot open file at: " << filePath << "\n";
		return;
	}

	CAnimationManager* AM = CAssetManager::GetInst()->GetAnimationManager();

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		if (line[0] == '#')
			continue;

		std::vector<std::string> row = Split(line, ',');

		const std::string& key = row[0];
		EAnimationType     type = static_cast<EAnimationType>(std::stoi(row[1]));
		EAnimationState    state = static_cast<EAnimationState>(std::stoi(row[2]));

		// 애니메이션이 없을 경우, 애니메이션 생성
		AM->CreateAnimation(key);

		CAnimation* animation = AM->GetAnimation(key);

		if (animation)
		{
			std::shared_ptr<FAnimationData> data = std::make_shared<FAnimationData>();

			data->type = type;
			data->isLoop = std::stoi(row[3]) != 0;
			data->intervalPerFrame = std::stof(row[4]);

			int frameCount = std::stoi(row[5]) * 4;
			for (int i = 0; i < frameCount; i += 4)
			{
				int x = std::stoi(row[6 + i].substr(1));
				int y = std::stoi(row[7 + i]);
				int w = std::stoi(row[8 + i]);
				int h = std::stoi(row[9 + i].substr(0, row[9 + i].length() - 1));

				data->frames.emplace_back(SDL_Rect{ x, y, w, h });
			}
			animation->AddState(state, data);
		}
		row.clear();
	}
	file.close();
}

void CDataLoader::LoadAllWidgetData()
{
	std::string filePath = CPathManager::GetInst()->FindPath(DATA_PATH);
	filePath += "Widget\\Widget.csv";

	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Cannot open file at: " << filePath << "\n";
		return;
	}

	CUIManager* UIM = CAssetManager::GetInst()->GetUIManager();

	std::string line;
	while (std::getline(file, line))
	{
		if (line[0] == '#')
			continue;

		std::vector<std::string> row = Split(line, ',');

		const std::string& key = row[1];

		int frameCount = std::stoi(row[2]) * 4;
		for (int i = 0; i < frameCount; i += 4)
		{
			int x = std::stoi(row[3 + i].substr(1));
			int y = std::stoi(row[4 + i]);
			int w = std::stoi(row[5 + i]);
			int h = std::stoi(row[6 + i].substr(1, row[6 + i].length() - 1));

			UIM->mUIs[key].emplace_back(SDL_Rect{ x,y,w,h });
		}
		row.clear();
	}
	file.close();
}

void CDataLoader::LoadAllCharacterData()
{
	std::string filePath = CPathManager::GetInst()->FindPath(DATA_PATH);
	filePath += "GameData\\CHARACTER_DATA.csv";

	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Cannot open file at: " << filePath << "\n";
		return;
	}

	CCharacterDataManager* CDM = CGameDataManager::GetInst()->GetCharacterDataManager();

	std::string line;
	while (std::getline(file, line))
	{
		if (line[0] == '#')
			continue;

		std::vector<std::string> row = Split(line, ',');

		const int typeIdx      = 0;
		const int lastNameIdx  = 1;
		const int firstNameIdx = 2;
		const int desc1Idx     = 3;
		const int desc2Idx     = 4;
		const int weaponIdx    = 5;

		const int hpIdx          = 6;
		const int attackIdx      = 7;
		const int defenseIdx     = 8;
		const int attackSpeedIdx = 9;
		const int moveSpeedIdx   = 10;
		const int pickUpIdx      = 11;
		const int growthIdx      = 12;

		{
			FCharacterData data;
			data.type = static_cast<ECharacterType>(std::stoi(row[typeIdx]));
			data.lastName       = row[lastNameIdx];
			data.firstName      = row[firstNameIdx];
			data.description1   = row[desc1Idx];
			data.description2   = row[desc2Idx];
			data.startingWeapon = row[weaponIdx];

			data.baseAttack      = std::stof(row[attackIdx]);
			data.baseDefense     = std::stof(row[defenseIdx]);
			data.baseMaxHp       = std::stof(row[hpIdx]);
			data.baseAttackSpeed = std::stof(row[attackSpeedIdx]);
			data.baseMoveSpeed   = std::stof(row[moveSpeedIdx]);
			data.basePickUpRange = std::stof(row[pickUpIdx]);
			data.baseGrowthExp   = std::stof(row[growthIdx]);

			CDM->mData[(int)data.type] = data;
		}
		row.clear();
	}
	file.close();
}

void CDataLoader::LoadAllPowerUpData()
{
	std::string filePath = CPathManager::GetInst()->FindPath(DATA_PATH);
	filePath += "GameData\\POWERUP_DATA.csv";

	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Cannot open file at: " << filePath << "\n";
		return;
	}

	CItemDataManager* IDM = CGameDataManager::GetInst()->GetItemDataManager();

	std::string line;
	while (std::getline(file, line))
	{
		if (line[0] == '#')
			continue;

		std::vector<std::string> row = Split(line, ',');

		const int typeIdx     = 0;
		const int nameIdx     = 1;
		const int descIdx     = 2;
		const int priceIdx    = 3;
		const int modifierIdx = 4;

		{
			FPowerUpData data;
			data.type = static_cast<EPowerUpType>(std::stoi(row[typeIdx]));
			data.name = row[nameIdx];
			data.description = row[descIdx];
			data.price = std::stoi(row[priceIdx]);
			data.statModifier = std::stof(row[modifierIdx]);

			
			IDM->mPowerUpData[(int)data.type] = data;
		}
		row.clear();
	}
	file.close();
}

void CDataLoader::LoadAllWeaponData()
{

}