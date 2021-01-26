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

}

void form::create_z() {

}

void show_screen() {

}

int is_collision() {

}

int is_over() {

}

int create() {

}