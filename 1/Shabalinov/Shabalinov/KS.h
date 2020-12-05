#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h> // Нужно для распознания кирилицы 
#include <vector>
#include <string>
using namespace std;

class KS
{
private:
	size_t id;
	string name;
	int number_shop;
	int number_shop_working;
	double effective;
	int number_in_sort;
	int min_dist;

public:
	size_t get_id();
	string get_name();
	int get_min_dist();
	int get_number_in_sort();
	int get_effective();
	int get_number_shop();
	int get_number_shop_working();

	void ks_create(const int& max_id_ks);
	void ks_print();
	void ks_edit(int number);
	
	void set_id(const int& number);
	void set_name(const string& stroka);
	void set_number_shop(const int& number);
	void set_number_shop_working(const int& number);
	void set_number_in_sort(const int& number);
	void set_min_dist(const int& number);
	void set_effective();



};

