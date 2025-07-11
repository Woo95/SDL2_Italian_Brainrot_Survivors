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
#include "../Manager/Data/GameData/InfoManager.h"

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

	LoadAllCharacterInfo();

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
			animation->AddAnimationState(state, data);
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

void CDataLoader::LoadAllCharacterInfo()
{
	std::string filePath = CPathManager::GetInst()->FindPath(DATA_PATH);
	filePath += "GameData\\Info\\Characters.csv";

	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Cannot open file at: " << filePath << "\n";
		return;
	}

	CInfoManager* IM = CGameDataManager::GetInst()->GetInfoManager();

	std::string line;
	while (std::getline(file, line))
	{
		if (line[0] == '#')
			continue;

		std::vector<std::string> row = Split(line, ',');

		const std::string& key = row[0];

		{
			FCharacterInfo info;
			info.name = row[1];
			info.description1 = row[2];
			info.description2 = row[3];
			info.character = row[4];
			info.weapon = row[5];

			IM->mCharacterInfo[key] = info;
		}
		row.clear();
	}
	file.close();
}