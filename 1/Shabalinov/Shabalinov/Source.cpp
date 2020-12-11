
#include "Pipe.h"
#include "KS.h"
#include <iostream>
#include <fstream>
#include <Windows.h> // Нужно для распознания кирилицы 
#include <vector>
#include <string>
#include "Header.h"
#include "Graph.h"

using namespace std;

void print_menu() {
	cout << endl
		<< "1. Добавить трубу" << endl
		<< "2. Добавить КС" << endl
		<< "3. Просмотр всех объектов" << endl
		<< "4. Редактировать трубу" << endl
		<< "5. Редактировать КС" << endl
		<< "6. Сохранить" << endl
		<< "7. Загрузить" << endl
		<< "8. Удалить" << endl
		<< "9. Фильтр" << endl
		<< "10. Сеть" << endl
		<< "0. Выход" << endl << endl;
}

void save_pipe(vector<Pipe>& Pipes, string& fileName, int size)
{
	ofstream fout;
	fout.open(fileName + "Pipes" + ".txt", ios::out);
	if (fout.is_open())
	{
		fout << size << endl;
		for (int i = 0; i < Pipes.size(); i++) {
			fout << Pipes[i].get_id() << endl << Pipes[i].get_lenght() << endl << Pipes[i].get_diametr() << endl << Pipes[i].get_repear() << endl;
		}
		fout.close();
	}
}
vector<Pipe> load_pipe(const string& fileName)
{
	ifstream fin;
	fin.open(fileName + "Pipes" + ".txt", ios::in);
	Pipe P;
	vector<Pipe> Pipes;
	if (fin.is_open())
	{
		int max;
		fin >> max;
		for (int i = 0; i < max; i++) {
			int a;
			fin >> a;
			P.set_id(a);
			fin >> a;
			P.set_lenght(a);
			fin >> a;
			P.set_diametr(a);
			fin >> a;
			P.set_repear(a);
			Pipes.push_back(P);
		}

		fin.close();
	}
	else
	{
		cout << "Файл не найден" << endl;
	}
	return Pipes;
}

void save_ks(vector<KS>& KS1, const string& fileName, int size) {
	ofstream fout;
	fout.open(fileName + "KS" + ".txt", ios::out);
	if (fout.is_open())
	{
		fout << size << endl;
		for (int i = 0; i < KS1.size(); i++) {
			fout << KS1[i].get_id() << endl << KS1[i].get_name() << endl << KS1[i].get_number_shop()
				<< endl << KS1[i].get_number_shop_working() << endl << KS1[i].get_effective() << endl
				<< KS1[i].get_number_in_sort() << endl << KS1[i].get_min_dist() << endl;
		}
		fout.close();
	}
}



vector <KS> load_ks(const string& fileName) {
	int size;
	ifstream myfile(fileName + "KS" + ".txt");
	KS KS1;
	int a;
	string str;
	vector <KS> KSs1;
	if (myfile.is_open()) {
		getline(myfile, str);
		size = atoi(str.c_str());
		for (int i = 0; i < size; i++) {
			getline(myfile, str);
			a = atoi(str.c_str());
			KS1.set_id(a);
			getline(myfile, str);
			KS1.set_name(str);
			getline(myfile, str);
			a = atoi(str.c_str());
			KS1.set_number_shop(a);
			getline(myfile, str);
			a = atoi(str.c_str());
			KS1.set_number_shop_working(a);
			getline(myfile, str);
			a = atoi(str.c_str());
			KS1.set_effective();
			getline(myfile, str);
			a = atoi(str.c_str());
			KS1.set_number_in_sort(a);
			getline(myfile, str);
			a = atoi(str.c_str());
			KS1.set_min_dist(a);
			KSs1.push_back(KS1);
		}
	}
	myfile.close();
	return KSs1;

}

void edit_pipe(vector<Pipe>& Pipes)
{
	double i;
	int m;
	int index = -1;
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите id трубы ";
		cin >> i;
		m = (int)i;
	} while (cin.fail() || m < 0);

	for (int key = 0; key < Pipes.size(); key++)
	{
		if (Pipes[key].get_id() == m)
		{
			index = key;
			Pipes[key].pipe_edit();
		}

	}
	if (index == -1) {

		cout << "id не найден" << endl;

	}
}

