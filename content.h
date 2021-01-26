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
	friend void show_screen();
	friend int is_collision();
	friend int is_over();
	form();
	form(const form& a);
};