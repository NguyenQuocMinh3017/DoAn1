#include"Game.h"

_Game::_Game(int pSize, int pLeft, int pTop){
	_b = new _Board(pSize, pLeft, pTop);
	_loop = true;
	_turn = 'X';
	_command = -1; // Gán lượt và phím mặc định 
	_x = pLeft; _y = pTop;
}
_Game::~_Game(){ delete _b; }

int _Game::getCommand(){ return _command; }
bool _Game::isContinue(){ return _loop; }
unsigned char _Game::waitKeyBoard(){
	_command = toupper(getch());
	return _command;
}

unsigned char _Game::askContinue(){
	_Common::gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 4);
	return waitKeyBoard();
}

void _Game::loadData(char *tenFile)
{
	int checkFile=0,sz=sizeof(int);
	_fcloseall();
	FILE *f = fopen(tenFile, "rb");
		fread(&checkFile, sz, 1, f);
		if (checkFile)
		{
			fread(&_turn, sizeof(char), 1, f);
			_b->loadData(f, 1);
		}
		else
		{
			_turn = 'X';
			_b->loadData(f, 0);
		}
	_fcloseall();
}
void _Game::saveData(char *tenFile,bool checkCont)
{
	int sz = sizeof(int);
	FILE *f = fopen(tenFile, "wb");
	fwrite(&checkCont, sz, 1, f);
	if (checkCont)
	{
		fwrite(&_turn, sizeof(char), 1, f);
		_b->saveData(f);
	}
	_fcloseall();
}
void _Game::startGame() {
	_Common::setColor(07);
	system("cls");
	loadData("Data.inp"); // Khởi tạo dữ liệu gốc 
	_b->drawBoard(); // Vẽ màn hình game 
	_x = _b->getLeft();
	_y = _b->getTop();
	_b->draw(_x, _y, 240);
}
void _Game::exitGame() {
	system("cls");
	_loop = false;
}

bool _Game::processCheckBoard() {
	unsigned char key = _b->checkBoard(_x, _y, _turn);
	switch (key){
	case 0: return false; // Khi đánh vào ô đã đánh rồi 
	default:
		_b->draw(_x, _y, 240);
		break;
	}
	return true;
}

int _Game::processFinish() {

	int pWhoWin = _b->testBoard(_x, _y, _turn);
	_Common::setColor(14);
	// Nhảy tới vị trí thích hợp để in chuỗi thắng/thua/hòa   
	_Common::gotoXY(_b->getSize()+2,0);
	switch (pWhoWin){
	case '0':
		printf("HOA CO");
		break;
	case ' ':
		_turn = 'X' + 'O' - _turn; // Đổi lượt nếu không có gì xảy ra 
		break;
	default:
		printf("NGUOI CHOI %c THANG", _turn);
		break;
	}
	_Common::gotoXY(_x + 1, _y + 1);// Trả về vị trí hiện hành của con trỏ màn hình bàn cờ 
	return pWhoWin;
}

void _Game::moveRight() {
	if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1)){
		printPoint();

		_x++;
		_b->draw(_x, _y, 240);
	}
}
void _Game::moveLeft() {
	if (_x > _b->getXAt(0, 0)) {
		printPoint();

		_x--;
		_b->draw(_x, _y, 240);
	}
}
void _Game::moveDown() {
	if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1)){
		printPoint();

		_y++;
		_b->draw(_x, _y, 240);
	}
}
void _Game::moveUp() {
	if (_y > _b->getYAt(0, 0)) {
		printPoint();

		_y--;
		_b->draw(_x, _y, 240);
	}
}

void _Game::printPoint()
{
	_Common::gotoXY(_x + 1, _y + 1);
	switch (_b->getCheckAt(_x, _y))
	{
	case 'X':
		_Common::setColor(12);
		break;
	case 'O':
		_Common::setColor(10);
		break;
	default:
		_Common::setColor(7);
	}
	printf("%c", _b->getCheckAt(_x, _y));
}

void _Game::GiaoDien()
{
	_Common::ReSet();
	char Home[][20] = {
		"NEW GAME",
		"CONTINUE",
		"HUONG DAN",
		"KET THUC"
	};

	int chon;
	do
	{
		chon = _Common::Menu(Home, 0, 3);
		switch (chon)
		{
		case 0:
			saveData("Data.inp", 0);
			_loop = true;
			playGame();
			break;
		case 1:
			_loop = true;
			playGame();
			break;
		}
	} while (chon != 3);
}

void _Game::playGame()
{
	startGame();
	while (isContinue()){
		waitKeyBoard();
		if (getCommand() == 27){
			saveData("Data.inp", 1);
			exitGame();
		}
		else {
			switch (getCommand()){
			case 'A':case 75:
				moveLeft();
				break;
			case 'W':case 72:
				moveUp();
				break;
			case 'S':case 80:
				moveDown();
				break;
			case 'D':case 77:
				moveRight();
				break;
			case ' ':
				//Đánh dấu bàn cờ, sau đó kiểm tra và xử lý thắng/thua/hòa/tiếp tục 
				if (processCheckBoard()){
					switch (processFinish()){
					case 'X': case 'O': case '0':
						saveData("Data.inp", 0);
						exitGame();
					}
				}
			}
		}
	}
}