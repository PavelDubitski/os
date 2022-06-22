

#include <iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

int main()
{


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
//    HANDLE event = CreateEvent(NULL, FALSE, FALSE, "1");
    SECURITY_ATTRIBUTES sa;
    SECURITY_DESCRIPTOR sd;
    HANDLE hNamedPipe;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL; // защита по умолчанию
    sa.bInheritHandle = FALSE;
    InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
    sa.lpSecurityDescriptor = &sd;
    hNamedPipe = CreateNamedPipe("\\\\.\\pipe\\first_pipe", PIPE_ACCESS_DUPLEX, // читаем из канала и пишем в канал
                                 PIPE_TYPE_MESSAGE | PIPE_WAIT, // синхронная передача сообщений
                                 1, // максимальное количество экземпляров канала
                                 0, // размер выходного буфера по умолчанию
                                 0, // размер входного буфера по умолчанию
                                 INFINITE, // клиент ждет связь 500 мс
                                 &sa // доступ для всех пользователей
    );
    char z;
    if (hNamedPipe == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Creation of the named pipe failed." << std::endl
                  << "The last error code: " << GetLastError() << std::endl;
        cout << "Press any char to finish server: ";
        cin >> z;
        return 0;
    }
    ConnectNamedPipe(hNamedPipe, (LPOVERLAPPED)NULL);


    DWORD sz;

    WriteFile(hNamedPipe, &n, sizeof(n), &sz, (LPOVERLAPPED)NULL);
    for(int i = 0; i<n; i++) {
        WriteFile(hNamedPipe, &arr[i], n, &sz, (LPOVERLAPPED) NULL);
    }
    int m;
    ReadFile(hNamedPipe, &m, sizeof(m), &sz, (LPOVERLAPPED)NULL);
    float* res = new float[m];
    //cout<<"our size"<<m<<endl;
    for(int i = 0; i<m; i++) {
    ReadFile(hNamedPipe, &res[i], m, &sz, (LPOVERLAPPED)NULL);
    }
    cout << '\n';
    for (int i = 0; i < m; i++)
    {
        cout << res[i]<<endl;
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

