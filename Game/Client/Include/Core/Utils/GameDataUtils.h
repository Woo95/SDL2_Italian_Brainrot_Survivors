#pragma once

#include "../GameInfo.h"

enum class ERegularMobType : signed char
{
	NONE = -1,
	SKELETON,
	SKELETON_KNIFE,
	SKULL,
	SKELETON_PANTHER,
	SKELETON_XL,
	SKELETON_MAD,
	SKELETON_ANGEL,
	SKELETON_NINJA,
	SKELETON_DRAGON,
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
	MOVE_SPEED,
	MAGNET,
	GROWTH,
	GREED,
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

// RUNTIME DATAs //

struct FSelectableItem
{
public:
	FSelectableItem() = default;
	FSelectableItem(EItemCategory c, int t, int l) : category(c), type(t), level(l) {}

	EItemCategory category = EItemCategory::NONE;
	signed char type = -1;
	int level = 0;
};

struct FPowerUp
{
	EPowerUpType type;
	int level;
};

struct FWeapon
{
	class CWeaponComponent* ptr;
};

////////////////////////////////////////

// STATIC DATAs //

struct FRegularMobData
{
	ERegularMobType type = ERegularMobType::NONE;
	float baseHP        = 0.0f;
	float baseAttack    = 0.0f;
	float baseMoveSpeed = 0.0f;
	float baseExp       = 0.0f;
};

struct FSubBossMobData
{
	ESubBossMobType type = ESubBossMobType::NONE;
	float baseHP        = 0.0f;
	float baseAttack    = 0.0f;
	float baseMoveSpeed = 0.0f;
	float baseExp       = 0.0f;
};

struct FCharacterData
{
	ECharacterType type = ECharacterType::NONE;
	std::string lastName;
	std::string firstName;
	std::string description1;
	std::string description2;
	std::string startingWeapon;

	float baseMaxHP;
	float baseAttack;
	float baseDefense;
	float baseMoveSpeed;
	float basePickUpRange;
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
	int   levelReached = 0;
	int   goldEarned   = 0;
	int   killCount    = 0;
};