#include"Game.h"
#include<iostream>

using namespace std;
void main(){
	_Common::fixConsoleWindow();
	_Game g(BOARD_SIZE, LEFT, TOP); // Sinh viên tự định nghĩa các hằng số 
	g.GiaoDien();
}
