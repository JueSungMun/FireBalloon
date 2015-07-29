#include "Audio.h"

INT AudioExample::audio()
{
	//must call this for COM
	CoInitializeEx( NULL, COINIT_MULTITHREADED );

	//create the engine
	if( FAILED( XAudio2Create( &g_engine ) ) )
	{
		CoUninitialize();
		return -1;
	}

	//create the mastering voice
	if( FAILED( g_engine->CreateMasteringVoice( &g_master ) ) )
	{
		g_engine->Release();
		CoUninitialize();
		return -2;
	}

	//helper class to load wave files; trust me, this makes it MUCH easier
	AudioExample buffer;

	//load a wave file
	if( !buffer.load( "..\\Resource\\Audio\\lol.wav" ) )
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

	//start consuming audio in the source voice
	g_source->Start();

	//simple message loop
	while( MessageBox( 0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO ) == IDYES )
	{
		//play the sound
		g_source->SubmitSourceBuffer( buffer.xaBuffer() );
	}

	//release the engine, NOT the voices!
	g_engine->Release();

	//again, for COM
	CoUninitialize();
}
