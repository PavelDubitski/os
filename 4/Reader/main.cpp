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
    WaitForSingleObject(sem, INFINITE);
//cout<<"HELLO";

cout<<"recived 'C' and 'D'";
//    if (WaitForSingleObject(A_mes, 0) == WAIT_OBJECT_0) {
//        cout << "MES: A" << endl;
//        ResetEvent(A_mes);
//    }
//    if (WaitForSingleObject(C_mes, 0) == WAIT_OBJECT_0) {
//        cout << "MES: C" << endl;
//        ResetEvent(C_mes);
//    }
//    if (WaitForSingleObject(B_mes, 0) == WAIT_OBJECT_0) {
//        cout << "MES: B" << endl;
//        ResetEvent(B_mes);
//    }
//    if (WaitForSingleObject(D_mes, 0) == WAIT_OBJECT_0) {
//        cout << "MES: D" << endl;
//        ResetEvent(D_mes);
//    }



    _getch();
    //ReleaseSemaphore(sem, 1, NULL);




}

