#include "SFX.h"
#include "../../Core/External/SDL/SDL_mixer.h"
#include "../../Manager/Data/PathManager.h"

CSFX::CSFX()
{
}

CSFX::~CSFX()
{
	if (mSound)
	{
		Mix_FreeChunk(mSound);
		mSound = nullptr;
	}
}

void CSFX::Play()
{
	// 첫번째 인자 (-1): play on the first free channel
	// 세번째 인자  (0): don't loop
	Mix_PlayChannel(-1, mSound, 0);
}

void CSFX::Stop()
{
	const int totalChannels = Mix_AllocateChannels(-1);

	for (int i = 0; i < totalChannels; i++)
	{
		if (Mix_Playing(i) && Mix_GetChunk(i) == mSound)
		{
			Mix_HaltChannel(i);
		}
	}
}

bool CSFX::IsPlaying() const
{
	const int totalChannels = Mix_AllocateChannels(-1);

	for (int i = 0; i < totalChannels; i++)
	{
		if (Mix_Playing(i) && Mix_GetChunk(i) == mSound)
			return true;
	}
	return false;
}

void CSFX::SetVolume(float volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	int scaledVolume = (int)(volume * MIX_MAX_VOLUME);

	Mix_VolumeChunk(mSound, scaledVolume);
}

bool CSFX::LoadSound(const char* fileName)
{
	std::string soundPath = CPathManager::GetInst()->FindPath(SOUND_PATH);
	soundPath += (std::string)fileName;

	mSound = Mix_LoadWAV(soundPath.c_str());

	return mSound != nullptr;
}