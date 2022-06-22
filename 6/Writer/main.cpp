

#include <iostream>
#include<Windows.h>
#include <conio.h>
using namespace std;

int main(int argc, char *argv[])
{   int m = atoi(argv[1]);
    HANDLE mut = OpenMutex(SYNCHRONIZE, FALSE, "mutex");
    HANDLE A_mes = OpenEvent(EVENT_MODIFY_STATE,FALSE, "A");
    HANDLE B_mes = OpenEvent(EVENT_MODIFY_STATE,FALSE, "B");
    HANDLE C_mes = OpenEvent(EVENT_ALL_ACCESS,FALSE, "C");
    HANDLE D_mes = OpenEvent(EVENT_ALL_ACCESS,FALSE, "D");
    HANDLE E_mes = OpenEvent(EVENT_ALL_ACCESS,FALSE, "E");
    WaitForSingleObject(mut, INFINITE);
    cout << "Input A and B \n";
    char mes;
    for(int i = 0; i<m;i++){
        cin>>mes;

        if(mes=='A'){
            SetEvent(A_mes);
        }
        if(mes=='B'){
            SetEvent(B_mes);
        }
        if(mes=='C'){
            SetEvent(C_mes);
        }
        if(mes=='D'){
            SetEvent(D_mes);
        }}
    ReleaseMutex(mut);
    SetEvent(E_mes);
    _getch();
}
