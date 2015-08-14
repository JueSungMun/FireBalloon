#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#include <time.h>
#include <string>
#include <cstdlib>
#include <d3d9.h>
#include <d3dx9.h>
#include <List>
#include <iostream>
#include <memory>

#include "Enemy.h"
#include "TextDisplay.h"
#include "ObjectManager.h"

#pragma warning( default : 4996 ) 
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define IMG_FIREBALLOON "..\\Resource\\bird_test\\fireballoon_t.png"
#define IMG_BIRD_RIGHT "..\\Resource\\bird_test\\sprite_bird_right.png"
#define IMG_BIRD_LEFT "..\\Resource\\bird_test\\sprite_bird_left.png"
#define IMG_BG "..\\Resource\\bird_test\\background.png"
#define IMG_GOALLINE "..\\Resource\\Goal_line.png"	

#define IMG_0 "..\\Resource\\Literal\\0.png"	
#define IMG_1 "..\\Resource\\Literal\\1.png"	
#define IMG_2 "..\\Resource\\Literal\\2.png"
#define IMG_3 "..\\Resource\\Literal\\3.png"
#define IMG_4 "..\\Resource\\Literal\\4.png"
#define IMG_5 "..\\Resource\\Literal\\5.png"
#define IMG_6 "..\\Resource\\Literal\\6.png"
#define IMG_7 "..\\Resource\\Literal\\7.png"
#define IMG_8 "..\\Resource\\Literal\\8.png"
#define IMG_9 "..\\Resource\\Literal\\9.png"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 700
#define MAX_ENEMY 3
#define BIRD_RECT_LEFT 0
#define BIRD_RECT_TOP 0
#define BIRD_RECT_RIGHT 81
#define BIRD_RECT_BOTTOM 56


