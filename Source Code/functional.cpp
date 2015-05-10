#include "functional.h"
#include <graphics.h>
#include <string.h>

#define LEFT 0
#define UP 1
#define DOWN 2
#define RIGHT 3

#define INVALID -1
#define ENTER -2

extern color_t numbkcolor[];
extern color_t numftcolor[];
extern color_t blank_color;
extern color_t canvas_color;
extern color_t panel_color;

enum{
	try_again,
	exit_game
};

// initGame

void initGame(Board& bd)
{
	int width = bd.getWidth();
	int height = bd.getHeight();
	
	int lineWidth = bd.getLineWidth();
	
	int topHeight = bd.getTopHeight();
	
	int pwidth = bd.getPwidth();
	int pheight = bd.getPheight();
	
	initgraph(width*pwidth+(width+1)*lineWidth,height*pheight+(height+1)*lineWidth+topHeight);
	setcaption(TEXT("2048 (制作：Hi Ke)"));
	
	setinitmode(INIT_RENDERMANUAL);
	
}


// updateGame

void updateGame(Board& bd,int& historyScores)
{
	int pwidth = bd.getPwidth();
	int pheight = bd.getPheight();
	
	int lineWidth = bd.getLineWidth();
	
	int topHeight = bd.getTopHeight();
	
	int width = bd.getWidth();
	int height = bd.getHeight();
	
	int* map = bd.getMap();
	
	cleardevice();
	
	// 绘制面板背景 
	setfillcolor(panel_color);
	bar(0,0,width*pwidth+(width+1)*lineWidth,height*pheight+(height+1)*lineWidth+topHeight);
	
	// 绘制"SCORE" 
	setfillcolor(canvas_color);
	bar((width/2)*pwidth+(width/2+1)*lineWidth,
		20,
		(width/2)*pwidth+(width/2+1)*lineWidth+pwidth,
		20+pheight*0.75);
			
	setbkmode(TRANSPARENT);	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[1]);
	
	LOGFONT* font = new LOGFONT();
					
	font->lfHeight = pheight/4 - 4;
	font->lfWidth = pwidth/4 - 14;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_SEMIBOLD;
					
	setfont(font);
	
	xyprintf((width/2)*pwidth+(width/2+1)*lineWidth+pwidth/2,
			 20+pheight*0.75/4,
			 TEXT("SCORE"));
	
	font->lfHeight = pheight/4 + 5;
	font->lfWidth = pwidth/4 - 7;
	font->lfWeight = FW_BLACK;
	
	setfont(font);
	
	xyprintf((width/2)*pwidth+(width/2+1)*lineWidth+pwidth/2,
			 20+pheight*0.75*3/5,
			 "%d",bd.getScores());
	
	delete font;
	
	// 绘制"BEST"
	setfillcolor(canvas_color);
	bar((width*3/4)*pwidth+(width*3/4+1)*lineWidth,
		20,
		(width*3/4)*pwidth+(width*3/4+1)*lineWidth+pwidth,
		20+pheight*0.75);
			
	setbkmode(TRANSPARENT);	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[1]);
	
	font = new LOGFONT();
					
	font->lfHeight = pheight/4 - 4;
	font->lfWidth = pwidth/4 - 14;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_SEMIBOLD;
					
	setfont(font);
	
	xyprintf((width*3/4)*pwidth+(width*3/4+1)*lineWidth+pwidth/2,
			 20+pheight*0.75/4,
			 TEXT("BEST"));
	
	font->lfHeight = pheight/4 + 5;
	font->lfWidth = pwidth/4 - 7;
	font->lfWeight = FW_BLACK;
	
	setfont(font);
	
	xyprintf((width*3/4)*pwidth+(width*3/4+1)*lineWidth+pwidth/2,
			 20+pheight*0.75*3/5,
			 "%d",historyScores);
	
	delete font;
	
	// 绘制"2048"的logo
	setbkmode(TRANSPARENT);	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[0]);
	
	font = new LOGFONT();
					
	font->lfHeight = pheight - 10;
	font->lfWidth = pwidth - 40;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_BLACK;
					
	setfont(font);
	
	xyprintf(pwidth+lineWidth,
			 20+pheight*0.75/2,
			 TEXT("2048"));
	
	delete font;
	
	// 输出一行"Don't you think this is such an amazing game?" 
	setbkmode(TRANSPARENT);	
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[0]);
	
	font = new LOGFONT();
					
	font->lfHeight = 15;
	font->lfWidth = 5;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_SEMIBOLD;
					
	setfont(font);
	
	xyprintf(lineWidth,
			 90,
			 TEXT("Don't you think this is such an amazing game?"));
	
	delete font;
	
	
	// 绘制画布背景 
	setfillcolor(canvas_color);
	bar(0,topHeight,width*pwidth+(width+1)*lineWidth,height*pheight+(height+1)*lineWidth+topHeight);
	
	// 绘制方格 
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(map[i*width+j]>0)
			{
				if(map[i*width+j]==2)
				{
					setfillcolor(numbkcolor[0]);
				}
				else if(map[i*width+j]==4)
				{
					setfillcolor(numbkcolor[1]);
				}
				else if(map[i*width+j]==8)
				{
					setfillcolor(numbkcolor[2]);
				}
				else if(map[i*width+j]==16)
				{
					setfillcolor(numbkcolor[3]);
				}
				else if(map[i*width+j]==32)
				{
					setfillcolor(numbkcolor[4]);
				}
				else if(map[i*width+j]==64) 
				{
					setfillcolor(numbkcolor[5]);
				}
				else if(map[i*width+j]==128)
				{
					setfillcolor(numbkcolor[6]);
				}
				else if(map[i*width+j]==256)
				{
					setfillcolor(numbkcolor[7]);
				}
				else if(map[i*width+j]==512 || map[i*width+j]==1024)
				{
					setfillcolor(numbkcolor[8]);
				}
				else
				{
					setfillcolor(numbkcolor[9]);
				}
	
				bar(j*pwidth+(j+1)*lineWidth,
					i*pheight+(i+1)*lineWidth+topHeight,
					(j+1)*(pwidth+lineWidth),
					(i+1)*(pheight+lineWidth)+topHeight);
					
				LOGFONT* font = new LOGFONT();
				
				if(map[i*width+j]>=10000)
				{
					font->lfHeight = 25;
					font->lfWidth = 10;
				}
				else if(map[i*width+j]>=1000)
				{
					font->lfHeight = 28;
					font->lfWidth = 12;
				}
				else if(map[i*width+j]>=100)
				{
					font->lfHeight = 32;
					font->lfWidth = 14;
				}
				else
				{
					font->lfHeight = 35;
					font->lfWidth = 16;
				}
				
				font->lfEscapement = 0;
				font->lfOrientation = 0;
				font->lfWeight = FW_BLACK;
					
				setfont(font);
		
				setbkmode(TRANSPARENT);
		
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				
				if(map[i*width+j]==2 || map[i*width+j]==4)
				{
					setcolor(numftcolor[0]);
				}
				else
				{
					setcolor(numftcolor[1]);
				}
		
				xyprintf(j*pwidth+(j+1)*lineWidth+pwidth/2,
						 i*pheight+(i+1)*lineWidth+pheight/2+topHeight,
						 "%d",map[i*width+j]);
					
				delete font;
			}
			else
			{
				setfillcolor(blank_color);
				
				bar(j*pwidth+(j+1)*lineWidth,
				i*pheight+(i+1)*lineWidth+topHeight,
				(j+1)*(pwidth+lineWidth),
				(i+1)*(pheight+lineWidth)+topHeight);
			}
		}
	}
}


