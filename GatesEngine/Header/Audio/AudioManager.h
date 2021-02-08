#pragma once
#include "..\Audio\Audio.h"
#include <vector>
namespace GatesEngine
{
	class AudioManager
	{
	private:
		std::vector<Audio*> audios;
	public:
		AudioManager();
		~AudioManager();
		void Add(Audio* newAudio);
		void Add(AudioData* newAudioData,const char* tag);
		Audio* Use(const char* tag);
	};
}
