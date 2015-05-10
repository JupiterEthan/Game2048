#include <iostream>
#include <graphics.h>
#include "Board.h"
#include "Cell.h"
#include "functional.h"
#include <fstream> 
using namespace std;

#define LEFT 0
#define UP 1
#define DOWN 2
#define RIGHT 3

#define INVALID -1
#define ENTER -2

color_t numbkcolor[] = 
{
	EGERGB(238,228,218), // 2的背景色 
	EGERGB(236,224,200), // 4的背景色 
	EGERGB(242,177,121), // 8的背景色
	EGERGB(245,149,99), // 16的背景色 
	EGERGB(245,124,95), // 32的背景色
	EGERGB(246,93,59), // 64的背景色 
	EGERGB(237,206,113),  // 128的背景色 
	EGERGB(237,204,97), // 256的背景色
	EGERGB(228,192,42), // 512和1024的背景色
	EGERGB(235,195,1) // 其他数的背景色 
};

color_t numftcolor[] = 
{
	EGERGB(119,110,101), // 2和4的前景色 
	EGERGB(255,245,239) // 其他数的前景色 
};

color_t blank_color = EGERGB(204,192,178); // 空白方格的颜色 

color_t canvas_color = EGERGB(187,173,160); // 画布颜色 

color_t panel_color = EGERGB(251,248,239); // 面板颜色（底层背景色） 

enum{
	play, // 游戏模式 
	end  // OVER模式 
};

enum{
	try_again,  // 选项卡--重新开始 
	exit_game  // 选项卡--退出游戏 
};


int main(int argc, char** argv) {
	
	Board bd;
	int key;
	bool changed;
	Cell cl;
	int mode(play);
	int card(try_again);
	int historyScores = 0;
	fstream file;
	
	file.open("./2048.sav",ios::binary|ios::in);
	
	if(!file)
	{	file.close();
	}
	else
	{
		file.close();
		file.open("./2048.sav",ios::binary|ios::in);
		file.read((char* )&historyScores,sizeof(historyScores));
		file.close();
	}
		
	initGame(bd);
	
	for(;is_run();delay_fps(60))
	{	

		if(mode==play)
		{
			key = checkKeyboard();
		
			if(key>=0)
			{
				changed = addNumbers(bd,key);
			
				historyScores = (historyScores>bd.getScores())?historyScores:bd.getScores();
			
				file.open("./2048.sav",ios::binary|ios::out|ios::trunc);
				file.write((char* )&historyScores,sizeof(historyScores));
				file.close();
			
				if(changed)
				{
					drawBulge(bd,historyScores);
				}
			
				if(!isFull(bd) && changed)
				{
					cl = produceNumber(bd);
					drawProduce(bd,cl,historyScores);
				}
			}
		
			updateGame(bd,historyScores);
			
			if(isFull(bd)) // 只有当棋盘满的时候才判断是否Game Over，提高程序效率 
			{
				if(isOver(bd))
				{
					mode = end;
					continue;
				}
			}
		}
		else if(mode==end)
		{
			key = checkKeyboard();
			if(card==try_again && key==DOWN)
			{
				card = exit_game;
			}
			else if(card==exit_game && key==UP)
			{
				card = try_again; 
			}
			else if(card==try_again && key==ENTER)
			{
				mode = play;
				bd = Board();
				continue;
			}
			else if(card==exit_game && key==ENTER)
			{
				break;
			}
			
			showOver(bd,historyScores,card);
		}
		
	}
	
	closeGame();	
	
	return 0;
}
