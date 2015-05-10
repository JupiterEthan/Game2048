#pragma once

#include "Board.h"
#include "Cell.h"

// main function

void initGame(Board& bd);

void updateGame(Board& bd,int& historyScores);

void closeGame();

// functional

int checkKeyboard(); // 检测并接收键盘按键消息 

bool addNumbers(Board& bd,int direction);  // 实现数的合并和移动 

Cell produceNumber(Board& bd); // 产生新数 

bool isFull(Board& bd); // 判断棋盘是否已满 

void drawBulge(Board& bd,int& historyScores);  // 合并后瞬间的方格"膨胀"特效 (主函数)

void bulge(Board& bd,int increment,int& historyScores); // 合并后瞬间的方格"膨胀"特效 (功能函数)

void swap(bool& a,bool& b); //交换两个布尔变量的值

void drawProduce(Board& bd,Cell& cl,int& historyScores); // 产生新数瞬间的"展开"特效 (主函数)

void produce(Board& bd,Cell& cl,int increment,int& historyScores); // 产生新数瞬间的"展开"特效 (功能函数)

bool isOver(Board& bd); // 判断是否已经Game Over 

void showOver(Board& bd,int& historyScores,int card); // Game Over画面，选择是否retry 
