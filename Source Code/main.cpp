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
	EGERGB(238,228,218), // 2�ı���ɫ 
	EGERGB(236,224,200), // 4�ı���ɫ 
	EGERGB(242,177,121), // 8�ı���ɫ
	EGERGB(245,149,99), // 16�ı���ɫ 
	EGERGB(245,124,95), // 32�ı���ɫ
	EGERGB(246,93,59), // 64�ı���ɫ 
	EGERGB(237,206,113),  // 128�ı���ɫ 
	EGERGB(237,204,97), // 256�ı���ɫ
	EGERGB(228,192,42), // 512��1024�ı���ɫ
	EGERGB(235,195,1) // �������ı���ɫ 
};

color_t numftcolor[] = 
{
	EGERGB(119,110,101), // 2��4��ǰ��ɫ 
	EGERGB(255,245,239) // ��������ǰ��ɫ 
};

color_t blank_color = EGERGB(204,192,178); // �հ׷������ɫ 

color_t canvas_color = EGERGB(187,173,160); // ������ɫ 

color_t panel_color = EGERGB(251,248,239); // �����ɫ���ײ㱳��ɫ�� 

enum{
	play, // ��Ϸģʽ 
	end  // OVERģʽ 
};

enum{
	try_again,  // ѡ�--���¿�ʼ 
	exit_game  // ѡ�--�˳���Ϸ 
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
			
			if(isFull(bd)) // ֻ�е���������ʱ����ж��Ƿ�Game Over����߳���Ч�� 
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