// closeGame

void closeGame()
{
	closegraph();
}


// checkKeyboard

int checkKeyboard()
{
	int key;
	key_msg k;
	
	if(kbmsg())
	{
		k = getkey();
		
		switch(k.key)
		{
			case VK_LEFT:
				if(k.msg==key_msg_down)
				{
					key = LEFT;
				}
				else
				{
					key = INVALID;
				}
				
				break;
				
			case VK_RIGHT:
				if(k.msg==key_msg_down)
				{
					key = RIGHT;
				}
				else
				{
					key = INVALID;
				}
				
				break;
				
			case VK_UP:
				if(k.msg==key_msg_down)
				{
					key = UP;
				}
				else
				{
					key = INVALID;
				}
				
				break;
				
			case VK_DOWN:
				if(k.msg==key_msg_down)
				{
					key = DOWN;
				}
				else
				{
					key = INVALID;
				}
				
				break;
				
			case VK_RETURN:
				if(k.msg==key_msg_down)
				{
					key = ENTER;
				}
				else
				{
					key = INVALID;
				}
				
				break;
				
			default:
				key = INVALID;
		}
	}
	else
	{
		key = INVALID;
	}
	
	return key;
}


// addNumbers

bool addNumbers(Board& bd,int direction)
{
	bool changed(false);
	
	int* map = bd.getMap();
	
	int width = bd.getWidth();
	int height = bd.getHeight();
	
	bool* mergeCell = bd.getMergeCell();
	memset(mergeCell,0,sizeof(bool)*width*height);
	
	switch(direction)
	{
		case LEFT:
			
			for(int i=0;i<height;i++)
			{
				for(int j=0;j<width-1;j++)
				{		
					if(map[i*width+j]>0)
					{
						for(int k=j+1;k<width;k++)
						{
							if(map[i*width+k]>0 && map[i*width+j]==map[i*width+k])
							{
								map[i*width+j] += map[i*width+k];
								bd.setScores(bd.getScores()+map[i*width+j]);
								mergeCell[i*width+j] = true;
								map[i*width+k] = 0;
								j = k;
								changed = true;
							}
							else if(map[i*width+k]>0 && map[i*width+j]!=map[i*width+k])
							{
								break;
							}
						}
					}
				}
				
				int position(0);
				
				for(int j=0;j<width;j++)
				{
					if(map[i*width+j]>0)
					{
						map[i*width+position] = map[i*width+j];
						
						if(j!=position)
						{
							map[i*width+j] = 0;
							changed = true;
							swap(mergeCell[i*width+j],mergeCell[i*width+position]);
						}
						
						position++;
					}
				}
			}
			
			break;
			
		case RIGHT:
			
			for(int i=0;i<height;i++)
			{
				for(int j=width-1;j>0;j--)
				{					
					if(map[i*width+j]>0)
					{
						for(int k=j-1;k>=0;k--)
						{
							if(map[i*width+k]>0 && map[i*width+j]==map[i*width+k])
							{
								map[i*width+j] += map[i*width+k];
								bd.setScores(bd.getScores()+map[i*width+j]);
								mergeCell[i*width+j] = true;
								map[i*width+k] = 0;
								j = k;
								changed = true;
							}
							else if(map[i*width+k]>0 && map[i*width+j]!=map[i*width+k])
							{
								break;
							}
						}
					}
				}
				
				int position(width-1);
				
				for(int j=width-1;j>=0;j--)
				{
					if(map[i*width+j]>0)
					{
						map[i*width+position] = map[i*width+j];
						
						if(j!=position)
						{
							map[i*width+j] = 0;
							changed = true;
							swap(mergeCell[i*width+j],mergeCell[i*width+position]);
						}
						
						position--;
					}
				}
			}
			
			break;
			
		case UP:
			
			for(int j=0;j<width;j++)
			{
				for(int i=0;i<height-1;i++)
				{				
					if(map[i*width+j]>0)
					{
						for(int k=i+1;k<height;k++)
						{
							if(map[k*width+j]>0 && map[i*width+j]==map[k*width+j])
							{
								map[i*width+j] += map[k*width+j];
								bd.setScores(bd.getScores()+map[i*width+j]);
								mergeCell[i*width+j] = true;
								map[k*width+j] = 0;
								i = k;
								changed = true;
							}
							else if(map[k*width+j]>0 && map[i*width+j]!=map[k*width+j])
							{
								break;
							}
						}
					}
				}
				
				int position(0);
				
				for(int i=0;i<height;i++)
				{
					if(map[i*width+j]>0)
					{
						map[position*width+j] = map[i*width+j];
						
						if(i!=position)
						{
							map[i*width+j] = 0;
							changed = true;
							swap(mergeCell[i*width+j],mergeCell[position*width+j]);
						}
						
						position++;
					}
				}
			}
			
			break;
			
		case DOWN:
			
			for(int j=0;j<width;j++)
			{
				for(int i=height-1;i>0;i--)
				{					
					if(map[i*width+j]>0)
					{
						for(int k=i-1;k>=0;k--)
						{
							if(map[k*width+j]>0 && map[i*width+j]==map[k*width+j])
							{
								map[i*width+j] += map[k*width+j];
								bd.setScores(bd.getScores()+map[i*width+j]);
								mergeCell[i*width+j] = true;
								map[k*width+j] = 0;
								i = k;
								changed = true;
							}
							else if(map[k*width+j]>0 && map[i*width+j]!=map[k*width+j])
							{
								break;
							}
						}
					}
				}
				
				int position(height-1);
				
				for(int i=height-1;i>=0;i--)
				{
					if(map[i*width+j]>0)
					{
						map[position*width+j] = map[i*width+j];
						
						if(i!=position)
						{
							map[i*width+j] = 0;
							changed = true;
							swap(mergeCell[i*width+j],mergeCell[position*width+j]);
						}
						
						position--;
					}
				}
			}
			
			break;
			
	}
		
		
	return changed;	
	
}


