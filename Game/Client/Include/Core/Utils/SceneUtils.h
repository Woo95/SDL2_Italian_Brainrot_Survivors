#pragma once

enum class EMenuSubState : unsigned char
{
	NONE,
	START,
	MENU
};

enum class EPlaySubState : unsigned char
{
	NONE,
	PLAY,
	PAUSE,
	LVLUP
};

/////////////////////////////////////////

enum class ESceneState : unsigned char
{
	NONE,
	MENU,
	PLAY,
	RESULT
};

enum class ETransition : unsigned char
{
	NONE,
	PUSH,
	POP,
	SWAP,
	CLEAR,
	CLEAR_THEN_PUSH
};