#include<iostream>
#include<Windows.h>
#include<process.h>
#include<conio.h>
#include"content.h"
using namespace std;

form now_screen;
form inside_screen;
bool is_hit_down = false;
bool is_gameover = false;

void reply_hit(void* g) {
	bool is_gameover = (bool*)g;
	int ch;
	while (is_gameover) {
		if (_kbhit()) {
			ch = _getch();
			cout << ch << endl;
			if (ch == 97 || ch == 75) {    //×ó
				now_screen.left();
			}
			else if (ch == 100 || ch == 77) {    //ÓÒ
				now_screen.right();
			}
			else if (ch == 115 || ch == 80) {    //ÏÂ
				now_screen.down();
			}
		}
	}
	_endthread();
}

int main() {
	_beginthread(reply_hit, 0, &is_gameover);
	/*²âÊÔÓÃ
	for (int i = 0; i < 3; i++) {
		now_screen.create_t();
		show_screen();
		while (!is_dropover()) {
			if (!is_hit_down) {
				now_screen.drop();
				show_screen();
				Sleep(800);
			}
		}
	}
	*/
	return 0;
}