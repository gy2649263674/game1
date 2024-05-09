﻿
#include <iostream>
#include <easyx.h>
#include <ctime>
#include <Windows.h>
#include"all.h"
#include "Timer.h"
#include "Anime.h"
#include "board.h"
#include "Character.h"
#include "Draw.h"
#include"scene.h"
#include<system.h>
using namespace std;
const  int fps = 60;
const  int frame = 1000 / 60;
int Timer::time = 0;
IMAGE cursor[2];
IMAGE arrow[2];
bool EXIT = false;
Atlas back;
IMAGE border[2];
Board board[10];
IMAGE character_img[10];
IMAGE character_img_mask[10];
IMAGE character_img_l[10];
IMAGE character_img_l_mask[10];
IMAGE background;
IMAGE board_img[4];
IMAGE conveyor_right;
IMAGE conveyor_left;
IMAGE fake;
Character role;
ExMessage msg = { 0 };
int act = 1;


Start se;
void creatgame()
{
	initgraph(MAINW, MAINH);
	cleardevice();
	HWND handle = GetHWnd();
	MoveWindow(HWND(handle), MAINX, MAINY, MAINW, MAINH, true);
}
void loadresource()
{
	//arrow = new (IMAGE*)[2];
	loadimage(border, "picture/button/border.png", Button::wordsw, Button::h);
	loadimage(border + 1, "picture/button/border_mask.png", Button::wordsw, Button::h);
	loadimage(&arrow[0], "picture/button/arrow.png");
	loadimage(&arrow[1], "picture/button/arrow_mask.png");
	loadimage(cursor, "picture/button/cursor.ico");
	loadimage(cursor + 1, "picture/button/cursor_mask.ico");
}
void gameInit()
{
	loadresource();
	loadimage(board_img, "./picture/unit/normal.png");
	loadimage(board_img + 1, "./picture/unit/nails.png");
	loadimage(character_img, "./picture/character 1/stand.png", 60, 60);
	loadimage(character_img + 1, "./picture/character 1/run1.png", 60, 60);
	loadimage(character_img + 2, "./picture/character 1/run2.png", 60, 60);
	loadimage(character_img + 3, "./picture/character 1/run3.png", 60, 60);
	loadimage(character_img + 4, "./picture/character 1/run4.png", 60, 60);
	loadimage(character_img + 5, "./picture/character 1/falling.png", 60, 60);
	loadimage(character_img_mask, "./picture/character 1/stand_mask.png", 60, 60);
	loadimage(character_img_mask + 1, "./picture/character 1/run1_mask.png", 60, 60);
	loadimage(character_img_mask + 2, "./picture/character 1/run2_mask.png", 60, 60);
	loadimage(character_img_mask + 3, "./picture/character 1/run3_mask.png", 60, 60);
	loadimage(character_img_mask + 4, "./picture/character 1/run4_mask.png", 60, 60);
	loadimage(character_img_mask + 5, "./picture/character 1/falling_mask.png", 60, 60);
	loadimage(character_img_l, "./picture/character 1/stand.png", 60, 60);
	loadimage(character_img_l + 1, "./picture/character 1/run1_l.png", 60, 60);
	loadimage(character_img_l + 2, "./picture/character 1/run2_l.png", 60, 60);
	loadimage(character_img_l + 3, "./picture/character 1/run3_l.png", 60, 60);
	loadimage(character_img_l + 4, "./picture/character 1/run4_l.png", 60, 60);
	loadimage(character_img_l + 5, "./picture/character 1/falling.png", 60, 60);
	loadimage(character_img_l_mask, "./picture/character 1/stand_mask.png", 60, 60);
	loadimage(character_img_l_mask + 1, "./picture/character 1/run1_l_mask.png", 60, 60);
	loadimage(character_img_l_mask + 2, "./picture/character 1/run2_l_mask.png", 60, 60);
	loadimage(character_img_l_mask + 3, "./picture/character 1/run3_l_mask.png", 60, 60);
	loadimage(character_img_l_mask + 4, "./picture/character 1/run4_l_mask.png", 60, 60);
	loadimage(character_img_l_mask + 5, "./picture/character 1/falling_mask.png", 60, 60);
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 10; i++)
	{
		if (i == 0)
		{
			board[i].y = rand() % (WIDTH / 3) + 100;
		}
		else
		{
			board[i].y = BOARD_GAP + board[i - 1].y;
		}
		board[i].x = rand() % (LENGTH - 150);
		board[i].y = rand() % (WIDTH);
		board[i].len = 100;
		board[i].exist = true;
		board[i].type = rand() % 5;
	}
	role.h = 60;
	role.x = board[0].x + board[0].len / 2 - role.h / 2;
	role.y = board[0].y - role.h;
	role.health = 5;
	role.ob = -1;
}
void gamedraw()
{
	for (int i = 0; i < 10; i++)
	{
		if (board[i].type == 0)
		{
			putimage(board[i].x, board[i].y, &board_img[0]);
		}
		else if (board[i].type == 1)
		{
			putimage(board[i].x, board[i].y, &board_img[1]);
		}
	}
	if (msg.vkcode == VK_LEFT)
	{
		putimage(role.x, role.y, &character_img_l_mask[act / 4], SRCAND);
		putimage(role.x, role.y, &character_img_l[act / 4], SRCPAINT);
	}
	else if (msg.vkcode == VK_RIGHT)
	{
		putimage(role.x, role.y, &character_img_mask[act / 4], SRCAND);
		putimage(role.x, role.y, &character_img[act / 4], SRCPAINT);
	}
	else
	{
		putimage(role.x, role.y, &character_img_mask[0], SRCAND);
		putimage(role.x, role.y, &character_img[0], SRCPAINT);
	}
	msg.message = 0;
}

