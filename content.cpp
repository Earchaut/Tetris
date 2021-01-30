#include<iostream>
#include<ctime>
#include<conio.h>
#include<Windows.h>
#include"content.h"

int is_create[7] = { 0 };

form::form() {
	for (int i = 0; i < 200; i++) {
		content[i] = 0;
	}
	type = 0;
	axis = 0;
}

form::form(const form& a) {
	for (int i = 0; i < 200; i++) {
		content[i] = a.content[i];
	}
	type = a.type;
	axis = a.axis;
}

form form::operator+(const form& a) {
	form r;
	for (int i = 0; i < 200; i++) {
		r.content[i] = content[i] + a.content[i];
	}
	return r;
}

void form::create_i() {
	now_screen.clear();
	now_screen.content[3] = 1;
	now_screen.content[4] = 1;
	now_screen.content[5] = 1;
	now_screen.content[6] = 1;
	type = 1;
	axis = 5;
}

void form::create_j() {
	now_screen.clear();
	now_screen.content[5] = 1;
	now_screen.content[13] = 1;
	now_screen.content[14] = 1;
	now_screen.content[15] = 1;
	type = 2;
	axis = 4;
}

void form::create_l() {
	now_screen.clear();
	now_screen.content[3] = 1;
	now_screen.content[13] = 1;
	now_screen.content[14] = 1;
	now_screen.content[15] = 1;
	type = 3;
	axis = 4;
}

void form::create_o() {
	now_screen.clear();
	now_screen.content[4] = 1;
	now_screen.content[5] = 1;
	now_screen.content[14] = 1;
	now_screen.content[15] = 1;
	type = 4;
}

void form::create_s() {
	now_screen.clear();
	now_screen.content[4] = 1;
	now_screen.content[5] = 1;
	now_screen.content[13] = 1;
	now_screen.content[14] = 1;
	type = 5;
	axis = 4;
}

void form::create_t() {
	now_screen.clear();
	now_screen.content[4] = 1;
	now_screen.content[13] = 1;
	now_screen.content[14] = 1;
	now_screen.content[15] = 1;
	type = 6;
	axis = 4;
}

void form::create_z() {
	now_screen.clear();
	now_screen.content[3] = 1;
	now_screen.content[4] = 1;
	now_screen.content[14] = 1;
	now_screen.content[15] = 1;
	type = 7;
	axis = 4;
}

void form::clear() {
	for (int i = 0; i < 200; i++) {
		content[i] = 0;
	}
	type = 0;
	axis = 0;
}

int form::drop() {
	if (!is_dropover()) {
		for (int i = 199; i > 9; i--) {
			content[i] = content[i - 10];
		}
		for (int i = 0; i < 10; i++) {
			content[i] = 0;
		}
		axis += 10;
		show_screen();
	}
	else return 1;
	return 0;
}

void form::right() {
	is_hit = true;
	bool is_can_move = true;
	for (int i = 9; i < 200; i += 10) {
		if (content[i] == 1) is_can_move = false;
	}
	if (is_can_move) {
		int row = 9;
		for (int r = 0; r < 9; r++) {
			for (int i = row; i < 200; i += 10) {
				content[i] = content[i - 1];
			}
			row--;
		}
		for (int i = 0; i < 200; i += 10) {
			content[i] = 0;
		}
		axis += 1;
	}
	show_screen();
	is_hit = false;
}

void form::left() {
	is_hit = true;
	bool is_can_move = true;
	for (int i = 0; i < 200; i += 10) {
		if (content[i] == 1) is_can_move = false;
	}
	if (is_can_move) {
		int row = 0;
		for (int r = 0; r < 9; r++) {
			for (int i = row; i < 199; i += 10) {
				content[i] = content[i + 1];
			}
			row++;
		}
		for (int i = 9; i < 200; i += 10) {
			content[i] = 0;
		}
		axis -= 1;
	}
	show_screen();
	is_hit = false;
}

void form::up() {
	is_hit = true;
	if (is_can_spin()) {
		if (type != 1 && type != 4) {
			spin();
		}
		else if (type == 1) {
			spin_more();
		}
	}
	show_screen();
	is_hit = false;
}

void form::down() {
	is_hit = true;
	is_hit_down = true;
	bool is_drop_down = false;
	while (!is_drop_down) {
		is_drop_down = now_screen.drop();
	}
	show_screen();
	is_hit_down = false;
	is_hit = false;
}

void show_screen() {
	int line = 0;
	print(score, 13, 1);
	for (int i = 0; i < 20; i++) {
		for (int k = 0; k < 10; k++) {
			if (now_screen.content[10 * line + k] + inside_screen.content[10 * line + k] > 0) {
				if (save.content[10 * line + k] == 0) {
					print(1, 5 + k, 3 + line);
				}
			}
			else if (save.content[10 * line + k] > 0) {
				print(2, 5 + k, 3 + line);
			}
		}
		line++;
		std::cout << std::endl;
	}
	save = now_screen + inside_screen;
}

