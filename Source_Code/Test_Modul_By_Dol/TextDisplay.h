#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

class TextDisplay
{
private:
	PAINTSTRUCT ps;
    HDC hDC;
	RECT rc;
public:
	TextDisplay(void);
	~TextDisplay(void);

	void initScore(HWND);
	void initLife(HWND);
	void showScore(std::string);
	void showLife(std::string);
};

