﻿#define CRT_SECURE_NO_WARNINGS 1
#include"all.h"
#include"Anime.h"
void Anime::ppt(Atlas* images, int delt,int trans)
{
	//for(int i = 0;i<)
	//(cur_back + 1 * delt + back_ground->get_size()) % back_ground->get_size();
}
void draw_lucency(int x, int y, IMAGE* ori, IMAGE* mask)
{
	BeginBatchDraw();
	putimage(x, y, mask, SRCAND);
	putimage(x, y, ori, SRCPAINT);
	EndBatchDraw();
	return;
}
IMAGE* Atlas::get_image(int index, int cate)
{
	if (index >= 0)
	{
		if (cate == 0 && index < arr.size())
			return arr[index];
		else if (index < arr_mask.size())
		{
			return arr_mask[index];
		}
	}
	return NULL;
}

void Atlas::add_image(const char* rootdir, const char* filename, int w, int h, int n, const char* filetype, const char* mask)
{
	string t = PICDIR + string("\\") + string(rootdir) + "\\" + string(filename) + mask;
	//图片标号从1开始
	for (int i = 1; i <= n; i++)
	{
		fstream in;
		IMAGE* temp = new IMAGE;
		string path = t;
		if (n > 1)
		{
			path += " (" + to_string(i) + ")";
		}
		path += filetype;
		in.open(path, std::ios::in);
		if (in.is_open() == false)
		{
			delete temp;
			printf("\033[31m%s没有成功导入检查路径\033[0m\n", &path[0]);
			perror("\033[31m\n");
			return;
		}
		loadimage(temp, &path[0], w, h);
		if (mask == "")
		{
			arr.push_back(temp);
		}
		else
		{

			arr_mask.push_back(temp);
		}
	}
	return;
}