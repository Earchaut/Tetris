#include<iostream>
#include<Windows.h>
#include<process.h>
#include<conio.h>
#include"content.h"
using namespace std;

form now_screen;
form inside_screen;
form save;
bool is_hit_down = false;
bool is_gameover = false;
bool is_hit = false;
int score = 0;

void reply_hit(void* g) {
	bool is_gameover = (bool*)g;
	int ch;
	while (is_gameover) {
		if (_kbhit() && !is_hit) {
			ch = _getch();
			if (ch == 97 || ch == 75) {
				now_screen.left();
			}
			else if (ch == 100 || ch == 77) {
				now_screen.right();
			}
			else if (ch == 119 || ch == 72) {
				now_screen.up();
			}
			else if (ch == 115 || ch == 80) {
				now_screen.down();
			}
		}
	}
	_endthread();
}

int main() {
	_beginthread(reply_hit, 0, &is_gameover);
	system("cls");
	cout << "               俄罗斯方块" << endl;
	cout << "            您的当前分数：" << score << endl << endl;
	for (int i = 0; i < 20; i++) {
		cout << "          ";
		for (int k = 0; k < 10; k++) {
			cout << "□";
		}
		cout << endl;
	}
	while (!gameover()) {
		create();
		show_screen();
		Sleep(800);
		bool is_drop_down = false;
		while (!is_drop_down) {
			if (!is_hit) {
				is_hit = true;
				is_drop_down = now_screen.drop();
				is_hit = false;
				Sleep(800);
			}
		}
	}
	show_gameover();
	return 0;
}