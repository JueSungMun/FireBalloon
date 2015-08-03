#include "Button.h"

#include <Windows.h>

Button::Button(RECT rect){this->rect = rect;};

 bool Button::RectCollision(RECT rectA, RECT rectB)
 {
    if(rectA.left > rectB.right)
        return false;
    if(rectA.right < rectB.left)
        return false;
    if(rectA.top > rectB.bottom)
        return false;
    if(rectA.bottom < rectB.top)
        return false;

    return true;
}

bool Button::CheckForButtonPress(HWND hwnd)
{
    POINT mousePos;
    if(GetCursorPos(&mousePos)) //Gets the mousePos on the screen
    {
        if(ScreenToClient(hwnd, &mousePos)) //Sets the mousePos relative to the window
        {
            RECT mouseRect = {mousePos.x, mousePos.y, 1, 1};
            if(RectCollision(rect, mouseRect))
                return true;
            return false;
        }
    }
    return false;
}
