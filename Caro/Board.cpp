#include"Board.h"



int _Board::getSize(){ return _size; }
int _Board::getLeft(){ return _left; }
int _Board::getTop(){ return _top; }
int _Board::getXAt(int i, int j){
	return _pArr[i][j].getX();
}
int _Board::getYAt(int i, int j){
	return _pArr[i][j].getY();
}

int _Board::getCheckAt(int i, int j)
{
	return _pArr[i][j].getCheck();
}

_Board::_Board(int pSize, int pX, int pY){
	_size = pSize;
	_left = pX;
	_top = pY;
	_pArr = new _Point*[pSize];
	for (int i = 0; i < pSize; i++) _pArr[i] = new _Point[pSize];
}
_Board::~_Board(){
	for (int i = 0; i < _size; i++) delete[] _pArr[i];
	delete[] _pArr;
}

void _Board::loadData(FILE*f,bool checkFile) 
{
	if (_size == 0) return; // Phải gọi constructor trước khi loadData 
	if (checkFile)
	{
		fread(&_size, sizeof(int), 1, f);
		fread(&_left, sizeof(int), 1, f);
		fread(&_top, sizeof(int), 1, f);
		fread(&_used, sizeof(int), 1, f);
		for (int i = 0; i < _size; i++)
			for (int j = 0; j < _size; j++)
				fread(&_pArr[i][j], sizeof(_Point), 1, f);
	}
	else
	{
		for (int i = 0; i < _size; i++){
			for (int j = 0; j < _size; j++){
				_pArr[i][j].setX(i); // Trùng với hoành độ màn hình bàn cờ 
				_pArr[i][j].setY(j); // Trùng với tung độ màn hình bàn cờ 
				_pArr[i][j].setCheck(O_TRONG);
			}
		}
	}
}
void _Board::saveData(FILE *f)
{
	fwrite(&_size, sizeof(int), 1, f);
	fwrite(&_left, sizeof(int), 1, f);
	fwrite(&_top, sizeof(int), 1, f);
	fwrite(&_used, sizeof(int), 1, f);
	for (int i = 0; i < _size; i++)
	for (int j = 0; j < _size; j++)
		fwrite(&_pArr[i][j], sizeof(_Point), 1, f);
}
void _Board::drawBoard(){
	if (_pArr == NULL) return; // phải gọi constructor trước 
	for (int i = 0; i <= _size; i++)
	{
		_Common::setColor(77);
		printf(" ");
	}

	_Common::gotoXY(0, _size + 1);
	for (int i = 0; i <= _size; i++)
	{
		_Common::setColor(77);
		printf(" ");
	}

	for (int j = 0; j <= _size; j++)
	{
		_Common::gotoXY(0, j);
		_Common::setColor(77);
		printf(" ");
		_Common::gotoXY(_size + 1, j);
		_Common::setColor(77);
		printf(" ");
	}
	int color=7;
	for (int i = 0; i < _size; i++){
		for (int j = 0; j < _size; j++){
			switch (getCheckAt(i, j))
			{
			case 'X':
				color=12;
				break;
			case 'O':
				color=10;
				break;
			default:
				color=7;
			}
			_pArr[i][j].draw(color);
		}
	}
	_Common::gotoXY(_pArr[0][0].getX() * 2 + 1, _pArr[0][0].getY() * 2 + 1);// di chuyển vào ô đầu
}

void _Board::draw(int i, int j, int color)
{
	_pArr[i][j].draw(color);
}
int _Board::checkBoard(int pX, int pY, unsigned char pTurn){
	for (int i = 0; i < _size; i++){
		for (int j = 0; j < _size; j++){
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY && _pArr[i][j].getCheck() == O_TRONG){
				if (_pArr[i][j].setCheck(pTurn))
					_used++;
				return _pArr[i][j].getCheck();
			}
		}
	}
	return 0;
}

unsigned char _Board::testBoard(int pX, int pY, unsigned char pTurn)
{
	//Kiểm tra đường dọc
	int dem = 1, i = pX, j = pY + 1;
	while (j < _size&&_pArr[i][j].getCheck() == pTurn)
	{
		dem++;
		j++;
		if (dem == 5)
		{
			for (int k = j - 1; k>j - 6; k--)
				draw(i, k, 94);
			return pTurn;
		}
	}

	i = pX, j = pY - 1;
	while (j >= 0 && _pArr[i][j].getCheck() == pTurn)
	{
		dem++;
		j--;
		if (dem == 5)
		{
			for (int k = j + 1; k < j + 6; k++)
				draw(i, k, 94);
			return pTurn;
		}
	}
	//Kiểm tra đường ngang
	dem = 1; i = pX + 1, j = pY;
	while (i < _size&&_pArr[i][j].getCheck() == pTurn)
	{
		dem++;
		i++;
		if (dem == 5)
		{
			for (int k = i - 1; k>i - 6; k--)
				draw(k, j, 94);
			return pTurn;
		}
	}

	i = pX - 1, j = pY;
	while (i >= 0 && _pArr[i][j].getCheck() == pTurn)
	{
		dem++;
		i--;
		if (dem == 5)
		{
			for (int k = i + 1; k < i + 6; k++)
				draw(k, j, 94);
			return pTurn;
		}
	}
	//Kiểm tra đường chéo chính
	dem = 1, i = pX + 1, j = pY + 1;
	while (i < _size&&j < _size&&_pArr[i][j].getCheck() == pTurn)
	{
		dem++;
		i++;
		j++;
		if (dem == 5)
		{
			while (dem>0)
			{
				draw(i - dem, j - dem, 94);
				dem--;
			}
			return pTurn;
		}
	}

	i = pX - 1, j = pY - 1;
	while (i >= 0 && j >= 0 && _pArr[i][j].getCheck() == pTurn)
	{
		dem++;
		j--;
		i--;
		if (dem == 5)
		{
			while (dem > 0)
			{
				draw(i + dem, j + dem, 94);
				dem--;
			}
			return pTurn;
		}
	}
	//Kiểm tra đường chéo phụ
	dem = 1, i = pX + 1, j = pY - 1;
	while (i < _size&&j >= 0 && _pArr[i][j].getCheck() == pTurn)
	{
		dem++;
		i++;
		j--;
		if (dem == 5)
		{
			while (dem>0)
			{
				draw(i - dem, j + dem, 94);
				dem--;
			}
			return pTurn;
		}
	}

	i = pX - 1, j = pY + 1;
	while (i >= 0 && j <_size && _pArr[i][j].getCheck() == pTurn)
	{
		dem++;
		j++;
		i--;
		if (dem == 5)
		{
			while (dem>0)
			{
				draw(i + dem, j - dem, 94);
				dem--;
			}
			return pTurn;
		}
	}
	//Kiểm tra ván hòa

	if (_used == _size*_size)
		return '0';
	return ' ';
}

