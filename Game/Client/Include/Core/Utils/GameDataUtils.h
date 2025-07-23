#pragma once

#include "../GameInfo.h"

struct FPowerUpData
{
	std::string description1;
	std::string description2;
	int price = 0;
	float statModifier = 0.0f;
};

struct FCharacterData
{
	std::string lastName;
	std::string firstName;
	std::string description1;
	std::string description2;
	std::string startingWeapon;
};

enum class ECharacterType : unsigned char
{
	NONE,
	TRALALA,
	SAHUR,
	BANANINI
};