// produceNumber

Cell produceNumber(Board& bd)
{
	int* map = bd.getMap();
	
	int width = bd.getWidth();
	int height = bd.getHeight();
	
	int num;
	
	Cell cl;
	
	randomize();
	
	if(random(7)==0) // 产生4的概率较小，产生2的概率较大 
	{
		num = 4;
	}
	else
	{
		num = 2;
	}
	
	while(true)
	{
		int tempX;
		int tempY;
		
		tempX = random(width);
		tempY = random(height);
		
		if(map[tempY*width+tempX]==0)
		{
			map[tempY*width+tempX] = num;
			cl.setX(tempX);
			cl.setY(tempY);
			cl.setNum(num);
			break;
		}
	}
	
	return cl;
}


// isFull

bool isFull(Board& bd)
{	
	int width = bd.getWidth() ;
	int height = bd.getHeight();
	int* map = bd.getMap();
	
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(map[i*width+j]==0)
			{
				return false;
			}
		}
	}
	
	return true;
}


// drawBulge

void drawBulge(Board& bd,int& historyScores)
{
	int lineWidth = bd.getLineWidth();
	int times = 4;
	
	for(int i=0;i<times+1;i++,delay_fps(60))
	{
		bulge(bd,lineWidth/2*i/times,historyScores);
	}
	
	for(int i=0;i<times+1;i++,delay_fps(60))
	{
		bulge(bd,lineWidth/2-lineWidth/2*i/times,historyScores);
	}
}


