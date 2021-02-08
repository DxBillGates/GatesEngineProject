#include "..\..\Header\Audio\Audio.h"

IXAudio2* GatesEngine::Audio::xAudioEngine = nullptr;
IXAudio2MasteringVoice* GatesEngine::Audio::masterVoice = nullptr;

GatesEngine::Audio::Audio(AudioData * soundData,const char* tag):sourceVoice(nullptr),pSoundData(soundData),isStart(false),isPlay(false),isEnd(false),tag(tag)
{
	CreateVoice();
}

GatesEngine::Audio::~Audio()
{
	if (sourceVoice != nullptr)sourceVoice->Stop();
	delete pSoundData;
}

void GatesEngine::Audio::SetAudioEngine()
{
	XAudio2Create(&xAudioEngine, 0, XAUDIO2_DEFAULT_PROCESSOR);
	xAudioEngine->CreateMasteringVoice(&masterVoice);
}

void GatesEngine::Audio::CreateVoice()
{
	HRESULT result = xAudioEngine->CreateSourceVoice(&sourceVoice, pSoundData->GetWaveFormatEx(), 0, 2.0f, &(*this));
}

void GatesEngine::Audio::Start()
{
	if (!isPlay)
	{
		isEnd = false;
		sourceVoice->SubmitSourceBuffer(pSoundData->GetAudioBuffer());
		sourceVoice->Start();
	}
}

bool GatesEngine::Audio::GetIsStart()
{
	return isStart;
}

bool GatesEngine::Audio::GetIsPlay()
{
	return isPlay;
}

bool GatesEngine::Audio::GetIsEnd()
{
	return isEnd;
}

const char * GatesEngine::Audio::GetTag()
{
	return tag;
}
