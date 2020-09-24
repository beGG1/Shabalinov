
// Shabalinov1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <Windows.h> // Нужно для распознания кирилицы 


using namespace std;

    // Структура трубы
struct Pipe
{
    size_t id;
    int lenght;
    int diametr;
    bool repear;
};

    // Создание трубы
Pipe createPipe() {
    Pipe P;

    // Ввод и проверка положительности длинны
    do {
        cout << "Введите длину: ";
        cin >> P.lenght;
        if (P.lenght <= 0) {
            cout << "Ошибка. Ведите положительное число" << endl;
        }
    } while (P.lenght <= 0);
    
    // Ввод и проверка положительности диаметра
    do {
        cout << "Введите диаметр: ";
        cin >> P.diametr;
        if (P.diametr <= 0) {
            cout << "Ошибка. Ведите положительное число" << endl;
        }
    } while (P.diametr <= 0);

        P.repear = false;
    return P;
}

    // Изменение состояния ремонта
void editPipe(Pipe P) {
    if (P.repear) {
        P.repear = false;
    }
    else {
        P.repear = true;
    }
 }


    // Вывод данных о трубе в консоль
void printPipe(Pipe P)
{
    cout << "id: " << P.id << endl << "Длина: " << P.lenght << endl << "Диаметр: " << P.diametr << endl;
    if (P.repear) {
        cout << "Состояние ремонта: В ремонте" << endl;
    }
    else {
        cout << "Состояние ремонта: Не в Ремонте" << endl << endl;
    }

}

    //Сохранение в файл
void savePipe(const Pipe& P) {
    ofstream fout;
    fout.open("Pipe.txt", ios::out);
    if (fout.is_open())
    {
        fout << P.id << endl << P.lenght << endl << P.diametr << endl << P.repear;
        fout.close();
    }
}

    //Загрузка из файла
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
    // Распознание кириллицы в консоли  (https://ru.stackoverflow.com/questions/117144/Русские-символы-при-вводе-и-выводе-на-c)
    SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
    SetConsoleOutputCP(1251); // Вывод на консоль в кодировке 1251. Нужно только будет изменить шрифт консоли на Lucida Console или Consolas

    Pipe P1 = createPipe();
    printPipe(P1);
    editPipe(P1);
    printPipe(P1);
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
