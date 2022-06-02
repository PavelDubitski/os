// Пример процесса, который создает новое консольное приложение с новой консолью
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
using namespace std;
volatile UINT count1;

int main()
{
    cout<<"Enter size"<<endl;
    int size;
    cin>>size;
    cout<<"Enter elements:";
    int a;
    string b ="C:\\Users\\bboyp\\CLionProjects\\untitled4\\cmake-build-debug\\untitled4.exe ";
    for(int i = 0; i<size; i++){
        cin>>a;
        b+=(to_string(a));
        b+=" ";
    }
    cout<<b;
    char lpszCommandLine[255];
    strcpy(lpszCommandLine,b.c_str());
    STARTUPINFO si;
    PROCESS_INFORMATION piCom;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
// создаем новый консольный процесс
    CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE,
                  CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCom);
// закрываем дескрипторы этого процесса
// WaitForSingleObject(piCom.hProcess,INFINITE);
    string c;
    for ( ; ; )
    {
        cout << "Input 'y' to display the count or 'e' to exit or 't' to terminate process: ";
        cin >> c;
        if (c[0] == 'y')
            cout << "count = " << count1 << endl;
        if (c[0] == 'e')
            ExitProcess(1);
        if(c[0] == 't'){
            TerminateProcess(piCom.hProcess,1);
        }
    }

    CloseHandle(piCom.hThread);
    CloseHandle(piCom.hProcess);
    _cputs("The new process is created.\n");
    _cputs("Press any key to finish.\n");
    _getch();
    return 0;
}