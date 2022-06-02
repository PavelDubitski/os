// Parent.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include <conio.h>
using namespace std;

int main(int argc, char *argv[])
{

    HANDLE A_mes = OpenEvent(EVENT_ALL_ACCESS,FALSE, "A1");
    HANDLE B_mes = OpenEvent(EVENT_ALL_ACCESS,FALSE, "B1");
    HANDLE C_mes = OpenEvent(EVENT_ALL_ACCESS,FALSE, "C1");
    HANDLE D_mes = OpenEvent(EVENT_ALL_ACCESS,FALSE, "D1");
    HANDLE E_mes = OpenEvent(EVENT_ALL_ACCESS,FALSE, "E1");
    HANDLE sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS,TRUE, "semaphore");
    if (sem == NULL) {
        GetLastError();
    }
    bool b;




    if (WaitForSingleObject(A_mes, 0) == WAIT_OBJECT_0) {
        cout << "MES: A" << endl;
        ResetEvent(A_mes);
    }
    if (WaitForSingleObject(C_mes, 0) == WAIT_OBJECT_0) {
        cout << "MES: C" << endl;
        ResetEvent(C_mes);
    }
    if (WaitForSingleObject(B_mes, 0) == WAIT_OBJECT_0) {
        cout << "MES: B" << endl;
        ResetEvent(B_mes);
    }
    if (WaitForSingleObject(D_mes, 0) == WAIT_OBJECT_0) {
        cout << "MES: D" << endl;
        ResetEvent(D_mes);
    }



    _getch();
    ReleaseSemaphore(sem, 1, NULL);




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
