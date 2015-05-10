#pragma once

#include "Cell.h"

class Board
{
	private:
		int pwidth; //每个方格的宽（像素个数） 
		int pheight; //每个方格的高（像素个数） 
		
		int lineWidth; //方格边缘线宽（即相邻方格间的间距）（像素个数） 
		
		int topHeight; //顶部面板高度（像素个数） 
		
		int width; //每行的方格数 
		int height; //每列的方格数 
		
		int scores;  //分数 
		
		int* map; //整个棋盘 
		
		bool* mergeCell; // 用于记录刚刚合并后得到的方格 
		
		
	public:
		
		Board();
		
		Board(const Board& bd);
		
		void operator=(const Board& bd);
		
		~Board();
		
		int getPwidth()const;
//		void setPwidth(int pwidth);
		
		int getPheight()const;
//		void setPheight(int pheight);

		int getLineWidth()const; 
		
		int getTopHeight()const; 
		
		int getWidth()const;
//		void setWidth(int width);
		
		int getHeight()const;
//		void setHeight(int height);
		
		int getScores()const;
		void setScores(int scores);
		
		int* getMap()const;
		
		bool* getMergeCell()const; 
};
