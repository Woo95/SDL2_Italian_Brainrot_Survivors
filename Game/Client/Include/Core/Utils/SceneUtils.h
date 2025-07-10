#pragma once

enum class ESceneState : unsigned char
{
	NONE,
	MENU,
	PLAY,
	PAUSE,
	GAMEOVER
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