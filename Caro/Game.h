#include"Board.h"

class _Game{
	_Board* _b;// một bàn cờ 
	unsigned char _turn;// lượt chơi: 'X' lượt người chơi 'X' & 'O' lượt người chơi 'O' 
	int _x, _y; // Tọa độ hiện hành của nháy chuột 
	int _command; // phím gõ từ người dùng 
	bool _loop; // Biến quyết định thoát game hay không 
public:
	_Game(int, int, int);
	~_Game();

	int getCommand();
	bool isContinue();
	unsigned char waitKeyBoard(); // Hàm nhận phím từ người dùng 
	unsigned char askContinue();

	void startGame(); // Hàm bắt đầu game 
	void exitGame(); // Hàm thoát game 
	void playGame();
	void GiaoDien();
	void loadData(char *);
	void saveData(char *, bool checkCont);


	int processFinish();
	bool processCheckBoard();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	void printPoint();
};
