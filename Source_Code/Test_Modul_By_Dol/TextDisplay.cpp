#include "TextDisplay.h"


TextDisplay::TextDisplay(void)
{
}

TextDisplay::~TextDisplay(void)
{
}

void TextDisplay::initScore(HWND hwnd)
{
    hDC=BeginPaint(hwnd,&ps);
    EndPaint(hwnd,&ps);
	rc.left = 400;
	rc.right = 580;
	rc.top = 20;
	rc.bottom = 90;
	SelectObject(hDC, GetStockObject(DEFAULT_PALETTE));
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 0, 0));
}

void TextDisplay::initLife(HWND hwnd)
{
    hDC=BeginPaint(hwnd,&ps);
	rc.left = 20;
	rc.right = 200;
	rc.top = 20;
	rc.bottom = 90;
	SelectObject(hDC, GetStockObject(DEFAULT_PALETTE));
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 255));
	EndPaint(hwnd,&ps);
}

void TextDisplay::showScore(std::string s)
{
	std::string score = "SCORE ";
	score.append(s);
	
	//TextOut(hDC, rc.left, rc.top, (LPCSTR)score.data(), 15);
	DrawText(hDC, score.c_str(), score.length(), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
}

void TextDisplay::showLife(std::string s)
{
	std::string score = "LIFE ";
	score.append(s);
//	DrawText(hDC, score.c_str(), score.length(), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
