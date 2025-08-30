#pragma once

#include "../GameInfo.h"

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

enum class ECharacterType : signed char
{
	NONE = -1,
	TRALALA,
	SAHUR,
	BANANINI,
	MAX
};

////////////////////////////////////////

struct FPowerUpData
{
	EPowerUpType type;
	std::string name;
	std::string description1;
	std::string description2;
	int price = 0;
	float statModifier = 0.0f;
};

struct FCharacterData
{
	ECharacterType type;
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