#pragma once

#include "../GameInfo.h"

enum class EEventType : unsigned char
{
	PLAYER_EXP_GAINED,
	PLAYER_LEVEL_UP,
	PLAYER_HP_CHANGED,
	PLAYER_DIED,
	REGULAR_MOB_SPAWN,
	SUBBOSS_MOB_SPAWN,
	MAX
};