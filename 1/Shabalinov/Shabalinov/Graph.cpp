#include "Graph.h"

#include "Pipe.h"
#include "KS.h"
#include <iostream>
#include <fstream>
#include <Windows.h> // Нужно для распознания кирилицы 
#include <vector>
#include <string>
#include "Header.h"
using namespace std;
void Graph::graph_create(size_t P, size_t K)
{
	vector <int> a;
	for (int i = 0; i < K; i++)
	{
		a.push_back(0);
		KS1++;
	}
	for (int i = 0; i < P; i++)
	{
		Insident.push_back(a);
		Pipe1++;
	}
	for (int i = 0; i < K; i++)
	{
		Smej.push_back(a);
	}
}

void Graph::graph_show()
{

	cout << "Матрица инцидентности" << endl;
	for (int i = 0; i < KS1; i++) {
		for (int j = 0; j < Pipe1; j++) {
			cout << Insident[j][i] << "  ";
		}
		cout << endl;
	}
	cout << endl <<
		"Матрица смежности" << endl;

	for (int i = 0; i < KS1; i++) {
		for (int j = 0; j < KS1; j++) {
			cout << Smej[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;

}

size_t Graph::get_KS()
{
	return KS1;
}

size_t Graph::get_Pipe()
{
	return Pipe1;
}

void Graph::add_conection(vector<KS> KSs, vector<Pipe> Pipes, int max_id_ks, int max_id_pipe)
{
	double idK1;
	int idKS1;
	do {
		cout << "Введите id начальной КС" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> idK1;
		idKS1 = (int)idK1;
	} while (cin.fail() || idKS1 < 0 || idKS1 > max_id_ks - 1);
	int start = find_nomer_ks(KSs, idKS1);

	double idK2;
	int idKS2;
	do {
		cout << "Введите id конечной КС" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> idK2;
		idKS2 = (int)idK2;
	} while (cin.fail() || idKS2 < 0 || idKS2 > max_id_ks - 1);


	int finish = find_nomer_ks(KSs, idKS2);
	if (start == -1 || finish == -1) {
		cout << "Id не найдены" << endl;
		return;
	}

	double idPipe;
	int idP;
	do {
		cout << "Введите id Трубы" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> idPipe;
		idP = (int)idPipe;
	} while (cin.fail() || idP < 0 || idP > max_id_pipe - 1);


	int rebro = find_nomer_pipe(Pipes, idP);
	if (rebro == -1) {
		cout << "Id не найдены" << endl;
		return;
	}

	for (int j = 0; j < Pipes.size(); j++) {
		if (Insident[rebro][j] != 0) {
			cout << "Это ребро уже было использованно" << endl;
			break;
		}
	}

	Smej[idKS1][idKS2] = 1;
	Insident[rebro][idKS1] = 1;
	Insident[rebro][idKS2] = -1;

}

void Graph::delete_conection(vector<KS> KSs, vector<Pipe> Pipes, int max_id_ks, int max_id_pipe)
{
	double idK1;
	int idKS1;
	do {
		cout << "Введите id первой КС" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> idK1;
		idKS1 = (int)idK1;
	} while (cin.fail() || idKS1 < 0 || idKS1 > max_id_ks - 1);
	int start = find_nomer_ks(KSs, idKS1);

	double idK2;
	int idKS2;
	do {
		cout << "Введите id второй КС" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> idK2;
		idKS2 = (int)idK2;
	} while (cin.fail() || idKS2 < 0 || idKS2 > max_id_ks - 1);


	int finish = find_nomer_ks(KSs, idKS2);
	if (start == -1 || finish == -1) {
		cout << "Id не найдены" << endl;
		return;
	}
	Smej[idKS1][idKS2] = 0;
	Smej[idKS2][idKS1] = 0;
	for (int j = 0; j < Pipes.size(); j++)
	{
		if ((Insident[j][start] == 1 && Insident[j][finish] == -1) || (Insident[j][start] == -1 && Insident[j][finish] == 1))
		{
			Insident[j][start] = 0;
			Insident[j][finish] = 0;

		}
	}
}

void Graph::top_sort(vector<KS> &KSs, vector<Pipe> &Pipes, int max_id_ks, int max_id_pipe, bool show_result)
{
	int maxNum = 1;
	for (int i = 0; i < KS1; i++) {
		int count = 0;
		int countminus = 0;
		for (int j = 0; j < Pipe1; j++) {
			if (Insident[j][i] == 1) {
				count++;

			}
			if (Insident[j][i] == -1) {
				countminus++;

			}


			if (count != 0 && countminus == 0)
			{
				KSs[i].set_number_in_sort(maxNum);
			}
		}
	}

	// Отбросить изолированные точки
	for (int i = 0; i < KS1; i++) {
		int count = 0;
		int countminus = 0;
		for (int j = 0; j < Pipe1; j++) {
			if (Insident[j][i] == 1) {
				count++;

			}
			if (Insident[j][i] == -1) {
				countminus++;

			}

			if (count == 0 && countminus == 0) {
				KSs[i].set_number_in_sort(0);


			}
		}

	}



	int numOfMinusOdin = findNumSort(KSs);
	while (numOfMinusOdin > 0 && maxNum <= KS1 + 1) {
		for (int j = 0; j < KS1; j++) {
			if (KSs[j].get_number_in_sort() == maxNum) {
				for (int i = 0; i < KS1; i++) {
					if (Smej[j][i] == 1) {
						maxNum++;
						KSs[i].set_number_in_sort(maxNum);
						numOfMinusOdin--;
					}
				}
			}
		}
		if (maxNum == KS1 + 1)
		{
			cout << "Граф содержит цикл" << endl;
		}
		maxNum++;

	}

	if (show_result) {
		for (int i = 1; i <= maxNum; i++) {
			for (int j = 0; j < KS1; j++) {
				if (KSs[j].get_number_in_sort() == i) {
					cout << KSs[j].get_id() << "  ";
				}
			}
		}

		for (int i = 0; i < KS1; i++) {
			KSs[i].set_number_in_sort(-1);
		}
	}

	cout << endl;

}

void Graph::delet_not_working(vector<KS> KSs, vector<Pipe>Pipes, int max_id_ks, int max_id_pipe)
{

	for (int i = 0; i < KS1; i++) {
		if (KSs[i].get_number_shop_working() == 0) 
		{
			for (int j = 0; j < Pipe1; j++) 
			{																	//Если numshopworking == 0
				if (Insident[j][i] != 0)
				{
					for (int m = 0; m < KS1; m++)
					{
						Insident[j][m] = 0;
					}
				}

			}
		}
	}


	for (int i = 0; i < Pipe1; i++) 
	{
		if (Pipes[i].get_repear())
		{
			for (int j = 0; j < KS1; j++)
			{

				Insident[i][j] = 0;

			}
		}
	}
}

void Graph::max_propusk(vector<KS> KSs, vector<Pipe>Pipes, int max_id_ks, int max_id_pipe)
{
	delet_not_working(KSs, Pipes, max_id_ks, max_id_pipe);
	top_sort(KSs, Pipes, max_id_ks, max_id_pipe, false);


	double idK1;
	int idKS1;
	do {
		cout << "Введите id начальной КС" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> idK1;
		idKS1 = (int)idK1;
	} while (cin.fail() || idKS1 < 0 || idKS1 > max_id_ks - 1);

	int start = find_nomer_ks(KSs, idKS1);

	double idK2;
	int idKS2;
	do {
		cout << "Введите id конечной КС" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> idK2;
		idKS2 = (int)idK2;
	} while (cin.fail() || idKS2 < 0 || idKS2 > max_id_ks - 1);


	int finish = find_nomer_ks(KSs, idKS2);


	if (start == -1 || finish == -1) {
		cout << "Id не найдены" << endl;
		return;
	}

	int max_provod = -1;
	int provod = -1;
	bool check = true;


	if (KSs[start].get_number_in_sort() > KSs[finish].get_number_in_sort()) {
		cout << "Путь не найден" << endl;
		return;
	}
	KSs[start].set_min_dist(0);
	//for (int i = KSs[start].numberInSort; i < KSs[finish].numberInSort; i++) {
	for (int j = 0; j < KS1; j++) 
	{
		if (Smej[start][j] == 1) 
		{
			int pipe = 0;
			for (int r = 0; r < Pipe1; r++) 
			{
				if (Insident[r][start] == 1 && Insident[r][j] == -1) 
				{
					pipe = r;
				}
			}

			KSs[j].set_min_dist(Pipes[pipe].get_diametr());

		}

	}
	//}


	for (int m = KSs[start].get_number_in_sort() + 1; m < KSs[finish].get_number_in_sort(); m++) {

		for (int i = 0; i < KS1; i++)
			if (KSs[i].get_number_in_sort() == m && KSs[i].get_min_dist() != -1) {

				for (int j = 0; j < KS1; j++) {
					if (Smej[i][j] == 1) {
						int pipe = 0;
						for (int r = 0; r < Pipe1; r++) {
							if (Insident[r][i] == 1 && Insident[r][j] == -1) {
								pipe = r;
							}
						}

						if (KSs[j].get_min_dist() == -1 || KSs[j].get_min_dist() < minimal(KSs[i].get_min_dist(), Pipes[pipe].get_diametr())) {
							KSs[j].set_min_dist(minimal(KSs[i].get_min_dist(), Pipes[pipe].get_lenght()));
						}
					}

				}

			}
	}




	if (KSs[finish].get_min_dist() != -1) {
		cout << "Максимальная пропускная способность " << KSs[finish].get_min_dist() << endl;
	}
	else {
		cout << "Путь не существует" << endl;
	}

	for (int i = 0; i < KS1; i++) {
		KSs[i].set_min_dist(-1);
		KSs[i].set_number_in_sort(-1);
	}
}

void Graph::max_lenght(vector<KS> KSs, vector<Pipe> Pipes, int max_id_ks, int max_id_pipe)
{

	double idK1;
	int idKS1;
	do {
		cout << "Введите id начальной КС" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> idK1;
		idKS1 = (int)idK1;
	} while (cin.fail() || idKS1 < 0 || idKS1 > max_id_ks - 1);

	int start = find_nomer_ks(KSs, idKS1);

	double idK2;
	int idKS2;
	do {
		cout << "Введите id конечной КС" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> idK2;
		idKS2 = (int)idK2;
	} while (cin.fail() || idKS2 < 0 || idKS2 > max_id_ks - 1);


	int finish = find_nomer_ks(KSs, idKS2);


	if (start == -1 || finish == -1) {
		cout << "Id не найдены" << endl;
		return;
	}

	int minRast = -1;
	int Rast = -1;
	top_sort(KSs, Pipes, max_id_ks, max_id_pipe, false);
	

	bool check = true;

	if (KSs[start].get_number_in_sort() > KSs[finish].get_number_in_sort()) {
		cout << "Путь не найден" << endl;
		return;
	}
	KSs[start].set_min_dist(0);
	//for (int i = KSs[start].numberInSort; i < KSs[finish].numberInSort; i++) {
	for (int j = 0; j < KS1; j++) {
		if (Smej[start][j] == 1) {
			int pipe;
			for (int r = 0; r < Pipe1; r++) {
				if (Insident[r][start] == 1 && Insident[r][j] == -1) {
					pipe = r;
				}
			}

			KSs[j].set_min_dist(Pipes[pipe].get_lenght());

		}

	}
	//}


	for (int m = KSs[start].get_number_in_sort() + 1; m < KSs[finish].get_number_in_sort(); m++) {

		for (int i = 0; i < KS1; i++)
			if (KSs[i].get_number_in_sort() == m && KSs[i].get_min_dist() != -1) {

				for (int j = 0; j < KS1; j++) {
					if (Smej[i][j] == 1) {
						int pipe;
						for (int r = 0; r < Pipe1; r++) {
							if (Insident[r][i] == 1 && Insident[r][j] == -1) {
								pipe = r;
							}
						}

						if (KSs[j].get_min_dist() == -1 || KSs[j].get_min_dist() > KSs[i].get_min_dist() + Pipes[pipe].get_lenght()) {
							KSs[j].set_min_dist(KSs[i].get_min_dist() + Pipes[pipe].get_lenght());
						}
					}

				}

			}
	}




	if (KSs[finish].get_min_dist() != -1) {
		cout << "Минимальное расстояние " << KSs[finish].get_min_dist() << endl;
	}
	else {
		cout << "Путь не существует" << endl;
	}

	for (int i = 0; i < KS1; i++) {
		KSs[i].set_min_dist(-1);
		KSs[i].set_number_in_sort(-1);
	}
}

void Graph::add_pipe()
{
	vector <int> a;
	Pipe1++;
	for (int i = 0; i < KS1; i++)
	{
		a.push_back(0);
	}
	Insident.push_back(a);
}

void Graph::add_ks()
{
	vector <int> a;
	KS1++;
	for (int i = 0; i < Pipe1; i++)
	{
		Insident[i].push_back(0);
	}

	for (int i = 0; i < KS1 -1; i++)
	{
		a.push_back(0);
	}
	Smej.push_back(a);

	for (int i = 0; i < KS1; i++)
	{
		Smej[i].push_back(0);
	}
}

void Graph::load(vector<KS> KSs, vector<Pipe> Pipes, string fileName)
{
	ifstream fin;
	fin.open(fileName + "Insident" + ".txt", ios::in);
	graph_create(Pipes.size(), KSs.size());
	if (fin.is_open()) {
		for (int j = 0; j < KSs.size(); j++)
		{
			for (int i = 0; i < Pipes.size(); i++) {
				fin >> Insident[i][j];
			}
		}
		fin.close();
	}

	fin.open(fileName + "Smej" + ".txt", ios::in);

	if (fin.is_open())
	{
		for (int j = 0; j < KSs.size(); j++)
		{
			for (int i = 0; i < KSs.size(); i++) {
				fin >> Smej[i][j];
			}
		}
		fin.close();
	}
}

void Graph::pipe_delete(int index)
{
	int start = -1;
	int finish = -1;
	for (int j = 0; j < KS1; j++)
	{
		
		if (Insident[index][j] == 1)
		{
			start = j;
		}
		if (Insident[index][j] == -1)
		{
			finish = j;
		}
	}
	if (start != -1 && finish != -1)
	{
		Smej[start][finish] = 0;
	}

	Pipe1--;
	Insident.erase(Insident.begin() + index);
}

void Graph::delete_all()
{
	for (int i = 0; i < KS1; i++)
	{
		for (int j = 0; j < KS1; j++)
		{
			Smej[i][j] = 0;
		}
	}
	for (int i = 0; i < Pipe1; i++)
	{
		for (int j = 0; j < KS1; j++)
		{
			Insident[i][j] = 0;
		}
	}
}

void Graph::ks_delete(int index)
{
	int start = -1;
	int finish = -1;
	Smej.erase(Smej.begin() + index);
	for (int i = 0; i < KS1-1; i++)
	{
		Smej[i].erase(Smej[i].begin() + index);
	}
	KS1--;
	for (int i = 0; i < Pipe1; i++)
	{
		if (Insident[i][index] != 0)
		{
			for (int j = 0; j < KS1 + 1; j++)
			{
				Insident[i][j] = 0;
			}
		}

	}
	for (int i = 0; i < KS1; i++)
	{
		Insident[i].erase(Insident[i].begin() + index);
	}
}

void Graph::save(vector<KS> KSs, vector<Pipe>Pipes, string fileName)
{
	ofstream fout;
	fout.open(fileName + "Insident" + ".txt", ios::out);
	if (fout.is_open())
	{
		for (int j = 0; j < KSs.size(); j++)
		{
			for (int i = 0; i < Pipes.size(); i++) {
				fout << Insident[i][j] << endl;
			}
		}
		fout.close();
	}
	fout.open(fileName + "Smej" + ".txt", ios::out);
	if (fout.is_open())
	{
		for (int j = 0; j < KSs.size(); j++)
		{
			for (int i = 0; i < KSs.size(); i++) {
				fout << Smej[i][j] << endl;
			}
		}
		fout.close();
	}
}


