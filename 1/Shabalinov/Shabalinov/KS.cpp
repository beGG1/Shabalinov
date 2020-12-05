#include "KS.h"

size_t KS::get_id()
{
    return id;
}

int KS::get_effective()
{
	return effective;
}
int KS::get_min_dist()
{
    return min_dist;
}
int KS::get_number_shop()
{
	return number_shop;
}
int KS::get_number_shop_working()
{
	return number_shop_working;
}
void KS::set_effective()
{
	effective = number_shop_working / number_shop;
}
string KS::get_name()
{
    return name;
}

int KS::get_number_in_sort()
{
	return number_in_sort;
}

void KS::ks_create(const int& max_id_ks)
{
	id = max_id_ks;
	cout << "Введите название КС: ";
	cin.ignore();
	getline(cin, name);

	number_in_sort = -1;
	min_dist= -1;

	double check;
	int m = 0;
	do {
		if (m != 0) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Количество цехов: ";
			cin >> check;
			number_shop = int(check);
		}
		else
		{
			cout << "Количество цехов: ";
			cin >> check;
			number_shop = int(check);
		}
	} while (cin.fail() ||  number_shop <= 0);

	number_shop_working = number_shop;

	effective = double(number_shop_working) / double(number_shop) * 100;
}

void KS::ks_print()
{
	cout << "id: " << id << endl
		<< "Навание КС: " << name << endl
		<< "Количество цехов: " << number_shop << endl
		<< "Количество цехов в работе: " << number_shop_working << endl
		<< "Эффективность: " << effective << endl << endl;
}

void KS::ks_edit(int number)
{
	number_shop_working += number;
}

void KS::set_id(const int& number)
{
	id = number;
}

void KS::set_name(const string& stroka)
{
	name = stroka;
}

void KS::set_number_shop(const int& number)
{
	number_shop = number;
}

void KS::set_number_shop_working(const int& number)
{
	number_shop_working = number;
}

void KS::set_number_in_sort(const int& number)
{
	number_in_sort = number;
}

void KS::set_min_dist(const int& number)
{
	min_dist = number;
}
