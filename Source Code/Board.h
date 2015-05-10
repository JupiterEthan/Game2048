#pragma once

#include "Cell.h"

class Board
{
	private:
		int pwidth; //ÿ������Ŀ����ظ����� 
		int pheight; //ÿ������ĸߣ����ظ����� 
		
		int lineWidth; //�����Ե�߿������ڷ����ļ�ࣩ�����ظ����� 
		
		int topHeight; //�������߶ȣ����ظ����� 
		
		int width; //ÿ�еķ����� 
		int height; //ÿ�еķ����� 
		
		int scores;  //���� 
		
		int* map; //�������� 
		
		bool* mergeCell; // ���ڼ�¼�ոպϲ���õ��ķ��� 
		
		
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
