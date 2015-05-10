#include "Cell.h"

Cell::Cell()
{
	x = 0;
	y = 0;
	
	num = 2;	
}

Cell::Cell(int x,int y,int num)
{
	this->x = x;
	this->y = y;
	
	this->num = num;
}

Cell::Cell(const Cell& cl)
{
	x = cl.getX();
	y = cl.getY();
	num = cl.getNum();
}

void Cell::operator=(const Cell& cl)
{
	x = cl.getX();
	y = cl.getY();
	num = cl.getNum();
}

int Cell::getX()const
{
	return x;
}

void Cell::setX(int x)
{
	this->x = x;
}

int Cell::getY()const
{
	return y;
}

void Cell::setY(int y)
{
	this->y = y;
}

int Cell::getNum()const
{
	return num;
}

void Cell::setNum(int num)
{
	this->num = num;
}