void board_move()
{

	for (int i = 0; i < 10; i++)
	{
		board[i].y -= 1;
		if (board[i].y < 0)
		{
			board[i].y = 8 * BOARD_GAP;
			board[i].x = rand() % (LENGTH - 150);
			board[i].type = rand() % 3;
		}
	}
}

void tempgameing()
{
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, se.get_background());
		gamedraw();
		if (Timer::timer(20, 1))
			role.character_move();
		if (Timer::timer(5, 0))
			board_move();
		EndBatchDraw();
	}

	system("pause");
}





//void trace(IMAGE* a = NULL, IMAGE* b = NULL)
//{
//	creatgame();
//	setbkcolor(WHITE);
//	int fps = 144;
//	Button ba;
//	Atlas bk;
//	ba.init("exit", "fuck");
//	while (1)
//	{
//		while (peekmessage(&msg, EX_MOUSE | EX_KEY))
//		{
//			int st = clock();
//			fillcircle(msg.x, msg.y, 5);
//			BeginBatchDraw();
//			cleardevice();
//			putimage(msg.x, msg.y, b, SRCPAINT);
//			putimage(msg.x, msg.y, a);//,SRCAND);
//			clearrectangle(msg.x, msg.y, msg.x + a->getwidth() + 1, msg.y + a->getheight() + 1);
//			draw_lucency(msg.x, msg.y, a, b);
//			EndBatchDraw();
//			getchar();
//			if (msg.vkcode == VK_BACK)
//			{
//				return;
//			}
//			int end = clock();
//			Sleep(max(0, 1000 / fps - (end - st)));
//		}
//	}
//}
//void testmask(IMAGE a[2])
//{
//	trace(&a[0], &a[1]);
//}

void testbutton()
{
	se = Start();
	creatgame();
	gameInit();
	se.enter_scene();
	//Character joker("ch", 4);
	//while (1)
	//{
	//	Timer::beginkeep();
	//	cleardevice();
	//	joker.exhibit(LEFT);
	//	Timer::endkeep();
	//}
	//setbkcolor(BLACK);
	while (1 ^ EXIT)
	{
		while (peekmessage(&msg, EX_KEY | EX_MOUSE))
		{
			StartOpt opt;
			opt = StartOpt(se.process_command(msg));
			if (opt == startgame)
			{
				cout << "start game" << endl;
				tempgameing();
			}
			else if (opt == choose_map)
			{
				se.ChooseMap(msg);
				cout << "choose map" << endl;
			}
			else if (opt == choose_role)
			{
				cout << "choose role" << endl;
			}
			else if (opt == exit_game)
			{
				EXIT = true;
				cout << "exit game" << endl;
			}
		}

	}
	return;
}
void testch()
{


}

int main(void)
{
	//se.enter_scene();
	//testbutton();
	testbutton();
	return 0;

}

