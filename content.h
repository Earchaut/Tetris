#pragma once
class form {
private:
	int content[200];
	int type;
	int axis;
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
	void up();
	void down();
	int drop();
	friend void show_screen();
	friend void eliminate();
	friend bool is_dropover();
	friend bool gameover();
	void spin();
	void spin_more();
	bool is_can_spin();
	form();
	form operator+(const form& a);
};

extern form now_screen;
extern form inside_screen;
extern bool is_hit_down;
extern bool is_gameover;
extern bool is_hit;
extern int score;

void show_screen();
void eliminate();
bool is_dropover();
int create();
bool gameover();
void show_gameover();