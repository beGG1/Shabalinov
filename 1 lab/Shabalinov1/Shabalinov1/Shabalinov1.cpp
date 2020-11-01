
// Shabalinov1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <Windows.h> // Нужно для распознания кирилицы 
#include <vector>
#include <string>


using namespace std;

	// Структура трубы
struct Pipe
{
	size_t id;
	int lenght;
	int diametr;
	bool repear;
};

	// Структура КС
struct KS {
	size_t id;
	string name;
	int numShop;
	int numShopWorking;
	double effective;
};


	// Напечатать меню 1. Добавить трубу 2. Добавить КС 3. Просмотр всех объектов 4. Редактировать трубу 5. Редактировать КС 6. Сохранить 7. Загрузить 0. Выход
void printMenu() {
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
		<< "0. Выход" << endl << endl;
}

	// Создание трубы
Pipe createPipe(const int& maxId) {
	Pipe P;
	P.id = maxId;
	// Ввод и проверка положительности длинны
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите длину: ";
		cin >> P.lenght;
	} while (cin.fail() || P.lenght <= 0);
	
	// Ввод и проверка положительности диаметра
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите диаметр: ";
		cin >> P.diametr;

	} while (cin.fail() || P.diametr <= 0);

		P.repear = false;
	return P;
}

	// Создание КС
KS createKS(const int& maxId) {
	KS KS1;
	KS1.id = maxId;
	cout << "Введите название КС: ";
	cin.ignore();
	getline(cin, KS1.name);

		

	do {
		int i = 0;
		if (i == 0) {
			i++;
			cout << "Количество цехов: ";
			cin >> KS1.numShop;
		}
		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Количество цехов: ";
			cin >> KS1.numShop;
		}
	} while (cin.fail() || KS1.numShop <= 0);
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Количество цехов в работе: ";
		cin >> KS1.numShopWorking;
	} while (cin.fail() || KS1.numShopWorking <= 0 || KS1.numShopWorking > KS1.numShop);

	KS1.effective =  double(KS1.numShopWorking) / double(KS1.numShop) * 100;
	return KS1;
}

	// Вывод КС
void printKS(const KS &KS1) {
	cout << "id: " << KS1.id << endl
		<< "Навание КС: " << KS1.name << endl
		<< "Количество цехов: " << KS1.numShop << endl
		<< "Количество цехов в работе: " << KS1.numShopWorking << endl
		<< "Эффективность: " << KS1.effective << endl << endl;
}

	// Изменение состояния ремонта
void editPipe(vector <Pipe> &P) {
	double i;
	int m;
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите id трубы ";
		cin >> i;
		m = (int)i;
	} while (cin.fail() || m < 0);

	for (int key = 0; key < P.size(); key++) {
		if (P[key].id == m) {
			if (P[key].repear) {
				P[key].repear = false;
			}
			else {
				P[key].repear = true;
			}
		}
		else
		{
			cout << "id не найден" << endl;
		}
	 
	}
 }

	// Ввод и вывот цехов в работу КС
