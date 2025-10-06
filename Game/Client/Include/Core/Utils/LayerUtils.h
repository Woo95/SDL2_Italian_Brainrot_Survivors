#pragma once

namespace ELayer
{
	enum Type : signed char
	{
		NONE = -1,
		BACKGROUND,
		OBJECT,
		EFFECT,
		MAX
	};
}

namespace ESort
{
	enum Type : signed char
	{
		NONE,
		Y
	};
}