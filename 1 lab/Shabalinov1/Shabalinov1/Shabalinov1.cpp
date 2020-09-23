
// Shabalinov1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

using namespace std;

struct Pipe
{
    int id;
    int lenght;
    int diametr;
    bool repear;
};

Pipe createPipe() {
    Pipe P;
    cout << "Input id ";
    cin >> P.id;
    cout << "Input lenght ";
    cin >> P.lenght;
    cout << "Input diametr ";
    cin >> P.diametr;
    P.repear = false;
    return P;
}

void editPipe(Pipe P) {
    if (P.repear == false) {
        P.repear = true;
    }
    else {
        P.repear = false;
    }
}

void printPipe(Pipe P)
{
    cout << "id " << P.id << "  " << "Lenght " << P.lenght << "  " << "Diametr " << P.diametr << "  " << "Repear " << P.repear << endl;

}

void savePipe(const Pipe& P) {
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        fout << P.id << endl << P.lenght << endl << P.diametr << endl << P.repear;
        fout.close();
    }
}
Pipe loadPipe() {
    ifstream fin;
    fin.open("data.txt", ios::in);
    Pipe P;
    fin >> P.id;
    fin >> P.lenght;
    fin >> P.diametr;
    fin >> P.repear;
    fin.close();
    return P;
}

int main()
{
    Pipe P1 = createPipe();
    printPipe(P1);
    editPipe(P1);
    printPipe(P1);
    editPipe(P1);
    printPipe(P1);
    savePipe(P1);
    return 0;

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