void editKS(vector <KS> &KS1) {
	double i;
	int key;
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите id КС ";
		cin >> i;
		key = (int)i;
	} while (cin.fail() || key < 0);

	for (int m = 0; m < KS1.size(); m++) {
		if (KS1[m].id == key) {
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
					if (KS1[m].numShop == KS1[m].numShopWorking) {
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
						if (KS1[m].numShopWorking + shops <= KS1[m].numShop) {
							KS1[m].numShopWorking += shops;
							KS1[m].effective = double(KS1[m].numShopWorking) / double(KS1[m].numShop) * 100;
							break;
						}
						else {
							cout << "Можно добавть максимум " << -KS1[m].numShopWorking + KS1[m].numShop
								<< " цехов" << endl;
							break;
						}
					}
				}

				case 2:
				{
					if (KS1[m].numShop == 0) {
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
						if (KS1[m].numShopWorking - shops >= 0) {
							KS1[m].numShopWorking -= shops;
							KS1[m].effective = double (KS1[m].numShopWorking) /  double(KS1[m].numShop) * 100;
							break;
						}
						else {
							cout << "Можно убрать максимум " << KS1[m].numShopWorking
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
		else
		{
			cout << "id не найден" << endl;
		}
	}
}


	// Вывод данных о трубе в консоль
void printPipe(const Pipe &P)
{
	cout << "id: " << P.id << endl << "Длина: " << P.lenght << endl << "Диаметр: " << P.diametr << endl;
	if (P.repear) {
		cout << "Состояние ремонта: В ремонте" << endl << endl;
	}
	else {
		cout << "Состояние ремонта: Не в Ремонте" << endl << endl;
	}

}

	//Сохранение в файл Труба
void savePipe(const vector<Pipe>& Pipes , const string & fileName) {
	ofstream fout;
	fout.open(fileName +"Pipes"+ ".txt", ios::out);
	if (fout.is_open())
	{
		for (int i = 0; i < Pipes.size(); i++) {
			fout << Pipes[i].id << endl << Pipes[i].lenght << endl << Pipes[i].diametr << endl << Pipes[i].repear << endl;
		}
		fout.close();
	}
}

	//Загрузка из файла Труба
vector<Pipe> loadPipe(const int &Size, const string& fileName) {
	ifstream fin;
	fin.open(fileName + "Pipes" + ".txt", ios::in);
	Pipe P;
	vector<Pipe> Pipes;
	if (fin.is_open()) {
		for (int i = 0; i < Size; i++) {
			fin >> P.id;
			fin >> P.lenght;
			fin >> P.diametr;
			fin >> P.repear;
			Pipes.push_back(P);
		}
		fin.close();
		return Pipes;
	}
}

//Сохранение в файл КС
void saveKS(const vector<KS>& KS1, const string & fileName) {
	ofstream fout;
	fout.open(fileName +"KS"+ ".txt", ios::out);
	if (fout.is_open())
	{
		for (int i = 0; i < KS1.size(); i++) {
			fout << KS1[i].id << endl << KS1[i].name << endl << KS1[i].numShop << endl << KS1[i].numShopWorking << endl << KS1[i].effective << endl;
		}
		fout.close();
	}
}

//Загрузка из файла КС
vector <KS> loadKS(const int& Size, const string& fileName) {
	//ifstream fin;
	//fin.open("KS.txt", ios::in);
	ifstream myfile(fileName + "KS" + ".txt");
	KS KS1;
	string str;
	vector <KS> KSs1;
	//if (fin.is_open()) {
		for (int i = 0; i < Size; i++) {
			getline(myfile,str);
			KS1.id = atoi(str.c_str());
			getline(myfile, KS1.name);
			getline(myfile, str);
			KS1.numShop = atoi(str.c_str());
			getline(myfile, str);
			KS1.numShopWorking = atoi(str.c_str());
			getline(myfile, str);
			KS1.effective = atoi(str.c_str());
			KSs1.push_back(KS1);
		}
		//fin.close();
		return KSs1;
	//}
}



// Max id  Pipe 
void saveMaxPipeId(const int & maxIdPipe, const string& fileName) {
	ofstream fout;
	fout.open(fileName + "IDPipe"+".txt", ios::out);
	if (fout.is_open())
	{
		fout << maxIdPipe;
		}
		fout.close();

}

int loadMaxPipeID(const string& fileName) {
	ifstream fin;
	fin.open(fileName + "IDPipe" + ".txt", ios::in);
	int i;
	if (fin.is_open()) {
		fin >> i;
		fin.close();
		return i;
	}
}

// Max id  KS
void saveMaxKSId(const int& maxIdKS, const string& fileName) {
	ofstream fout;
	fout.open(fileName + "IDKS" + ".txt", ios::out);
	if (fout.is_open())
	{
		fout << maxIdKS;
	}
	fout.close();

}

int loadMaxKSID(const string& fileName) {
	ifstream fin;
	fin.open(fileName + "IDKS" + ".txt", ios::in);
	int i;
	if (fin.is_open()) {
		fin >> i;
		fin.close();
		return i;
	}
}


//Удалить Трубу
void deletePipe(vector <Pipe>& P) {
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
		for (int m=0; m <P.size(); m++) {
			if (P[m].id == idPipe) {
				index = m;
				break;
			}
		}
		
		if (index == -1) {
			cout << "Ошибка. Трубы с таким id не существует" << endl;
			break;
		}
		
		P.erase(P.begin() + index); //https://coderoad.ru/875103/Как-удалить-элемент-из-std-vector-по-индексу
	}


}



//Удалить KS
void deleteKS(vector <KS>& K) {
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
			if (K[m].id == idKS) {
				index = m;
				break;
			}
		}

		if (index == -1) {
			cout << "Ошибка. Трубы с таким id не существует" << endl;
			break;
		}

		K.erase(K.begin() + index); //https://coderoad.ru/875103/Как-удалить-элемент-из-std-vector-по-индексу
	}


}


	//Фильтр по работающим трубам
