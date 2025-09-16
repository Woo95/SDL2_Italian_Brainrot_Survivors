#pragma once

#include "../GameInfo.h"

enum class ERegularMobType : signed char
{
	NONE = -1,
	SKELETON,
	MAX
};

enum class ESubBossMobType : signed char
{
	NONE = -1,
	REAPER,
	DROWNER,
	TRICKSTER,
	STALKER,
	MADDENER,
	ENDER,
	MAX
};

enum class ECharacterType : signed char
{
	NONE = -1,
	TRALALA,
	SAHUR,
	BANANINI,
	MAX
};

enum class EItemCategory : signed char
{
	NONE = -1,
	POWERUP,
	WEAPON,
	CONSUMABLE,
	MAX
};

enum class EPowerUpType : signed char
{
	NONE = -1,
	MIGHT,
	ARMOR,
	MAX_HEALTH,
	RECOVERY,
	ATTACK_SPEED,
	MOVE_SPEED,
	MAGNET,
	GROWTH,
	MAX
};

enum class EWeaponType : signed char
{
	NONE = -1,
	BUBBLE,
	BAT,
	BANANA,
	MAX
};

enum class EConsumableType : signed char
{
	NONE = -1,
	COIN_BAG,
	CHICKEN,
	MAX
};

////////////////////////////////////////

struct FItem
{
	EItemCategory category = EItemCategory::NONE;
	signed char type = -1;
	int level = 0;
};

struct FCharacterData
{
	ECharacterType type = ECharacterType::NONE;
	std::string lastName;
	std::string firstName;
	std::string description1;
	std::string description2;
	std::string startingWeapon;

	float baseMaxHp;
	float baseAttack;
	float baseDefense;
	float baseAttackSpeed;
	float baseMoveSpeed;
	float basePickUpRange;
	float baseGrowthExp;
};

struct FPowerUpData
{
	EPowerUpType type = EPowerUpType::NONE;
	std::string name;
	std::string description;
	int price = 0;
	float statModifier = 0.0f;
};

struct FWeaponData
{
	EWeaponType type = EWeaponType::NONE;
	std::string name;
	std::string description;
};

struct FConsumableData
{
	EConsumableType type = EConsumableType::NONE;
	std::string name;
	std::string description;
};

struct FResultData
{
	float survivedTime = 0.0f;
	int levelReached = 0;
	int goldEarned = 0;
	int killCount = 0;
};