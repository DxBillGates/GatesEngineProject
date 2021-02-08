#pragma once
#include "WaveAudioData.h"
namespace GatesEngine
{
	class Audio : public IXAudio2VoiceCallback
	{
	private:
		static IXAudio2* xAudioEngine;
		static IXAudio2MasteringVoice* masterVoice;
		IXAudio2SourceVoice* sourceVoice;
		AudioData* pSoundData;
		bool isStart;
		bool isPlay;
		bool isEnd;
		const char* tag;
	public:
		Audio(AudioData* soundData,const char* tag);
		~Audio();
		static void SetAudioEngine();
		void CreateVoice();
		void Start();
		bool GetIsStart();
		bool GetIsPlay();
		bool GetIsEnd();
		const char* GetTag();
	private:
		void OnVoiceProcessingPassStart(UINT32 BytesRequired) {};
		STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
		STDMETHOD_(void, OnStreamEnd) (THIS) {};
		STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext)
		{
			isStart = true;
			isPlay = true;
			isEnd = false;
		};
		STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext)
		{
			isStart = false;
			isPlay = false;
			isEnd = true;
		};
		STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
		STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
	};

}