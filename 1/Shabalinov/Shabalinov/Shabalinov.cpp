
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

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector <Pipe> Pipes;
	vector <KS> KSs;
	Graph G;
	G.graph_create(0, 0);
	
	while (true)
	{
		print_menu();

		int max_id_pipe;
		if (Pipes.size() == 0) {
			max_id_pipe = 0;
		}
		else {
			max_id_pipe = Pipes[Pipes.size() - 1].get_id() + 1;
		}

		
		int max_id_ks;
		if (KSs.size() == 0) {
			max_id_ks = 0;
		}
		else {
			max_id_ks = KSs[KSs.size() - 1].get_id() + 1;
		}
		

		int menu;
		cin >> menu;

		while (cin.fail() || menu < 0) {
			cin.clear();
			cin.ignore(10000, '\n');
			print_menu();
			cin >> menu;
		};

		switch (menu)
		{
		case 1:																	//Создать трубу
		{
			Pipe P;
			P.pipe_create(max_id_pipe);
			Pipes.push_back(P);
			G.add_pipe();
			break;
		}
		case 2:																	// Создать кс
		{
			KS K;
			K.ks_create(max_id_ks);
			KSs.push_back(K);
			G.add_ks();
			break;
		}
		case 3:																	//вывести трубы и кс
		{
			for (int i = 0; i < Pipes.size(); i++) {
				Pipes[i].pipe_print();
			}
			for (int i = 0; i < KSs.size(); i++) {
				KSs[i].ks_print();
			}
			break;
		}
		case 4:																	//редактировать трубу
		{
			edit_pipe(Pipes);
			break;
			
		}
		case 5:																	//редактировать кс
		{
			edit_ks(KSs);
			break;

		
		}
		case 6:																	//сохранить
		{
			cout << "Введите название файла: ";
			string fileName;
			cin.ignore();
			getline(cin, fileName);
			save_pipe(Pipes, fileName, Pipes.size());
			save_ks(KSs, fileName, KSs.size());
			G.save(KSs, Pipes, fileName);

			break;
		}


		case 7:																					//Загрузить
		{
			cout << "Введите название файла: ";
			string fileName;
			cin.ignore();
			getline(cin, fileName);
			Pipes = load_pipe(fileName);
			KSs = load_ks(fileName);
			G.load(KSs, Pipes, fileName);

			break;
		}
		case 8:														// Удалить Трубу или кс
		{
			bool check = true;
			while (check) {
				int keyDelete;
				do {
					cout << "1. Удалить трубу" << endl
						<< "2. Удалить КС" << endl
						<< "0. Назад" << endl;
					cin.clear();
					cin.ignore(10000, '\n');
					cin >> keyDelete;
				} while (cin.fail() || keyDelete < 0 || keyDelete > 2);

				switch (keyDelete)
				{
				case 1:
				{
					deletePipe(Pipes,G);
					
					
					break;
				}

				case 2:
				{
					deleteKS(KSs,G);
					break;
				}
				case 0:
				{
					check = false;
					break;
				}
				default:
					cout << "Ошибка" << endl;
					break;
				}
			}
			break;
		}
		case 9:														// Фильтры
		{
			
			vector <Pipe> filterPipe;				
			vector <KS> filterKSEffect;				
			vector <KS> filterKSName;
			vector <KS> filterKS;
			int keyFilter;
			do {
				cout << "1. Фильтр труба (Работающие)" << endl
					<< "2. Фильтр КС" << endl
					<< "0. Назад" << endl;
				cin.clear();
				cin.ignore(10000, '\n');
				cin >> keyFilter;
			} while (cin.fail() || keyFilter < 0 || keyFilter > 2);

			switch (keyFilter)
			{
			case 1:
			{
				filterPipe = pipe_filter(Pipes);
				for (int i = 0; i < filterPipe.size(); i++) {
					filterPipe[i].pipe_print();
				}
				break;
			}
			case 2:
			{
				int keyFilterKS;
				do {
					cout << "1. Фильтр по имени" << endl
						<< "2. Фильтр по эффективности" << endl;

					cin.clear();
					cin.ignore(10000, '\n');
					cin >> keyFilterKS;
				} while (cin.fail() || keyFilterKS < 1 || keyFilterKS > 2);

				switch (keyFilterKS)
				{

				case 1:
				{
					
					string name;
					cout << "Введите имя КС" << endl;
					cin.ignore();
					getline(cin, name);
					filterKSName = ks_filter_name(KSs, name);
					if (filterKSName.size() == 0) {
						cout << "Результатов не найдено" << endl;
					}
					else {
						for (int i = 0; i < filterKSName.size(); i++) {
							filterKSName[i].ks_print();
						}
						filterKS = filterKSName;
					}


					break;
				}

				case 2:
				{
					int keyFilterKSE;
					do {
						cout << "1. Больше или равно введенному числу" << endl
							<< "2. Меньше данного числа" << endl;

						cin.clear();
						cin.ignore(10000, '\n');
						cin >> keyFilterKSE;
					} while (cin.fail() || keyFilterKSE < 1 || keyFilterKSE > 2);

					double number;
					do {
						cout << "Введите число" << endl;

						cin.clear();
						cin.ignore(10000, '\n');
						cin >> number;
					} while (cin.fail() || number < 0 || number > 100);


					switch (keyFilterKSE)
					{
					case 1:
					{

						filterKSEffect = ks_filter_effect(KSs, true, number);
						for (int i = 0; i < filterKSEffect.size(); i++) {
							filterKSEffect[i].ks_print();
						}
						filterKS = filterKSEffect;
						break;
					}
					case 2:
					{
						filterKSEffect = ks_filter_effect(KSs, false, number);
						for (int i = 0; i < filterKSEffect.size(); i++) {
							filterKSEffect[i].ks_print();
						}
						filterKS = filterKSEffect;
						break;
					}

					default:
						cout << "error" << endl;
						break;
					}
					break;
				}

				default:
					cout << "Ошибка" << endl;
					break;
				}


				break;
			}
			default:
				cout << "Ошибка";
				break;
			}
			break;
		}

		case 10:
		{
			bool check1 = true;
			while (check1) {
				int grafKey;
				do {
					cout << "1. Удалить сеть" << endl;
					cout << "2. Добавить соединение" << endl;
					cout << "3. Убрать соединение" << endl;
					cout << "4. Показать" << endl;
					cout << "5. Топологическая сортировка" << endl;
					cout << "6. Максимальная пропускная способность" << endl;
					cout << "7. Кратчайший путь" << endl;
					cout << "0. Выход" << endl;
					cin.clear();
					cin.ignore(10000, '\n');
					double idP;
					cin >> idP;
					grafKey = (int)idP;
				} while (cin.fail() || grafKey < 0 || grafKey>7);
				switch (grafKey)
				{
				case 1:
				{
					G.delete_all();
					break;
				}
				case 2:
				{


					G.add_conection(KSs, Pipes,max_id_ks, max_id_pipe);

					break;
				}

				case 3:
				{
					
					G.delete_conection(KSs, Pipes, max_id_ks, max_id_pipe);

					break;
				}

				case 4:
				{
					

					G.graph_show();

					break;
				}

				case 5:


				{

					
					
					G.top_sort(KSs, Pipes, max_id_ks, max_id_pipe,true);
					for (int j = 0; j < KSs.size(); j++) {
						KSs[j].set_number_in_sort(-1);
					}
					

					break;
				}

				case 6:
				{

					
					Graph G1 = G;
					G1.max_propusk(KSs, Pipes, max_id_ks, max_id_pipe);
					for (int j = 0; j < KSs.size(); j++) {
						KSs[j].set_number_in_sort(-1);
					}
					
					break;
				}

				case 7:
				{

					Graph G1 = G;
					G1.max_lenght(KSs, Pipes, max_id_ks, max_id_pipe);
					for (int j = 0; j < KSs.size(); j++) {
						KSs[j].set_number_in_sort(-1);
					}
					break;
				}

				case 0:
				{
					check1 = false;
					break;
				}


				default:
					cout << "error" << endl;
					break;
				}
			}

			break;
		}
		case 0:
		{

			return 0;
		}
		default:
		{
			cout << "Ошибка" << endl;
			break;
		}

		}
		
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
