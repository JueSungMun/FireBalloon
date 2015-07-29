#include "Audio.h"

Audio::Audio()
{
	//must call this for COM
	CoInitializeEx( NULL, COINIT_MULTITHREADED );

	//create the engine
	if( FAILED( XAudio2Create( &g_engine ) ) )
	{
		CoUninitialize();
		//return -1;
	}

	//create the mastering voice
	if( FAILED( g_engine->CreateMasteringVoice( &g_master ) ) )
	{
		g_engine->Release();
		CoUninitialize();
		//return -2;
	}
}

INT Audio::LoadTheSource(const char* resource)
{

	//helper class to load wave files; trust me, this makes it MUCH easier
	//AudioExample buffer;

	//load a wave file
	if( !buffer.load(resource) )
	{
		g_engine->Release();
		CoUninitialize();
		return -3;
	}
	//create the source voice, based on loaded wave format
	if( FAILED( g_engine->CreateSourceVoice( &g_source, buffer.wf() ) ) )
	{
		g_engine->Release();
		CoUninitialize();
		return -4;
	}
	g_source->Start();
	g_source->SubmitSourceBuffer( buffer.xaBuffer() );

	//start consuming audio in the source voice
	
	
	//{
	
	
	//simple message loop
	//while( MessageBox( 0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO ) == IDYES )
	//{
		//play the sound
			
	//}

	//getchar();
	//release the engine, NOT the voices!
	
}


void Audio::Play()
{

	
}
