

#include <iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

int main()
{

    HANDLE write, read, read1;
    int n;
    cout << "Enter array size \n";

    cin >> n;
    float* arr=new float[n];
    cout << "\nEnter array elements \n";
    for (size_t i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << '\n';
    for (size_t i = 0; i < n; i++)
    {

    }
    HANDLE event = CreateEvent(NULL, FALSE, FALSE, "1");
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL; // защита по умолчанию
    sa.bInheritHandle = TRUE;
    CreatePipe(&read, &write, &sa, 0);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    char a[255];
    wsprintf(a, "C:\\Users\\bboyp\\CLionProjects\\Search\\cmake-build-debug\\Search.exe %d %d %d", int(write), int(read),n);

    if (!CreateProcess(NULL, a, NULL, NULL, TRUE,
                       CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        GetLastError();
    }

    for (size_t i = 0; i < n; i++)
    {
        DWORD size;
        WriteFile(write, &arr[i], sizeof(arr[i]), &size, NULL);
    }
    SetEvent(event);
    HANDLE end = OpenEvent(SYNCHRONIZE, FALSE, "end");
    if (end == NULL) {
        GetLastError();
    }
    Sleep(500);
    WaitForSingleObject(end, INFINITE);
    float c[7];

    DWORD size;
    float* g = new float[7];

    ReadFile(read, &g[0], sizeof(g[0]), &size, NULL);

    for (int i = 0;i < g[0];i++) {
   ReadFile(read, &c[i], sizeof(c[i]), &size, NULL);
    }
    for (int i = 0;i < g[0];i++) {
        cout << c[i]<<endl;
    }

char q;
    while (true) {
    cout<<"press q to exit"<<endl;
    cin>>q;
    if(q=='q'){
        break;
    }
    }
    return 0;
}