void edit_ks(vector<KS>& KSs)
{
	double i;
	int m = -1;
	int keys;
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите id КС ";
		cin >> i;
		keys = (int)i;
	} while (cin.fail() || keys < 0);

	for (int i = 0; i < KSs.size(); i++) {
		if (KSs[i].get_id() == keys) {
			m = i;
			break;
		}
	}
	if (m == -1)
	{
		cout << "id не найден" << endl;
	}

	if (m != -1) {
		bool check = true;
		while (check) {

			int k;
			do {
				cout << "1 - Ввести цех в работу" << endl
					<< "2 - Вывести цех из работы" << endl
					<< "0 - Назад" << endl;
				cin.clear();
				cin.ignore(10000, '\n');
				cin >> k;
			} while (cin.fail() || k < 0 || k>2);
			switch (k)
			{
			case 1:
			{
				if (KSs[m].get_number_shop() == KSs[m].get_number_shop_working()) {
					cout << "Максимальное количество рабочих цехов" << endl;
					break;
				}
				else {
					int shops;
					do {
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "Количество цехов: ";
						cin >> shops;
					} while (shops <= 0 || cin.fail());
					if (KSs[m].get_number_shop_working() + shops <= KSs[m].get_number_shop()) {
						KSs[m].ks_edit(shops);
						KSs[m].set_effective();
						break;
					}
					else {
						cout << "Можно добавть максимум " << -KSs[m].get_number_shop_working() + KSs[m].get_number_shop()
							<< " цехов" << endl;
						break;
					}
				}
			}

			case 2:
			{
				if (KSs[m].get_number_shop_working() == 0) {
					cout << "Минимальное количество рабочих цехов" << endl;
					break;
				}
				else {
					int shops;
					do {
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "Количество цехов: ";
						cin >> shops;
					} while (shops <= 0 || cin.fail());
					if (KSs[m].get_number_shop_working() - shops >= 0) {
						KSs[m].ks_edit(-shops);
						KSs[m].set_effective();
						break;
					}
					else {
						cout << "Можно убрать максимум " << KSs[m].get_number_shop_working()
							<< " цехов" << endl;
						break;
					}
				}
			}

			case 0:
			{
				check = false;
				break;
			}
			default:
				cout << "Ошибка " << endl;
				break;
			}

		}
	}
}

//Удалить Трубу
void deletePipe(vector <Pipe>& P, Graph &G)
{
	int i;

	//Количество труб, которых надо удалить
	do {
		cout << "Введите количество труб, которых нужно удалить" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> i;
	} while (cin.fail() || i < 0 || i>P.size());


	//Ввод id этих труб
	for (int n = 0; n < i; n++) {
		double idP;
		int idPipe;
		do {
			cout << "Введите id труб, которых нужно удалить" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			cin >> idP;
			idPipe = (int)idP;
		} while (cin.fail() || idPipe < 0);


		//Поиск индекса 
		int index = -1;
		for (int m = 0; m < P.size(); m++) {
			if (P[m].get_id() == idPipe) {
				index = m;
				break;
			}
		}

		if (index == -1) {
			cout << "Ошибка. Трубы с таким id не существует" << endl;
			break;
		}
		G.pipe_delete(index);

		P.erase(P.begin() + index); //https://coderoad.ru/875103/Как-удалить-элемент-из-std-vector-по-индексу
	}


}



//Удалить KS
void deleteKS(vector <KS>& K, Graph &G) 
{
	int i;

	//Количество КС, которых надо удалить
	do {
		cout << "Введите количество КС, которых нужно удалить" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> i;
	} while (cin.fail() || i < 0 || i>K.size());


	//Ввод id этих КС
	for (int n = 0; n < i; n++) {
		double idK;
		int idKS;
		do {
			cout << "Введите id КС, которых нужно удалить" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			cin >> idK;
			idKS = (int)idK;
		} while (cin.fail() || idKS < 0);


		//Поиск индекса 
		int index = -1;
		for (int m = 0; m < K.size(); m++) {
			if (K[m].get_id() == idKS) {
				index = m;
				break;
			}
		}

		if (index == -1) {
			cout << "Ошибка. Трубы с таким id не существует" << endl;
			break;
		}
		
		G.ks_delete(index);
		K.erase(K.begin() + index); //https://coderoad.ru/875103/Как-удалить-элемент-из-std-vector-по-индексу
		
	}


}

vector <Pipe> pipe_filter(vector <Pipe>& P) {
	vector <Pipe> Pipes;
	for (int i = 0; i < P.size(); i++) {
		if (P[i].get_repear()) {
			Pipes.push_back(P[i]);
		}
	}
	return Pipes;

}

// Фильтр по эффективности
vector <KS> ks_filter_effect(vector <KS>& KS1, bool key, double number) {
	vector <KS> Bolshe;
	vector <KS> Menshe;

	for (int i = 0; i < KS1.size(); i++) {
		if (KS1[i].get_effective() >= number) {
			Bolshe.push_back(KS1[i]);
		}
		else
			Menshe.push_back(KS1[i]);
	}

	if (key)
		return Bolshe;
	else
		return Menshe;

}

// Фильтр по имени КС
vector <KS> ks_filter_name(vector <KS>& KS1, string Name) {
	vector <KS> NameV;
	for (int i = 0; i < KS1.size(); i++) {
		if (KS1[i].get_name() == Name) {
			NameV.push_back(KS1[i]);
		}
	}
	return NameV;
}

//Поиск порядкого номера

int find_nomer_pipe(vector<Pipe>& Pipe, size_t id) {
	int num = -1;
	for (int i = 0; i <= Pipe.size(); i++) {
		if (Pipe[i].get_id() == id) {
			num = i;
			break;
		}
	}
	return num;
}

int find_nomer_ks(vector<KS>& KS1, size_t id) {
	int num = -1;
	for (int i = 0; i <= KS1.size(); i++) {
		if (KS1[i].get_id() == id) {
			num = i;
			break;
		}
	}
	return num;
}



int findNumSort(vector<KS> KS) {
	int a = 0;
	for (int i = 0; i < KS.size(); i++) {
		if (KS[i].get_number_in_sort() == -1) {
			a++;
		}
	}
	return a;
}

int minimal(int a, int b)
{
	if (a >= b) 
	{
		return a;
	}
	else
	{
		return b;
	}
}


