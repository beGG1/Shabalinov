
// Shabalinov1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <Windows.h> // Нужно для распознания кирилицы 
#include <vector>


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
    int effective;
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
        << "0. Выход" << endl << endl;
}

    // Создание трубы
Pipe createPipe(int maxId) {
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
KS createKS( int maxId) {
    KS KS1;
    KS1.id = maxId;
        cout << "Введите название КС: ";
        cin >> KS1.name ;
    do {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Количество цехов: ";
        cin >> KS1.numShop;
    } while (cin.fail() || KS1.numShop <= 0);
    do {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Количество цехов в работе: ";
        cin >> KS1.numShopWorking;
    } while (cin.fail() || KS1.numShopWorking <= 0 || KS1.numShopWorking > KS1.numShop);

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
    int i;
    do {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите id трубы ";
        cin >> i;
    } while (cin.fail() || i < 0);
    if (P[i].repear) {
        P[i].repear = false;
    }
    else {
        P[i].repear = true;
    }
 }

    // Ввод и вывот цехов в работу КС
void editKS(vector <KS> &KS1) {
    int i;
    do {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите id КС ";
        cin >> i;
    } while (cin.fail() || i < 0);

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
        } while (cin.fail() || k < 1 || k>2);
        switch (k)
        {
        case 1:
        {
            if (KS1[i].numShop == KS1[i].numShopWorking) {
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
                if (KS1[i].numShopWorking + shops <= KS1[i].numShop) {
                    KS1[i].numShopWorking += shops;
                    break;
                }
                else {
                    cout << "Можно добавть максимум " << - KS1[i].numShopWorking + KS1[i].numShop
                        << " цехов" << endl;
                    break;
                }
            }
        }

        case 2:
        {
            if (KS1[i].numShop == 1) {
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
                if (KS1[i].numShopWorking - shops >= 1) {
                    KS1[i].numShopWorking -= shops;
                    break;
                }
                else {
                    cout << "Можно убрать максимум " << KS1[i].numShopWorking 
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

    //Сохранение в файл
void savePipe(const vector<Pipe>& Pipes) {
    ofstream fout;
    fout.open("Pipe.txt", ios::out);
    if (fout.is_open())
    {
        for (int i = 0; i < Pipes.size(); i++) {
            fout << Pipes[i].id << endl << Pipes[i].lenght << endl << Pipes[i].diametr << endl << Pipes[i].repear << endl;
        }
        fout.close();
    }
}

    //Загрузка из файла
vector<Pipe> loadPipe(const int &Size) {
    ifstream fin;
    fin.open("Pipe.txt", ios::in);
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

//Сохранение в файл
void saveKS(const vector<KS>& KS1) {
    ofstream fout;
    fout.open("KS.txt", ios::out);
    if (fout.is_open())
    {
        for (int i = 0; i < KS1.size(); i++) {
            fout << KS1[i].id << endl << KS1[i].name << endl << KS1[i].numShop << endl << KS1[i].numShopWorking << endl << KS1[i].effective << endl;
        }
        fout.close();
    }
}

//Загрузка из файла
vector <KS> loadKS(const int& Size) {
    ifstream fin;
    fin.open("KS.txt", ios::in);
    KS KS1;
    vector <KS> KSs1;
    if (fin.is_open()) {
        for (int i = 0; i < Size; i++) {
        fin >> KS1.id;
        fin >> KS1.name;
        fin >> KS1.numShop;
        fin >> KS1.numShopWorking;
        fin >> KS1.effective;
        KSs1.push_back(KS1);
        }
        fin.close();
        return KSs1;
    }
}
// Max id  Pipe
void saveMaxPipeId(const int & maxIdPipe) {
    ofstream fout;
    fout.open("MaxPipeId.txt", ios::out);
    if (fout.is_open())
    {
        fout << maxIdPipe;
        }
        fout.close();

}

int loadMaxPipeID() {
    ifstream fin;
    fin.open("MaxPipeId.txt", ios::in);
    int i;
    if (fin.is_open()) {
        fin >> i;
        fin.close();
        return i;
    }
}

// Max id  KS
void saveMaxKSId(const int& maxIdKS) {
    ofstream fout;
    fout.open("MaxKSId.txt", ios::out);
    if (fout.is_open())
    {
        fout << maxIdKS;
    }
    fout.close();

}

int loadMaxKSID() {
    ifstream fin;
    fin.open("MaxKSId.txt", ios::in);
    int i;
    if (fin.is_open()) {
        fin >> i;
        fin.close();
        return i;
    }
}

int main()
{
    // Распознание кириллицы в консоли  (https://ru.stackoverflow.com/questions/117144/Русские-символы-при-вводе-и-выводе-на-c)
    SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
    SetConsoleOutputCP(1251); // Вывод на консоль в кодировке 1251. Нужно только будет изменить шрифт консоли на Lucida Console или Consolas

    vector <Pipe> Pipes;
    vector <KS> KSs;

    while (true) {
        int maxIdPipe = Pipes.size();
        int maxIdKS = KSs.size();
        int i;
        printMenu();
        cin >> i;
        switch (i){
        case 1:
        {
           Pipe P;
           P = createPipe(maxIdPipe);
           Pipes.push_back(P);
           break;
        }
        case 2:
        {
            KS KS1;
            KS1 = createKS(maxIdKS);
            KSs.push_back(KS1);
            break;
        }
        case 3:
        {
            for (int i = 0; i < Pipes.size(); i++) {
                printPipe(Pipes[i]);
            }
            for (int i = 0; i < KSs.size(); i++) {
                printKS(KSs[i]);
            }
           break;
        }
        case 4:
        {
            editPipe(Pipes);
            break;
        }
        case 5:
        {
            editKS(KSs);
            break;
        }
        case 6:
        {
            saveMaxPipeId(maxIdPipe);
            savePipe(Pipes);
            saveMaxKSId(maxIdKS);
            saveKS(KSs);
            break;
        }
        case 7:
        {
            maxIdPipe = loadMaxPipeID();
            Pipes = loadPipe(maxIdPipe);
            maxIdKS = loadMaxKSID();
            KSs = loadKS(maxIdKS);
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
