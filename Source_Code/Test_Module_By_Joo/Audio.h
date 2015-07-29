#include "AudioLib.h"

class Audio
{
private:
	AudioLib buffer;
	IXAudio2* g_engine;
	IXAudio2MasteringVoice* g_master;
	IXAudio2SourceVoice* g_source;
	
public:
	Audio();
	INT LoadTheSource(const char* resource);
	~Audio()
	{
		g_engine->Release();
		CoUninitialize();
	}
	void Play();
	void Stop();
};