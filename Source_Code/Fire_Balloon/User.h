#pragma once

class User
{
private:
	LPCWSTR userName;
	int score;
	int stage;
	int userState;
public:
	enum {GAME_CLEAR=10, USER_DIE, PLAYING_GAME};
	User(LPCWSTR _userName);
	void SetScore(int _score);
	void SetStage(int _stage);
	void SetUserState(int state);
	int GetScore();
	int GetStageState();
	int GetUserState();
	LPCWSTR GetName();
};