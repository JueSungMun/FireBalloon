#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

class Score
{
private:
	PAINTSTRUCT ps;
    HDC hDC;
	RECT rc;
public:
	Score(void);
	~Score(void);

	void initScore(HWND);
	void showText(std::string);
	
};

