#pragma once

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

