#include "Board.h"
#include <graphics.h>
#include <string.h>


Board::Board()
{	
	pwidth = 70;
	pheight = 70;
	
	lineWidth = 10;
	
	topHeight = 110;
	
	width = 4;
	height = 4;
	
	scores = 0;
	
	map = new int[width*height](); //初始化为0 
	
	mergeCell = new bool[width*height];
	memset(mergeCell,0,sizeof(bool)*width*height); // 初始化为false 
	
	randomize();
	
	map[random(height)*width+random(width)] = 2;
	
	int tempX;
	int tempY;
	
	while(true)
	{
		tempX = random(width);
		tempY = random(height);
		
		if(map[tempY*width+tempX]==0)
		{
			map[tempY*width+tempX] = 2;
			break;
		}
	}
	
}

Board::Board(const Board& bd)
{
	pwidth = bd.getPwidth(); 
	pheight = bd.getPheight(); 
		
	lineWidth = bd.getLineWidth(); 
		
	topHeight = bd.getTopHeight(); 
		
	width = bd.getWidth(); 
	height = bd.getHeight(); 
		
	scores = bd.getScores(); 
		
	map = new int[width*height];
	memcpy(map,bd.getMap(),sizeof(int)*width*height);
		
	mergeCell = new bool[width*height];
	memcpy(mergeCell,bd.getMap(),sizeof(bool)*width*height);
} 


void Board::operator=(const Board& bd)
{
	pwidth = bd.getPwidth(); 
	pheight = bd.getPheight(); 
		
	lineWidth = bd.getLineWidth(); 
		
	topHeight = bd.getTopHeight(); 
		
	width = bd.getWidth(); 
	height = bd.getHeight(); 
		
	scores = bd.getScores(); 
	
	delete[] map;
	map = new int[width*height];
	memcpy(map,bd.getMap(),sizeof(int)*width*height);
	
	delete[] mergeCell;
	mergeCell = new bool[width*height];
	memcpy(mergeCell,bd.getMap(),sizeof(bool)*width*height);
}

Board::~Board()
{
	delete[] map;
	delete[] mergeCell;
} 

int Board::getPwidth()const
{
	return pwidth;
}

int Board::getPheight()const
{
	return pheight;
}

int Board::getLineWidth()const
{
	return lineWidth;
}

int Board::getTopHeight()const
{
	return topHeight;
}

int Board::getWidth()const
{
	return width;
}

int Board::getHeight()const
{
	return height;
}

int Board::getScores()const
{
	return scores;
}

void Board::setScores(int scores)
{
	this->scores = scores;
}

int* Board::getMap()const
{
	return map;
}

bool* Board::getMergeCell()const
{
	return mergeCell;
}

