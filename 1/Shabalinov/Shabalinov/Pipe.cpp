#include "Pipe.h"
#include <iostream>
#include <fstream>
#include <Windows.h> // Нужно для распознания кирилицы 
#include <vector>
#include <string>
using namespace std;

size_t Pipe::get_id()
{
	return id;
};
int Pipe::get_lenght()
{
	return lenght;
}
int Pipe::get_diametr()
{
	return diametr;
}
bool Pipe::get_repear()
{
	return repear;
}

void Pipe::set_id(const int& number)
{
	id = number;
};
void Pipe::set_lenght(const int& number)
{
	lenght = number;
}
void Pipe::set_diametr(const int& number)
{
	diametr = number;
}
void Pipe::set_repear(const int& number)
{
	repear = number;
}

void Pipe::pipe_print()
{
	cout << "id: " << id << endl << "Длина: " << lenght << endl << "Диаметр: " << diametr << endl;
	if (repear) {
		cout << "Состояние ремонта: В ремонте" << endl << endl;
	}
	else {
		cout << "Состояние ремонта: Не в Ремонте" << endl << endl;
	}
}


void Pipe::pipe_create(const int& max_id_pipe)
{
	id = max_id_pipe;
	// Ввод и проверка положительности длинны
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите длину: ";
		cin >> lenght;
	} while (cin.fail() || lenght <= 0);

	// Ввод и проверка положительности диаметра
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите диаметр: ";
		cin >> diametr;

	} while (cin.fail() || diametr <= 0);

	repear = false;
}
 

void Pipe::pipe_edit()
{
	if (repear) {
		repear = false;
	}
	else
	{
		repear = true;
	}
}
