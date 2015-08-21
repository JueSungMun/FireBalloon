#include "All_Header.h"

User::User(LPCWSTR _userName) : score(0), stage(0), userName(_userName), userState(0)
{

}

void User::SetScore(int _score)
{
	score = _score;
}

void User::SetStage(int _stage)
{
	stage = _stage;
}

void User::SetUserState(int _state)
{
	switch(_state)
	{
	case PLAYING_GAME : 
		userState = PLAYING_GAME;
		break;
	case GAME_CLEAR : 
		userState = GAME_CLEAR;
		break;
	case USER_DIE : 
		userState = USER_DIE;
		break;
	default : 
		userState = 0;
		break;
	}
}

int User::GetScore()
{
	return score;
}

int User::GetStageState()
{
	return stage;
}

int User::GetUserState()
{
	return userState;
}

LPCWSTR User::GetName()
{
	return userName;
}