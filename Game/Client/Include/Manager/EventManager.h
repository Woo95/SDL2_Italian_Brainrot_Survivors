#pragma once

#include "../Core/Utils/EventUtils.h"

class CEventManager
{
private:
	CEventManager() = default;
	~CEventManager() = default;

private:
	inline static CEventManager* mInst;

	using EventCallback = std::function<void(void*)>;
	std::vector<EventCallback> mListener[(int)EEventType::MAX] = {};

public:
	void AddListener(EEventType type, EventCallback callback)
	{
		mListener[(int)type].emplace_back(callback);
	}
	void ClearAllListener()
	{
		for (int i = 0; i < (int)EEventType::MAX; i++)
			mListener[i].clear();
	}

	void Broadcast(EEventType type, void* data = nullptr)
	{
		for (auto& callback : mListener[(int)type])
		{
			callback(data);
		}
	}

public:
	static CEventManager* GetInst()
	{
		if (!mInst)
			mInst = new CEventManager;
		return mInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};