// bulge

void bulge(Board& bd,int increment,int& historyScores)
{
	int width = bd.getWidth();
	int height = bd.getHeight();
	
	bool* mergeCell = bd.getMergeCell();
	
	int pwidth = bd.getPwidth();
	int pheight = bd.getPheight();
	
	int lineWidth = bd.getLineWidth();
	
	int topHeight = bd.getTopHeight();
	
	int* map = bd.getMap();
	
	cleardevice();
	
	// 绘制面板背景 
	setfillcolor(panel_color);
	bar(0,0,width*pwidth+(width+1)*lineWidth,height*pheight+(height+1)*lineWidth+topHeight);
	
	// 绘制"SCORE" 
	setfillcolor(canvas_color);
	bar((width/2)*pwidth+(width/2+1)*lineWidth,
		20,
		(width/2)*pwidth+(width/2+1)*lineWidth+pwidth,
		20+pheight*0.75);
			
	setbkmode(TRANSPARENT);	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[1]);
	
	LOGFONT* font = new LOGFONT();
					
	font->lfHeight = pheight/4 - 4;
	font->lfWidth = pwidth/4 - 14;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_SEMIBOLD;
					
	setfont(font);
	
	xyprintf((width/2)*pwidth+(width/2+1)*lineWidth+pwidth/2,
			 20+pheight*0.75/4,
			 TEXT("SCORE"));
	
	font->lfHeight = pheight/4 + 5;
	font->lfWidth = pwidth/4 - 7;
	font->lfWeight = FW_BLACK;
	
	setfont(font);
	
	xyprintf((width/2)*pwidth+(width/2+1)*lineWidth+pwidth/2,
			 20+pheight*0.75*3/5,
			 "%d",bd.getScores());
	
	delete font;
	
	// 绘制"BEST"
	setfillcolor(canvas_color);
	bar((width*3/4)*pwidth+(width*3/4+1)*lineWidth,
		20,
		(width*3/4)*pwidth+(width*3/4+1)*lineWidth+pwidth,
		20+pheight*0.75);
			
	setbkmode(TRANSPARENT);	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[1]);
	
	font = new LOGFONT();
					
	font->lfHeight = pheight/4 - 4;
	font->lfWidth = pwidth/4 - 14;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_SEMIBOLD;
					
	setfont(font);
	
	xyprintf((width*3/4)*pwidth+(width*3/4+1)*lineWidth+pwidth/2,
			 20+pheight*0.75/4,
			 TEXT("BEST"));
	
	font->lfHeight = pheight/4 + 5;
	font->lfWidth = pwidth/4 - 7;
	font->lfWeight = FW_BLACK;
	
	setfont(font);
	
	xyprintf((width*3/4)*pwidth+(width*3/4+1)*lineWidth+pwidth/2,
			 20+pheight*0.75*3/5,
			 "%d",historyScores);
	
	delete font;
	
	// 绘制"2048"的logo
	setbkmode(TRANSPARENT);	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[0]);
	
	font = new LOGFONT();
					
	font->lfHeight = pheight - 10;
	font->lfWidth = pwidth - 40;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_BLACK;
					
	setfont(font);
	
	xyprintf(pwidth+lineWidth,
			 20+pheight*0.75/2,
			 TEXT("2048"));
	
	delete font;
	
	// 输出一行"Don't you think this is such an amazing game?" 
	setbkmode(TRANSPARENT);	
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[0]);
	
	font = new LOGFONT();
					
	font->lfHeight = 15;
	font->lfWidth = 5;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_SEMIBOLD;
					
	setfont(font);
	
	xyprintf(lineWidth,
			 90,
			 TEXT("Don't you think this is such an amazing game?"));
	
	delete font;
	
	
	// 绘制画布背景 
	setfillcolor(canvas_color);
	bar(0,topHeight,width*pwidth+(width+1)*lineWidth,height*pheight+(height+1)*lineWidth+topHeight);
	
	// 绘制方格 
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(map[i*width+j]>0)
			{
				if(map[i*width+j]==2)
				{
					setfillcolor(numbkcolor[0]);
				}
				else if(map[i*width+j]==4)
				{
					setfillcolor(numbkcolor[1]);
				}
				else if(map[i*width+j]==8)
				{
					setfillcolor(numbkcolor[2]);
				}
				else if(map[i*width+j]==16)
				{
					setfillcolor(numbkcolor[3]);
				}
				else if(map[i*width+j]==32)
				{
					setfillcolor(numbkcolor[4]);
				}
				else if(map[i*width+j]==64) 
				{
					setfillcolor(numbkcolor[5]);
				}
				else if(map[i*width+j]==128)
				{
					setfillcolor(numbkcolor[6]);
				}
				else if(map[i*width+j]==256)
				{
					setfillcolor(numbkcolor[7]);
				}
				else if(map[i*width+j]==512 || map[i*width+j]==1024)
				{
					setfillcolor(numbkcolor[8]);
				}
				else
				{
					setfillcolor(numbkcolor[9]);
				}
				
				if(mergeCell[i*width+j]==true)
				{
					bar(j*pwidth+(j+1)*lineWidth-increment,
						i*pheight+(i+1)*lineWidth+topHeight-increment,
						(j+1)*(pwidth+lineWidth)+increment,
						(i+1)*(pheight+lineWidth)+topHeight+increment);
				}
				else
				{
					bar(j*pwidth+(j+1)*lineWidth,
						i*pheight+(i+1)*lineWidth+topHeight,
						(j+1)*(pwidth+lineWidth),
						(i+1)*(pheight+lineWidth)+topHeight);
				}
				
					
				LOGFONT* font = new LOGFONT();
					
				if(map[i*width+j]>=10000)
				{
					font->lfHeight = 25;
					font->lfWidth = 10;
				}
				else if(map[i*width+j]>=1000)
				{
					font->lfHeight = 28;
					font->lfWidth = 12;
				}
				else if(map[i*width+j]>=100)
				{
					font->lfHeight = 32;
					font->lfWidth = 14;
				}
				else
				{
					font->lfHeight = 35;
					font->lfWidth = 16;
				}
				
				
				font->lfEscapement = 0;
				font->lfOrientation = 0;
				font->lfWeight = FW_BLACK;
					
				setfont(font);
		
				setbkmode(TRANSPARENT);
		
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				
				if(map[i*width+j]==2 || map[i*width+j]==4)
				{
					setcolor(numftcolor[0]);
				}
				else
				{
					setcolor(numftcolor[1]);
				}
		
				xyprintf(j*pwidth+(j+1)*lineWidth+pwidth/2,
						 i*pheight+(i+1)*lineWidth+pheight/2+topHeight,
						 "%d",map[i*width+j]);
					
				delete font;
			}
			else
			{
				setfillcolor(blank_color);
				
				bar(j*pwidth+(j+1)*lineWidth,
				i*pheight+(i+1)*lineWidth+topHeight,
				(j+1)*(pwidth+lineWidth),
				(i+1)*(pheight+lineWidth)+topHeight);
			}
		}
	}
	
}


