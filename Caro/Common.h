#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<Windows.h>
#include<conio.h>

#define O_TRONG 249
#define BOARD_SIZE 25
#define LEFT 1
#define TOP 1

class _Common{
public:
	static void fixConsoleWindow();
	static void gotoXY(int, int);
	static void setColor(int);


	static void ReSet();

	static void Khung(int x, int y, int a, int b);

	static void TrangChu();

	static int Menu(char S[][20], int first, int last);
};

