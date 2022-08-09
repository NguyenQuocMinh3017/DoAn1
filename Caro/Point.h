#include"Common.h"

class _Point{
	int _x, _y;
	unsigned char _check = O_TRONG;
public:
	_Point();
	_Point(int, int);
	bool setCheck(unsigned char);
	int getX();
	int getY();
	unsigned char getCheck();
	void setX(int);
	void setY(int);
	void draw(int color)
	{
		_Common::gotoXY(_x + 1, _y + 1);
		_Common::setColor(color);
		printf("%c", _check);
	};
};