// swap

void swap(bool& a,bool& b)
{
	bool temp;
	
	temp = a;
	a = b;
	b = temp;
}


// drawProduce

void drawProduce(Board& bd,Cell& cl,int& historyScores)
{
	int pwidth = bd.getPwidth();
	int times = 4;
	
	for(int i=0;i<times+1;i++,delay_fps(60))
	{
		produce(bd,cl,-(pwidth/4-pwidth/4/times*i),historyScores);
	}

}


// produce
void produce(Board& bd,Cell& cl,int increment,int& historyScores)
{
	int width = bd.getWidth();
	int height = bd.getHeight();
	
	int pwidth = bd.getPwidth();
	int pheight = bd.getPheight();
	
	int lineWidth = bd.getLineWidth();
	
	int topHeight = bd.getTopHeight();
	
	int* map = bd.getMap();
	
	cleardevice();
	
	// 绘制面板背景 
	setfillcolor(panel_color);
	bar(0,0,width*pwidth+(width+1)*lineWidth,height*pheight+(height+1)*lineWidth+topHeight);
	
	// 绘制"SCORE" 
	setfillcolor(canvas_color);
	bar((width/2)*pwidth+(width/2+1)*lineWidth,
		20,
		(width/2)*pwidth+(width/2+1)*lineWidth+pwidth,
		20+pheight*0.75);
			
	setbkmode(TRANSPARENT);	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[1]);
	
	LOGFONT* font = new LOGFONT();
					
	font->lfHeight = pheight/4 - 4;
	font->lfWidth = pwidth/4 - 14;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_SEMIBOLD;
					
	setfont(font);
	
	xyprintf((width/2)*pwidth+(width/2+1)*lineWidth+pwidth/2,
			 20+pheight*0.75/4,
			 TEXT("SCORE"));
	
	font->lfHeight = pheight/4 + 5;
	font->lfWidth = pwidth/4 - 7;
	font->lfWeight = FW_BLACK;
	
	setfont(font);
	
	xyprintf((width/2)*pwidth+(width/2+1)*lineWidth+pwidth/2,
			 20+pheight*0.75*3/5,
			 "%d",bd.getScores());
	
	delete font;
	
	// 绘制"BEST"
	setfillcolor(canvas_color);
	bar((width*3/4)*pwidth+(width*3/4+1)*lineWidth,
		20,
		(width*3/4)*pwidth+(width*3/4+1)*lineWidth+pwidth,
		20+pheight*0.75);
			
	setbkmode(TRANSPARENT);	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[1]);
	
	font = new LOGFONT();
					
	font->lfHeight = pheight/4 - 4;
	font->lfWidth = pwidth/4 - 14;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_SEMIBOLD;
					
	setfont(font);
	
	xyprintf((width*3/4)*pwidth+(width*3/4+1)*lineWidth+pwidth/2,
			 20+pheight*0.75/4,
			 TEXT("BEST"));
	
	font->lfHeight = pheight/4 + 5;
	font->lfWidth = pwidth/4 - 7;
	font->lfWeight = FW_BLACK;
	
	setfont(font);
	
	xyprintf((width*3/4)*pwidth+(width*3/4+1)*lineWidth+pwidth/2,
			 20+pheight*0.75*3/5,
			 "%d",historyScores);
	
	delete font;
	
	// 绘制"2048"的logo
	setbkmode(TRANSPARENT);	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[0]);
	
	font = new LOGFONT();
					
	font->lfHeight = pheight - 10;
	font->lfWidth = pwidth - 40;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_BLACK;
					
	setfont(font);
	
	xyprintf(pwidth+lineWidth,
			 20+pheight*0.75/2,
			 TEXT("2048"));
	
	delete font;
	
	// 输出一行"Don't you think this is such an amazing game?" 
	setbkmode(TRANSPARENT);	
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[0]);
	
	font = new LOGFONT();
					
	font->lfHeight = 15;
	font->lfWidth = 5;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_SEMIBOLD;
					
	setfont(font);
	
	xyprintf(lineWidth,
			 90,
			 TEXT("Don't you think this is such an amazing game?"));
	
	delete font;
	
	
	// 绘制画布背景 
	setfillcolor(canvas_color);
	bar(0,topHeight,width*pwidth+(width+1)*lineWidth,height*pheight+(height+1)*lineWidth+topHeight);
	
	// 绘制方格 
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(map[i*width+j]>0)
			{
				if(map[i*width+j]==2)
				{
					setfillcolor(numbkcolor[0]);
				}
				else if(map[i*width+j]==4)
				{
					setfillcolor(numbkcolor[1]);
				}
				else if(map[i*width+j]==8)
				{
					setfillcolor(numbkcolor[2]);
				}
				else if(map[i*width+j]==16)
				{
					setfillcolor(numbkcolor[3]);
				}
				else if(map[i*width+j]==32)
				{
					setfillcolor(numbkcolor[4]);
				}
				else if(map[i*width+j]==64) 
				{
					setfillcolor(numbkcolor[5]);
				}
				else if(map[i*width+j]==128)
				{
					setfillcolor(numbkcolor[6]);
				}
				else if(map[i*width+j]==256)
				{
					setfillcolor(numbkcolor[7]);
				}
				else if(map[i*width+j]==512 || map[i*width+j]==1024)
				{
					setfillcolor(numbkcolor[8]);
				}
				else
				{
					setfillcolor(numbkcolor[9]);
				}
				
				if(cl.getX()==j && cl.getY()==i)
				{
					bar(j*pwidth+(j+1)*lineWidth-increment,
						i*pheight+(i+1)*lineWidth+topHeight-increment,
						(j+1)*(pwidth+lineWidth)+increment,
						(i+1)*(pheight+lineWidth)+topHeight+increment);
				}
				else
				{
					bar(j*pwidth+(j+1)*lineWidth,
						i*pheight+(i+1)*lineWidth+topHeight,
						(j+1)*(pwidth+lineWidth),
						(i+1)*(pheight+lineWidth)+topHeight);
				}
				
					
				LOGFONT* font = new LOGFONT();
					
				if(map[i*width+j]>=10000)
				{
					font->lfHeight = 25;
					font->lfWidth = 10;
				}
				else if(map[i*width+j]>=1000)
				{
					font->lfHeight = 28;
					font->lfWidth = 12;
				}
				else if(map[i*width+j]>=100)
				{
					font->lfHeight = 32;
					font->lfWidth = 14;
				}
				else
				{
					font->lfHeight = 35;
					font->lfWidth = 16;
				}
				
				
				font->lfEscapement = 0;
				font->lfOrientation = 0;
				font->lfWeight = FW_BLACK;
					
				setfont(font);
		
				setbkmode(TRANSPARENT);
		
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				
				if(map[i*width+j]==2 || map[i*width+j]==4)
				{
					setcolor(numftcolor[0]);
				}
				else
				{
					setcolor(numftcolor[1]);
				}
		
				xyprintf(j*pwidth+(j+1)*lineWidth+pwidth/2,
						 i*pheight+(i+1)*lineWidth+pheight/2+topHeight,
						 "%d",map[i*width+j]);
					
				delete font;
			}
			else
			{
				setfillcolor(blank_color);
				
				bar(j*pwidth+(j+1)*lineWidth,
				i*pheight+(i+1)*lineWidth+topHeight,
				(j+1)*(pwidth+lineWidth),
				(i+1)*(pheight+lineWidth)+topHeight);
			}
		}
	}
	
}