void print(int type, int x, int y)
{
	HANDLE hd;
	COORD pos;
	pos.X = 2 * x;
	pos.Y = y;
	hd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hd, pos);
	if (type == 1) {
		std::cout << "■";
	}
	else if (type == 2) {
		std::cout << "□";
	}
	else {
		std::cout << type;
	}
	pos.X = 0;
	pos.Y = 0;
	SetConsoleCursorPosition(hd, pos);
}

void eliminate() {
	int line = 190;
	bool is_eliminate;
	for (; line > 10;) {
		is_eliminate = true;
		for (int i = line; i < line + 10; i++) {
			if (inside_screen.content[i] == 0) {
				is_eliminate = false;
				break;
			}
		}
		if (is_eliminate) {
			score += 100;
			for (int i = line; i < line + 10; i++) {
				for (int k = i; k > 10; k -= 10) {
					inside_screen.content[k] = inside_screen.content[k - 10];
				}
			}
			line += 10;
		}
		line -= 10;
	}
	show_screen();
}

bool is_dropover() {
	for (int i = 0; i < 190; i++) {
		if (now_screen.content[i] == 1) {
			if (now_screen.content[i + 10] == 0 && inside_screen.content[i + 10] > 0) {
				inside_screen = inside_screen + now_screen;
				score += 5;
				eliminate();
				return true;
			}
		}
	}
	for (int i = 190; i < 200; i++) {
		if (now_screen.content[i] == 1) {
			inside_screen = inside_screen + now_screen;
			score += 5;
			eliminate();
			return true;
		}
	}
	return false;
}

int create() {
	if (is_create[0] == 1 && is_create[1] == 1 && is_create[2] == 1 && is_create[3] == 1 &&
		is_create[4] == 1 && is_create[5] == 1 && is_create[6] == 1) {
		for (int i = 0; i < 7; i++) {
			is_create[i] = 0;
		}
	}
	srand((int)time(NULL));
	int c;
	do {
		c = rand() % 7;
	} while (is_create[c] == 1);
	is_create[c] = 1;
	switch (c) {
	case 0:
		now_screen.create_i();
		break;
	case 1:
		now_screen.create_o();
		break;
	case 2:
		now_screen.create_t();
		break;
	case 3:
		now_screen.create_l();
		break;
	case 4:
		now_screen.create_j();
		break;
	case 5:
		now_screen.create_z();
		break;
	case 6:
		now_screen.create_s();
		break;
	}
	return 0;
}

bool gameover() {
	for (int i = 10; i < 20; i++) {
		if (inside_screen.content[i] == 1) {
			is_gameover = true;
			return true;
		}
	}
	return false;
}

void form::spin() {
	int tmp1 = content[axis - 1];
	int tmp2 = content[axis + 9];
	content[axis - 1] = content[axis + 10];
	content[axis + 9] = content[axis + 11];
	content[axis + 10] = content[axis + 1];
	content[axis + 11] = content[axis - 9];
	content[axis + 1] = content[axis - 10];
	content[axis - 9] = content[axis - 11];
	content[axis - 10] = tmp1;
	content[axis - 11] = tmp2;
}

void form::spin_more() {
	spin();
	int tmp = content[axis - 2];
	content[axis - 2] = content[axis + 20];
	content[axis + 20] = content[axis + 2];
	content[axis + 2] = content[axis - 20];
	content[axis - 20] = tmp;
}

bool form::is_can_spin() {
	if (axis % 10 == 0 || axis % 10 == 9) return false;
	if (axis < 10 || axis >= 190) return false;
	if (type == 1 && axis < 20) return false;
	if ((inside_screen.content[axis - 1] > 0 && content[axis + 10] == 1) ||
		(inside_screen.content[axis + 9] > 0 && content[axis + 11] == 1) ||
		(inside_screen.content[axis + 10] > 0 && content[axis + 1] == 1) ||
		(inside_screen.content[axis + 11] > 0 && content[axis - 9] == 1) ||
		(inside_screen.content[axis + 1] > 0 && content[axis - 10] == 1) ||
		(inside_screen.content[axis - 9] > 0 && content[axis - 11] == 1) ||
		(inside_screen.content[axis - 10] > 0 && content[axis - 1] == 1) ||
		(inside_screen.content[axis - 11] > 0 && content[axis + 9] == 1)) {
		return false;
	}
	if (type == 1) {
		if ((inside_screen.content[axis - 2] > 0 && content[axis + 20] == 1) ||
			(inside_screen.content[axis + 20] > 0 && content[axis + 2] == 1) ||
			(inside_screen.content[axis + 2] > 0 && content[axis - 20] == 1) ||
			(inside_screen.content[axis - 20] > 0 && content[axis - 2] == 1)) {
			return false;
		}
	}
	return true;
}

void show_gameover() {
	HANDLE hd;
	COORD pos;
	pos.X = 0;
	pos.Y = 22;
	hd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hd, pos); std::cout << std::endl;
	std::cout << "              GAME OVER!!!" << std::endl;
	if (score < 1000) std::cout << " ";
	std::cout << "          你的最终得分是：" << score << std::endl << std::endl;
	Sleep(1000);
	system("pause");
}