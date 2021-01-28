#include<iostream>
#include<ctime>
#include"content.h"

form::form() {
	for (int i = 0; i < 200; i++) {
		content[i] = 0;
		type[i] = 0;
	}
}

form::form(const form& a) {
	for (int i = 0; i < 200; i++) {
		content[i] = a.content[i];
		type[i] = a.type[i];
	}
}

void form::create_i() {
	
}

void form::create_j() {

}

void form::create_l() {

}

void form::create_o() {

}

void form::create_s() {

}

void form::create_t() {
	now_screen.content[4] = 1;
	now_screen.content[13] = 1;
	now_screen.content[14] = 1;
	now_screen.content[15] = 1;
}

void form::create_z() {

}

void form::clear() {
	for (int i = 0; i < 200; i++) {
		content[i] = 0;
	}
}

void form::drop() {
	for (int i = 199; i > 9; i--) {
		content[i] = content[i - 10];
	}
	for (int i = 0; i < 10; i++) {
		content[i] = 0;
	}
}

void form::right() {

}

void form::left() {

}

void form::down() {
	is_hit_down = true;
	while (!is_dropover()) {
		now_screen.drop();
		show_screen();
	}
	is_hit_down = false;
}

void show_screen() {
	int line = 0;
	system("cls");
	std::cout << "¶íÂÞË¹·½¿é" << std::endl << std::endl;
	for (int i = 0; i < 20; i++) {
		for (int k = 0; k < 10; k++) {
			if (now_screen.content[10 * line + k] + inside_screen.content[10 * line + k] > 0) {
				std::cout << "¡ö";
			}
			else std::cout << "¡õ";
		}
		line++;
		std::cout << std::endl;
	}
}

int is_collision() {
	return 0;
}

bool is_dropover() {
	for (int i = 0; i < 190; i++) {
		if (now_screen.content[i] == 1) {
			if (inside_screen.content[i + 10] == 1) return true;
		}
	}
	for (int i = 190; i < 200; i++) {
		if (now_screen.content[i] == 1) return true;
	}
	return false;
}

int create() {
	return 0;
}