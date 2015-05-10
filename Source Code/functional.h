#pragma once

#include "Board.h"
#include "Cell.h"

// main function

void initGame(Board& bd);

void updateGame(Board& bd,int& historyScores);

void closeGame();

// functional

int checkKeyboard(); // ��Ⲣ���ռ��̰�����Ϣ 

bool addNumbers(Board& bd,int direction);  // ʵ�����ĺϲ����ƶ� 

Cell produceNumber(Board& bd); // �������� 

bool isFull(Board& bd); // �ж������Ƿ����� 

void drawBulge(Board& bd,int& historyScores);  // �ϲ���˲��ķ���"����"��Ч (������)

void bulge(Board& bd,int increment,int& historyScores); // �ϲ���˲��ķ���"����"��Ч (���ܺ���)

void swap(bool& a,bool& b); //������������������ֵ

void drawProduce(Board& bd,Cell& cl,int& historyScores); // ��������˲���"չ��"��Ч (������)

void produce(Board& bd,Cell& cl,int increment,int& historyScores); // ��������˲���"չ��"��Ч (���ܺ���)

bool isOver(Board& bd); // �ж��Ƿ��Ѿ�Game Over 

void showOver(Board& bd,int& historyScores,int card); // Game Over���棬ѡ���Ƿ�retry 
