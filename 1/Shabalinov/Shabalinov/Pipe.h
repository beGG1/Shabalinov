#pragma once
class Pipe
{
private:
	size_t id;
	int lenght;
	int diametr;
	bool repear;

public:
	void pipe_print();
	void pipe_create(const int& max_id_pipe);
	size_t get_id();
	void pipe_edit();
	int get_lenght();
	int get_diametr();
	bool get_repear();

	void set_id(const int &number);
	void set_lenght(const int& number);
	void set_diametr(const int& number);
	void set_repear(const int& number);
};

