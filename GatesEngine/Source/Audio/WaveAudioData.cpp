#include "..\..\Header\Audio\WaveAudioData.h"

GatesEngine::AudioData::AudioData(const char * filepath)
{
	using namespace std;

	RiffHeader riffHeader;
	FormatChunk fmtChunk;
	Chunk chunk;

	ifstream file;
	file.open(filepath, ios_base::binary);
	Skip("RIFF", file);
	file.read((char*)&riffHeader, sizeof(riffHeader));
	Skip("fmt ", file);
	file.read((char*)&fmtChunk, sizeof(fmtChunk));
	Skip("data", file);
	file.read((char*)&chunk, sizeof(chunk));

	//波形データの読み込み
	buffer = new char[chunk.size];
	file.read(buffer, chunk.size);
	file.close();

	memcpy(&waveFormatEx, &fmtChunk.fmt, sizeof(fmtChunk.fmt));
	waveFormatEx.wBitsPerSample = waveFormatEx.nBlockAlign * 8 / waveFormatEx.nChannels;

	audioBuffer.pAudioData = (BYTE*)buffer;
	audioBuffer.Flags = XAUDIO2_END_OF_STREAM;
	audioBuffer.AudioBytes = chunk.size;
}

GatesEngine::AudioData::~AudioData()
{
	delete[] buffer;
}

WAVEFORMATEX * GatesEngine::AudioData::GetWaveFormatEx()
{
	return &waveFormatEx;
}

XAUDIO2_BUFFER * GatesEngine::AudioData::GetAudioBuffer()
{
	return &audioBuffer;
}

char * GatesEngine::AudioData::GetBuffer()
{
	return buffer;
}

void GatesEngine::AudioData::Skip(std::string target, std::ifstream & file)
{
	auto currentPos = file.tellg();
	std::string s = "";
	int i = 0;
	while (s != target && !file.eof())
	{
		char read;
		file.read((char*)&read, sizeof(read));
		if (read == target[i])
		{
			++i;
			s += read;
		}
		else
		{
			i = 0;
			s = "";
		}
	}

	if (s == target)
	{
		int size = (int)target.size();
		Skip(-(size), file);
	}
	else
	{
		file.seekg(((int)currentPos), std::ios_base::beg);
	}
}

void GatesEngine::AudioData::Skip(int byte, std::ifstream & file)
{
	auto currentPos = file.tellg();
	file.seekg((((int)currentPos) + byte), std::ios_base::beg);
}