vector <Pipe> pipeFilter(const vector <Pipe>& P) {
	vector <Pipe> Pipes;
	for (int i = 0; i < P.size(); i++) {
		if (P[i].repear) {
			Pipes.push_back(P[i]);
		}
	}
	return Pipes;

}


	// Фильтр по эффективности
vector <KS> ksFilterEffect(const vector <KS>& KS1, bool key , double number) {
	vector <KS> Bolshe;
	vector <KS> Menshe;

	for (int i = 0; i < KS1.size(); i++) {
		if (KS1[i].effective >= number) {
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
vector <KS> ksFilterName(const vector <KS>& KS1, string Name) {
	vector <KS> NameV;
	for (int i = 0; i < KS1.size(); i++) {
		if (KS1[i].name == Name) {
			NameV.push_back(KS1[i]);
		}
	}
	return NameV;
}



int main()
{
	// Распознание кириллицы в консоли  (https://ru.stackoverflow.com/questions/117144/Русские-символы-при-вводе-и-выводе-на-c)
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251); // Вывод на консоль в кодировке 1251. Нужно только будет изменить шрифт консоли на Lucida Console или Consolas

	vector <Pipe> Pipes;
	vector <KS> KSs;
	vector <Pipe> filterPipe;
	vector <KS> filterKSEffect;
	vector <KS> filterKSName;

	
	while (true) {

		// Определение максимальных id
		int maxIdPipe;
		if (Pipes.size() == 0) {
			maxIdPipe = 0;
		}
		else {
			maxIdPipe = Pipes[Pipes.size()-1].id + 1;
		}
		int maxIdKS;
		if (KSs.size() == 0) {
			maxIdKS = 0;
		}
		else {
			maxIdKS = KSs[KSs.size() -1].id + 1;
		}


		printMenu();
		int i;
		cin >> i;

		while (cin.fail() || i < 0) {
			cin.clear();
			cin.ignore(10000, '\n');
			printMenu();
			cin >> i;
		};
		
		switch (i){
		case 1:														// Создать Трубу
		{
		   Pipe P;
		   P = createPipe(maxIdPipe);
		   Pipes.push_back(P);
		   break;
		}
		case 2:														// Создать кс
		{
			KS KS1;
			KS1 = createKS(maxIdKS);
			KSs.push_back(KS1);
			break;
		}
		case 3:														// Вывести все на экран
		{
			for (int i = 0; i < Pipes.size(); i++) {
				printPipe(Pipes[i]);
			}
			for (int i = 0; i < KSs.size(); i++) {
				printKS(KSs[i]);
			}
		   break;
		}
		case 4:														// Изменить состояние ремонта трубы
		{
			editPipe(Pipes);
			break;
		}
		case 5:														//  Ввод и вывод в работу цехов КС
		{
			editKS(KSs);
			break;
		}
		case 6:														// Сохранить
		{
			cout << "Введите название файла: ";
			string fileName;
			cin.ignore();
			getline(cin, fileName);
			saveMaxPipeId(maxIdPipe, fileName);
			savePipe(Pipes, fileName);
			saveMaxKSId(maxIdKS, fileName);
			saveKS(KSs, fileName);
			break;
		}
		case 7:														// Загрузить из файла
		{
			cout << "Введите название файла: ";
			string fileName;
			cin.ignore();
			getline(cin, fileName);
			maxIdPipe = loadMaxPipeID(fileName);
			Pipes = loadPipe(maxIdPipe , fileName);
			maxIdKS = loadMaxKSID(fileName);
			KSs = loadKS(maxIdKS , fileName);
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
				cout << "1. Фильтр труба" << endl
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
				filterPipe = pipeFilter(Pipes);
				for (int i = 0; i < filterPipe.size(); i++) {
					printPipe(filterPipe[i]);
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
					filterKSName = ksFilterName(KSs, name);
					if (filterKSName.size() == 0) {
						cout << "Результатов не найдено" << endl;
					}
					else {
						for (int i = 0; i < filterKSName.size(); i++) {
							printKS(filterKSName[i]);
						}
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
						filterKSEffect = ksFilterEffect(KSs, true, number);
						for (int i = 0; i < filterKSEffect.size(); i++) {
							printKS(filterKSEffect[i]);
						}
						break;
					}				
					case 2:
					{
						filterKSEffect = ksFilterEffect(KSs, false, number);
						for (int i = 0; i < filterKSEffect.size(); i++) {
							printKS(filterKSEffect[i]);
						}
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
		case 0:
		{
			return 0;
		}
		default :
		{
			cout << "Ошибка" << endl;
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
