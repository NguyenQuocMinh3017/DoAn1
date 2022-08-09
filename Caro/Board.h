#include "Point.h"

class _Board{
private:
	int _size;
	int _left, _top;
	int _used = 0;
	_Point** _pArr;
public:
	int getSize();
	int getLeft();
	int getTop();
	int getXAt(int, int);
	int getYAt(int, int);
	int getCheckAt(int i, int j);

	_Board(int, int, int);
	~_Board();

	void loadData(FILE *f,bool checkFile);
	void saveData(FILE *f);
	void drawBoard();

	int checkBoard(int, int, unsigned char);
	unsigned char testBoard(int, int, unsigned char);

	void draw(int, int, int);
};