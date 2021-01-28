#pragma once
class form {
private:
	int content[200];
	int type[200];
public:
	void create_i();
	void create_o();
	void create_t();
	void create_l();
	void create_j();
	void create_z();
	void create_s();
	void clear();
	void left();
	void right();
	void down();
	void drop();
	friend void show_screen();
	friend int is_collision();
	friend bool is_dropover();
	form();
	form(const form& a);
};

extern form now_screen;
extern form inside_screen;
extern bool is_hit_down;
extern bool is_gameover;

void show_screen();
int is_collision();
bool is_dropover();
int create();