#include "Score.h"


Score::Score(void)
{
}

Score::~Score(void)
{
}

void Score::initScore(HWND hwnd)
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

void Score::showText(std::string s)
{
	std::string score = "SCORE ";
	score.append(s);
	DrawText(hDC, score.c_str(), score.length(), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

