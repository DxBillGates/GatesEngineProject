#include "..\..\Header\Audio\AudioManager.h"

GatesEngine::AudioManager::AudioManager()
{
	Audio::SetAudioEngine();
	audios.resize(32);
	for (auto itr = audios.begin(); itr != audios.end(); ++itr)
	{
		(*itr) = nullptr;
	}
}

GatesEngine::AudioManager::~AudioManager()
{
	for (auto itr = audios.begin(); itr != audios.end(); ++itr)
	{
		delete (*itr);
	}
	audios.clear();
}

void GatesEngine::AudioManager::Add(Audio * newAudio)
{
	for (auto itr = audios.begin(); itr != audios.end(); ++itr)
	{
		if ((*itr) == nullptr)
		{
			(*itr) = newAudio;
			return;
		}
	}
	audios.push_back(newAudio);
}

void GatesEngine::AudioManager::Add(AudioData * newAudioData, const char* tag)
{
	for (auto itr = audios.begin(); itr != audios.end(); ++itr)
	{
		if ((*itr) == nullptr)
		{
			(*itr) = new Audio(newAudioData,tag);
			return;
		}
	}
	audios.push_back(new Audio(newAudioData,tag));
}

GatesEngine::Audio * GatesEngine::AudioManager::Use(const char * tag)
{
	for (auto itr = audios.begin(); itr != audios.end(); ++itr)
	{
		if ((*itr)->GetTag() == tag)
		{
			return (*itr);
		}
	}
#ifdef _DEBUG
	printf("%s‚Í“o˜^‚³‚ê‚Ä‚¢‚Ü‚¹‚ñ\n", tag);
#endif

	return nullptr;
}