// isOver

bool isOver(Board& bd)
{
	bool changed = false;
	
	Board temp_bd(bd);
	 
	for(int i=0;i<4;i++) // 遍历上下左右4个方向，看是否能够引起变化
	{
		changed = addNumbers(temp_bd,i);
		if(changed)
		{
			break;
		}
	} 
	
	return !changed;
}


void showOver(Board& bd,int& historyScores,int card)
{
	int pwidth = bd.getPwidth();
	int pheight = bd.getPheight();
	
	int lineWidth = bd.getLineWidth();
	
	int topHeight = bd.getTopHeight();
	
	int width = bd.getWidth();
	int height = bd.getHeight();
	
	int* map = bd.getMap();
	
	int increment_1 = 0;
	int increment_2 = 0;
	
	if(card==try_again)
	{
		increment_1 = lineWidth;
	}
	else if(card==exit_game)
	{
		increment_2 = lineWidth;
	}
	
	cleardevice();
	
	// 绘制面板背景 
	setfillcolor(panel_color);
	bar(0,0,width*pwidth+(width+1)*lineWidth,height*pheight+(height+1)*lineWidth+topHeight);
	
	// 绘制"SCORE" 
	setfillcolor(canvas_color);
	bar((width/2)*pwidth+(width/2+1)*lineWidth,
		20,
		(width/2)*pwidth+(width/2+1)*lineWidth+pwidth,
		20+pheight*0.75);
			
	setbkmode(TRANSPARENT);	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[1]);
	
	LOGFONT* font = new LOGFONT();
					
	font->lfHeight = pheight/4 - 4;
	font->lfWidth = pwidth/4 - 14;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_SEMIBOLD;
					
	setfont(font);
	
	xyprintf((width/2)*pwidth+(width/2+1)*lineWidth+pwidth/2,
			 20+pheight*0.75/4,
			 TEXT("SCORE"));
	
	font->lfHeight = pheight/4 + 5;
	font->lfWidth = pwidth/4 - 7;
	font->lfWeight = FW_BLACK;
	
	setfont(font);
	
	xyprintf((width/2)*pwidth+(width/2+1)*lineWidth+pwidth/2,
			 20+pheight*0.75*3/5,
			 "%d",bd.getScores());
	
	delete font;
	
	// 绘制"BEST"
	setfillcolor(canvas_color);
	bar((width*3/4)*pwidth+(width*3/4+1)*lineWidth,
		20,
		(width*3/4)*pwidth+(width*3/4+1)*lineWidth+pwidth,
		20+pheight*0.75);
			
	setbkmode(TRANSPARENT);	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[1]);
	
	font = new LOGFONT();
					
	font->lfHeight = pheight/4 - 4;
	font->lfWidth = pwidth/4 - 14;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_SEMIBOLD;
					
	setfont(font);
	
	xyprintf((width*3/4)*pwidth+(width*3/4+1)*lineWidth+pwidth/2,
			 20+pheight*0.75/4,
			 TEXT("BEST"));
	
	font->lfHeight = pheight/4 + 5;
	font->lfWidth = pwidth/4 - 7;
	font->lfWeight = FW_BLACK;
	
	setfont(font);
	
	xyprintf((width*3/4)*pwidth+(width*3/4+1)*lineWidth+pwidth/2,
			 20+pheight*0.75*3/5,
			 "%d",historyScores);
	
	delete font;
	
	// 绘制"2048"的logo
	setbkmode(TRANSPARENT);	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[0]);
	
	font = new LOGFONT();
					
	font->lfHeight = pheight - 10;
	font->lfWidth = pwidth - 40;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_BLACK;
					
	setfont(font);
	
	xyprintf(pwidth+lineWidth,
			 20+pheight*0.75/2,
			 TEXT("2048"));
	
	delete font;
	
	// 输出一行"Don't you think this is such an amazing game?" 
	setbkmode(TRANSPARENT);	
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[0]);
	
	font = new LOGFONT();
					
	font->lfHeight = 15;
	font->lfWidth = 5;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_SEMIBOLD;
					
	setfont(font);
	
	xyprintf(lineWidth,
			 90,
			 TEXT("Don't you think this is such an amazing game?"));
	
	delete font;
	
	
	// 绘制画布背景 
	setfillcolor(canvas_color);
	bar(0,topHeight,width*pwidth+(width+1)*lineWidth,height*pheight+(height+1)*lineWidth+topHeight);
	
	// 绘制方格 
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(map[i*width+j]>0)
			{
				if(map[i*width+j]==2)
				{
					setfillcolor(numbkcolor[0]);
				}
				else if(map[i*width+j]==4)
				{
					setfillcolor(numbkcolor[1]);
				}
				else if(map[i*width+j]==8)
				{
					setfillcolor(numbkcolor[2]);
				}
				else if(map[i*width+j]==16)
				{
					setfillcolor(numbkcolor[3]);
				}
				else if(map[i*width+j]==32)
				{
					setfillcolor(numbkcolor[4]);
				}
				else if(map[i*width+j]==64) 
				{
					setfillcolor(numbkcolor[5]);
				}
				else if(map[i*width+j]==128)
				{
					setfillcolor(numbkcolor[6]);
				}
				else if(map[i*width+j]==256)
				{
					setfillcolor(numbkcolor[7]);
				}
				else if(map[i*width+j]==512 || map[i*width+j]==1024)
				{
					setfillcolor(numbkcolor[8]);
				}
				else
				{
					setfillcolor(numbkcolor[9]);
				}
	
				bar(j*pwidth+(j+1)*lineWidth,
					i*pheight+(i+1)*lineWidth+topHeight,
					(j+1)*(pwidth+lineWidth),
					(i+1)*(pheight+lineWidth)+topHeight);
					
				LOGFONT* font = new LOGFONT();
					
				if(map[i*width+j]>=10000)
				{
					font->lfHeight = 25;
					font->lfWidth = 10;
				}
				else if(map[i*width+j]>=1000)
				{
					font->lfHeight = 28;
					font->lfWidth = 12;
				}
				else if(map[i*width+j]>=100)
				{
					font->lfHeight = 32;
					font->lfWidth = 14;
				}
				else
				{
					font->lfHeight = 35;
					font->lfWidth = 16;
				}
				
				
				font->lfEscapement = 0;
				font->lfOrientation = 0;
				font->lfWeight = FW_BLACK;
					
				setfont(font);
		
				setbkmode(TRANSPARENT);
		
				settextjustify(CENTER_TEXT,CENTER_TEXT);
				
				if(map[i*width+j]==2 || map[i*width+j]==4)
				{
					setcolor(numftcolor[0]);
				}
				else
				{
					setcolor(numftcolor[1]);
				}
		
				xyprintf(j*pwidth+(j+1)*lineWidth+pwidth/2,
						 i*pheight+(i+1)*lineWidth+pheight/2+topHeight,
						 "%d",map[i*width+j]);
					
				delete font;
			}
			else
			{
				setfillcolor(blank_color);
				
				bar(j*pwidth+(j+1)*lineWidth,
				i*pheight+(i+1)*lineWidth+topHeight,
				(j+1)*(pwidth+lineWidth),
				(i+1)*(pheight+lineWidth)+topHeight);
			}
		}
	}
	
	// 绘制选项卡
	setfillcolor(numbkcolor[1]);
	
	bar(pwidth+2*lineWidth-increment_1,
		lineWidth+topHeight+pheight/2-increment_1,
		3*(pwidth+lineWidth)+increment_1,
		2*lineWidth+topHeight+pheight*3/2+increment_1);
		
	bar(pwidth+2*lineWidth-increment_2,
		lineWidth+topHeight+pheight/2+2*(pwidth+lineWidth)-increment_2,
		3*(pwidth+lineWidth)+increment_2,
		2*lineWidth+topHeight+pheight*3/2+2*(pwidth+lineWidth)+increment_2);
		
	setbkmode(TRANSPARENT);	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	
	setcolor(numftcolor[0]);
	
	font = new LOGFONT();
					
	font->lfHeight = 25;
	font->lfWidth = 10;
	font->lfEscapement = 0;
	font->lfOrientation = 0;
	font->lfWeight = FW_BLACK;
					
	setfont(font);
	
	xyprintf((pwidth+2*lineWidth+3*(pwidth+lineWidth))/2,
			 (lineWidth+topHeight+pheight/2+2*lineWidth+topHeight+pheight*3/2)/2,
			 TEXT("Try Again"));
	
	xyprintf((pwidth+2*lineWidth+3*(pwidth+lineWidth))/2,
			 (lineWidth+topHeight+pheight/2+2*(pwidth+lineWidth)+2*lineWidth+topHeight+pheight*3/2+2*(pwidth+lineWidth))/2,
			 TEXT("Exit Game"));
			 
	delete font;
}
