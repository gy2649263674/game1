#include <iostream>
#include <easyx.h>
#include <ctime>
#include <Windows.h>
#include "Timer.h"
#include "Anime.h"
#include "board.h"
#include "Character.h"
#include "Draw.h"
#define WIDTH 720
#define LENGTH 900
#define BOARD_GAP 50
using namespace std;
int board_speed;
Board board[150];
Board roof;
IMAGE character_img[10];
IMAGE character_img_mask[10];
IMAGE character_img_l[10];
IMAGE character_img_l_mask[10];
IMAGE background;
IMAGE board_img[4];
IMAGE conveyor_right;
IMAGE conveyor_left;
IMAGE fake;
IMAGE health[2];
IMAGE roof_img;
Character role;
ExMessage msg = { 0 };
int act = 1;
//游戏初始化
void gameInit()
{
	loadimage(health, "./picture/health/health1.png", 40, 40);
	loadimage(health+1, "./picture/health/health1_mask.png", 40, 40);
	loadimage(&roof_img, "./picture/ceiling.png");
	loadimage(board_img, "./picture/normal.png");
	loadimage(board_img+1, "./picture/nails.png");
	loadimage(character_img, "./picture/character 1/stand.png", 60, 60);
	loadimage(character_img+1, "./picture/character 1/run1.png", 60, 60);
	loadimage(character_img+2, "./picture/character 1/run2.png", 60, 60);
	loadimage(character_img+3, "./picture/character 1/run3.png", 60, 60);
	loadimage(character_img+4, "./picture/character 1/run4.png", 60, 60);
	loadimage(character_img+5, "./picture/character 1/falling.png", 60, 60);
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
	loadimage(&conveyor_left, "./picture/conveyor_left.png");
	loadimage(&conveyor_right, "./picture/conveyor_right.png");
	loadimage(&fake, "./picture/fake.png");
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 150; i++)
	{
		if (i == 0)
		{
			board[i].y = rand() % (WIDTH / 3) + 100;
			board[i].type = 0;
		}
		else
		{
			board[i].y = BOARD_GAP + board[i - 1].y;
			int judge = rand() % 10;
			int btype = rand() % 5;
			if (judge > 6 && btype != 0)
			{
				board[i].type = 0;
			}
			else
			{
				board[i].type = btype;
			}
		}
		board[i].x = rand() % (LENGTH-100);
		//board[i].y = rand() % (WIDTH);
		board[i].len = 100;
		board[i].exist = true;
		board[i].used = false;
		board[i].stay = 0;
	}
	role.h = 60;
	role.x = board[0].x + board[0].len / 2 - role.h / 2;
	role.y = board[0].y - role.h;
	role.health = 3;
	role.ob = -1;
	roof.type = 1;
	roof.len = LENGTH;
	roof.used = false;
	roof.x = 0;
	roof.y = 0;
	board_speed = 1;
}
//游戏绘制
//类型0为普通，1为尖刺,2为假板，3为左传送，4为右传送
void gamedraw()
{
	putimage(0, 0, &roof_img);
	putimage(400, 0, &roof_img);
	putimage(800, 0, &roof_img);
	for (int i = 0; i < role.health; i++)
	{
		putimage(600 + i * 40, 10, &health[1], SRCAND);
		putimage(600 + i * 40, 10, &health[0], SRCPAINT);
	}
	for (int i = 0; i < 150; i++)
	{
		if (board[i].type == 0)
		{
			putimage(board[i].x, board[i].y, &board_img[0]);
		}
		else if (board[i].type == 1)
		{
			putimage(board[i].x, board[i].y, &board_img[1]);
		}
		else if (board[i].type == 2)
		{
			putimage(board[i].x, board[i].y, 96, 217/6, &fake, 0, 0);
		}
		else if (board[i].type == 3)
		{
			putimage(board[i].x, board[i].y, 96, 16, &conveyor_left, 0, 0);
			//Anime::anime_conveyor_left(i);
		}
		else if (board[i].type == 4)
		{
			putimage(board[i].x, board[i].y, 96, 16, &conveyor_right, 0, 0);
			//Anime::anime_conveyor_right(i);
		}
	}
	if (msg.vkcode == VK_LEFT)
	{
		putimage(role.x, role.y, &character_img_l_mask[act/4], SRCAND);
		putimage(role.x, role.y, &character_img_l[act/4], SRCPAINT);
	}
	else if (msg.vkcode == VK_RIGHT)
	{
		putimage(role.x, role.y, &character_img_mask[act/4], SRCAND);
		putimage(role.x, role.y, &character_img[act/4], SRCPAINT);
	}
	else
	{
		putimage(role.x, role.y, &character_img_mask[0], SRCAND);
		putimage(role.x, role.y, &character_img[0], SRCPAINT);
	}
	
}

void board_move()
{
	
	for (int i = 0; i < 150; i++)
	{
		board[i].y -= 2;
		if (board[i].y < 0)
		{
			board[i].y = 150 * BOARD_GAP;
			board[i].x = rand() % (LENGTH - 150);
			board[i].type = rand() % 5;
			board[i].used = false;
			board[i].stay = 0;
		}
	}
}

int main()
{
	clock_t begintime = clock();
	//创建图形窗口
	initgraph(LENGTH, WIDTH);
	gameInit();
	while (1)
	{
		/*if ((clock() - begintime) / 1000 > 5)
		{
			board_speed+=1;
			begintime = clock();
		}*/
		BeginBatchDraw();
		cleardevice();
		
		if (Timer::timer(20, 1))
			role.character_move();
		if (role.is_dead())
		{
			return 0;
		}
		if(Timer::timer(5,0))
			board_move();
		gamedraw();
		EndBatchDraw();
	}
	










	system("pause");
}