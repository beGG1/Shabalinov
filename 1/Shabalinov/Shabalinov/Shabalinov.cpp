
#include "Pipe.h"
#include "KS.h"
#include <iostream>
#include <fstream>
#include <Windows.h> // Нужно для распознания кирилицы 
#include <vector>
#include <string>
#include "Header.h"
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector <Pipe> Pipes;
	vector <KS> KSs;
	vector <Pipe> filterPipe;
	vector <KS> filterKSEffect;
	vector <KS> filterKSName;
	vector <KS> filterKS;
	const int maxPipe = 50;
	const int maxKS = 50;
	int dataInsident[maxKS][maxPipe];
	int dataSmej[maxKS][maxKS];
	for (int i = 0; i < maxKS; i++) {
		for (int j = 0; j < maxPipe; j++) {
			dataInsident[i][j] = 0;
		}
	}
	for (int i = 0; i < maxKS; i++) {
		for (int j = 0; j < maxKS; j++) {
			dataSmej[i][j] = 0;
		}
	}
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
			break;
		}
		case 2:																	// Создать кс
		{
			KS K;
			K.ks_create(max_id_ks);
			KSs.push_back(K);
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

			//save matrix
			ofstream fout;
			fout.open(fileName + "Insident" + ".txt", ios::out);
			if (fout.is_open())
			{
				for (int j = 0; j < KSs.size(); j++)
				{
					for (int i = 0; i < Pipes.size(); i++) {
						fout << dataInsident[j][i] << endl;
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
						fout << dataSmej[j][i] << endl;
					}
				}
				fout.close();
			}
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

			ifstream fin;
			fin.open(fileName + "Insident" + ".txt", ios::in);

			if (fin.is_open()) {
				for (int j = 0; j < KSs.size(); j++)
				{
					for (int i = 0; i < Pipes.size(); i++) {
						fin >> dataInsident[j][i];
					}
				}
				fin.close();
			}

			fin.open(fileName + "Smej" + ".txt", ios::in);

			if (fin.is_open()) {
				for (int j = 0; j < KSs.size(); j++)
				{
					for (int i = 0; i < KSs.size(); i++) {
						fin >> dataSmej[j][i];
					}
				}
				fin.close();
			}
			break;
		}
		case 8:														// Удалить Трубу или кс
		{
			for (int i = 0; i <= KSs.size(); i++) {
				for (int j = 0; j <= Pipes.size(); j++) {
					dataInsident[i][j] = 0;
				}
			}
			for (int i = 0; i <= KSs.size(); i++) {
				for (int j = 0; j <= KSs.size(); j++) {
					dataSmej[i][j] = 0;
				}
			}
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
					deletePipe(Pipes);
					break;
				}

				case 2:
				{
					deleteKS(KSs);
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
			Pipes = filterPipe;
			break;
		}
		case 11:
		{
			KSs = filterKS;
			break;
		}
		case 12:
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
					for (int i = 0; i < KSs.size(); i++) {
						for (int j = 0; j < Pipes.size(); j++) {
							dataInsident[i][j] = 0;
						}
					}
					for (int i = 0; i < KSs.size(); i++) {
						for (int j = 0; j < KSs.size(); j++) {
							dataSmej[i][j] = 0;
						}
					}
					break;
				}
				case 2:
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
						break;
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
						break;
					}

					for (int j = 0; j < Pipes.size(); j++) {
						if (dataInsident[j][rebro] != 0) {
							cout << "Это ребро уже было использованно" << endl;
							break;
						}
					}

					dataSmej[idKS1][idKS2] = 1;
					dataInsident[idKS1][rebro] = 1;
					dataInsident[idKS2][rebro] = -1;

					break;
				}

				case 3:
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
						break;
					}
					dataSmej[idKS1][idKS2] = 0;
					dataSmej[idKS2][idKS1] = 0;
					for (int j = 0; j < Pipes.size(); j++)
					{
						if ((dataInsident[start][j] == 1 && dataInsident[finish][j] == -1)||(dataInsident[start][j] == -1 && dataInsident[finish][j] == 1))
						{
							dataInsident[start][j] = 0;
							dataInsident[finish][j] = 0;
							
						}
					}

					break;
				}

				case 4:
				{
					cout << "Матрица инцидентности" << endl;
					for (int i = 0; i < KSs.size(); i++) {
						for (int j = 0; j < Pipes.size(); j++) {
							cout << dataInsident[i][j] << "  ";
						}
						cout << endl;
					}
					cout << endl <<
						"Матрица смежности" << endl;

					for (int i = 0; i < KSs.size(); i++) {
						for (int j = 0; j < KSs.size(); j++) {
							cout << dataSmej[i][j] << "  ";
						}
						cout << endl;
					}
					cout << endl;

					break;
				}

				case 5:


				{

					int maxNum = 1;

					for (int i = 0; i < KSs.size(); i++) {
						int count = 0;
						int countminus = 0;
						for (int j = 0; j < Pipes.size(); j++) {
							if (dataInsident[i][j] == 1) {
								count++;

							}
							if (dataInsident[i][j] == -1) {
								countminus++;

							}


						}
						if (count != 0 && countminus == 0) {
							KSs[i].set_number_in_sort(maxNum);


						}
					}

					// Отбросить изолированные точки
					for (int i = 0; i < KSs.size(); i++) {
						int count = 0;
						int countminus = 0;
						for (int j = 0; j < Pipes.size(); j++) {
							if (dataInsident[i][j] == 1) {
								count++;

							}
							if (dataInsident[i][j] == -1) {
								countminus++;

							}


						}
						if (count == 0 && countminus == 0) {
							KSs[i].set_number_in_sort(0);


						}
					}



					int numOfMinusOdin = findNumSort(KSs);
					while (numOfMinusOdin > 0 && maxNum <= KSs.size()+1) {
						for (int i = 0; i < KSs.size(); i++) {
							if (KSs[i].get_number_in_sort() == maxNum) {
								for (int j = 0; j < KSs.size(); j++) {
									if (dataSmej[i][j] == 1) {
										KSs[j].set_number_in_sort(maxNum + 1);
										numOfMinusOdin--;
									}
								}
							}
						}
						if (maxNum == KSs.size() + 1)
						{
							cout << "Граф содержит цикл" << endl;
						}
						maxNum++;

					}

					for (int i = 1; i <= maxNum; i++) {
						for (int j = 0; j < KSs.size(); j++) {
							if (KSs[j].get_number_in_sort() == i) {
								cout << KSs[j].get_id() << "  ";
							}
						}
					}

					for (int j = 0; j < KSs.size(); j++) {
						KSs[j].set_number_in_sort(-1);
					}
					cout << endl;

					break;
				}

				case 6:
				{

					int maxNum = 1;

					int Insident[maxKS][maxPipe];
					int Smej[maxKS][maxKS];
					for (int i = 0; i < maxKS; i++) {
						for (int j = 0; j < maxPipe; j++) {
							Insident[i][j] = dataInsident[i][j];
						}
					}
					for (int i = 0; i < maxKS; i++) {
						for (int j = 0; j < maxKS; j++) {
							Smej[i][j] = 0;
						}
					}

					for (int i = 0; i < KSs.size(); i++) {
						if (KSs[i].get_number_shop_working() == 0) {
							for (int j = 0; j < Pipes.size(); j++) {											//Если numshopworking == 0
								if (Insident[i][j] != 0) {
									for (int m = 0; m < KSs.size(); m++) {
										Insident[m][j] = 0;
									}
								}

							}
						}
					}


					for (int i = 0; i < Pipes.size(); i++) {
						if (Pipes[i].get_repear()) {
							for (int j = 0; j < KSs.size(); j++) {

								Insident[j][i] = 0;

							}
						}
					}

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
						break;
					}

					int max_provod = -1;
					int provod = -1;




					for (int i = 0; i < KSs.size(); i++) {
						int count = 0;
						int count_minus = 0;
						for (int j = 0; j < Pipes.size(); j++) {
							if (dataInsident[i][j] == 1) {
								count++;

							}
							if (dataInsident[i][j] == -1) {
								count_minus++;

							}


						}
						if (count != 0 && count_minus == 0) {
							KSs[i].set_number_in_sort(maxNum);


						}
					}

					// Отбросить изолированные точки
					for (int i = 0; i < KSs.size(); i++) {
						int count = 0;
						int count_minus = 0;
						for (int j = 0; j < Pipes.size(); j++) {
							if (dataInsident[i][j] == 1) {
								count++;

							}
							if (dataInsident[i][j] == -1) {
								count_minus++;

							}


						}
						if (count == 0 && count_minus == 0) {
							KSs[i].set_number_in_sort(0);


						}
					}



					int numOfMinusOdin = findNumSort(KSs);
					while (numOfMinusOdin > 0 && maxNum < KSs.size()) {
						for (int i = 0; i < KSs.size(); i++) {
							if (KSs[i].get_number_in_sort() == maxNum) {
								for (int j = 0; j < KSs.size(); j++) {
									if (dataSmej[i][j] == 1) {
										KSs[j].set_number_in_sort(maxNum + 1);
										numOfMinusOdin--;
									}
								}
							}
						}
						maxNum++;

					}

					bool check = true;

					int smej[maxKS][maxKS];

					for (int i = 0; i < maxKS; i++) {
						for (int j = 0; j < maxKS; j++) {
							smej[i][j] = dataSmej[i][j];
						}
					}

					if (KSs[start].get_number_in_sort() > KSs[finish].get_number_in_sort()) {
						cout << "Путь не найден" << endl;
						break;
					}
					KSs[start].set_min_dist(0);
					//for (int i = KSs[start].numberInSort; i < KSs[finish].numberInSort; i++) {
					for (int j = 0; j < KSs.size(); j++) {
						if (smej[start][j] == 1) {
							int pipe;
							for (int r = 0; r < Pipes.size(); r++) {
								if (dataInsident[start][r] == 1 && dataInsident[j][r] == -1) {
									pipe = r;
								}
							}

							KSs[j].set_min_dist(Pipes[pipe].get_diametr());

						}

					}
					//}


					for (int m = KSs[start].get_number_in_sort() + 1; m < KSs[finish].get_number_in_sort(); m++) {

						for (int i = 0; i < KSs.size(); i++)
							if (KSs[i].get_number_in_sort() == m && KSs[i].get_min_dist() != -1) {

								for (int j = 0; j < KSs.size(); j++) {
									if (smej[i][j] == 1) {
										int pipe;
										for (int r = 0; r < Pipes.size(); r++) {
											if (dataInsident[i][r] == 1 && dataInsident[j][r] == -1) {
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

					for (int i = 0; i < KSs.size(); i++) {
						KSs[i].set_min_dist(-1);
						KSs[i].set_number_in_sort(-1);
					}

					break;
				}

				case 7:
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
						break;
					}

					int minRast = -1;
					int Rast = -1;




					int maxNum = 1;

					for (int i = 0; i < KSs.size(); i++) {
						int count = 0;
						int countminus = 0;
						for (int j = 0; j < Pipes.size(); j++) {
							if (dataInsident[i][j] == 1) {
								count++;

							}
							if (dataInsident[i][j] == -1) {
								countminus++;

							}


						}
						if (count != 0 && countminus == 0) {
							KSs[i].set_number_in_sort(maxNum);


						}
					}

					// Отбросить изолированные точки
					for (int i = 0; i < KSs.size(); i++) {
						int count = 0;
						int countminus = 0;
						for (int j = 0; j < Pipes.size(); j++) {
							if (dataInsident[i][j] == 1) {
								count++;

							}
							if (dataInsident[i][j] == -1) {
								countminus++;

							}


						}
						if (count == 0 && countminus == 0) {
							KSs[i].set_number_in_sort(0);


						}
					}



					int numOfMinusOdin = findNumSort(KSs);
					while (numOfMinusOdin > 0 && maxNum <KSs.size()) {
						for (int i = 0; i < KSs.size(); i++) {
							if (KSs[i].get_number_in_sort() == maxNum) {
								for (int j = 0; j < KSs.size(); j++) {
									if (dataSmej[i][j] == 1) {
										KSs[j].set_number_in_sort(maxNum + 1);
										numOfMinusOdin--;
									}
								}
							}
						}
						maxNum++;

					}

					bool check = true;

					int smej[maxKS][maxKS];

					for (int i = 0; i < maxKS; i++) {
						for (int j = 0; j < maxKS; j++) {
							smej[i][j] = dataSmej[i][j];
						}
					}

					if (KSs[start].get_number_in_sort() > KSs[finish].get_number_in_sort()) {
						cout << "Путь не найден" << endl;
						break;
					}
					KSs[start].set_min_dist(0);
					//for (int i = KSs[start].numberInSort; i < KSs[finish].numberInSort; i++) {
					for (int j = 0; j < KSs.size(); j++) {
						if (smej[start][j] == 1) {
							int pipe;
							for (int r = 0; r < Pipes.size(); r++) {
								if (dataInsident[start][r] == 1 && dataInsident[j][r] == -1) {
									pipe = r;
								}
							}

							KSs[j].set_min_dist(Pipes[pipe].get_lenght());

						}

					}
					//}


					for (int m = KSs[start].get_number_in_sort() + 1; m < KSs[finish].get_number_in_sort(); m++) {

						for (int i = 0; i < KSs.size(); i++)
							if (KSs[i].get_number_in_sort() == m && KSs[i].get_min_dist() != -1) {

								for (int j = 0; j < KSs.size(); j++) {
									if (smej[i][j] == 1) {
										int pipe;
										for (int r = 0; r < Pipes.size(); r++) {
											if (dataInsident[i][r] == 1 && dataInsident[j][r] == -1) {
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

					for (int i = 0; i < KSs.size(); i++) {
						KSs[i].set_min_dist(-1);
						KSs[i].set_number_in_sort(-1);
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
