#pragma once

class Cell
{
	private:
		int x;  
		int y;
		int num; 
		
	public:
		Cell();
		
		Cell(int x,int y,int num=2);
		
		Cell(const Cell& cl);
		
		void operator=(const Cell& cl);
		
		int getX()const;
		void setX(int x);
		
		int getY()const;
		void setY(int Y);
		
		int getNum()const;
		void setNum(int num);
};
