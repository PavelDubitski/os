
#include <iostream>
#include<Windows.h>
#include <string>
using namespace std;

int main()
{
    int n,m;
    cout << "Input number of  processes\n";
    cin >> n;
    //cout << "Input number of mes\n";
   // cin >> m;
    m=2;
    HANDLE sem = CreateSemaphore(NULL, 0, 2, "semaphore");
    HANDLE hFirst[2];
    HANDLE hSecond[2];
    hFirst[0]=CreateEvent(NULL,FALSE, FALSE,"A");
    hFirst[1]=CreateEvent(NULL,FALSE, FALSE,"B");
    hFirst[0]=CreateEvent(NULL,FALSE, FALSE,"C");
    hFirst[1]=CreateEvent(NULL,FALSE, FALSE,"D");
    //HANDLE A_mes = CreateEvent(NULL,FALSE, FALSE,"A");
    //HANDLE B_mes = CreateEvent(NULL,FALSE, FALSE,"B");
   // HANDLE C_mes = CreateEvent(NULL,FALSE, FALSE,"C");
    //HANDLE D_mes = CreateEvent(NULL,FALSE, FALSE,"D");
    HANDLE E_mes = CreateEvent(NULL,FALSE, FALSE,"E");
    HANDLE A1_mes = CreateEvent(NULL,FALSE, FALSE,"A1");
    HANDLE B1_mes = CreateEvent(NULL,FALSE, FALSE,"B1");
    HANDLE C1_mes = CreateEvent(NULL,FALSE, FALSE,"C1");
    HANDLE D1_mes = CreateEvent(NULL,FALSE, FALSE,"D1");
    HANDLE E1_mes = CreateEvent(NULL,FALSE, FALSE,"E1");
    //HANDLE* proc = new HANDLE[n+m];
    HANDLE W_events[5];
    HANDLE R_events[5];
    HANDLE mut;
    mut = CreateMutex(NULL, FALSE, "mutex");
    if (mut == NULL) {
        GetLastError();
    }
    //DWORD* id = new DWORD[n+m];
    STARTUPINFO* st = new STARTUPINFO[n + n];
    PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[n + n];


    string b ="C:\\proga\\algos\\Writer\\cmake-build-debug\\Writer.exe ";
    b+=(to_string(m));
    string bb ="C:\\proga\\algos\\Reader\\cmake-build-debug\\Reader.exe ";
    bb+=(to_string(m));
    char lpszCommandLine[255];
    char lpszCommandLine2[255];
    strcpy(lpszCommandLine,b.c_str());
    strcpy(lpszCommandLine2,bb.c_str());
    for (int i = 0;i < n;i++) {
        ZeroMemory(&st[i], sizeof(STARTUPINFO));
        st[i].cb = sizeof(STARTUPINFO);
        CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE,
                      CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);
        ZeroMemory(&st[i+n], sizeof(STARTUPINFO));
        st[i+n].cb = sizeof(STARTUPINFO);
        CreateProcess(NULL, lpszCommandLine2, NULL, NULL, FALSE,
                      CREATE_NEW_CONSOLE, NULL, NULL, &st[i+n], &pi[i+n]);
    }
    bool a1=false;
    bool b1=false;
    bool c1=FALSE;
    bool d1=FALSE;

    for(int i = 0; i<n;i++) {
        WaitForSingleObject(E_mes, INFINITE);
        cout<<"exit from writer"<<endl;
        WaitForMultipleObjects(2,hFirst,TRUE,0);
            cout<<"Recived 'A' and 'B'"<<endl;
            SetEvent(A1_mes);
            ReleaseSemaphore(sem, 2, NULL);
            //cout<<"otv:"<<endl;
       }
//        if (WaitForSingleObject(A_mes, 0) == WAIT_OBJECT_0) {
//            cout << "MES: A" << endl;
//           // ResetEvent(A_mes);
//           a1 = true;
//            SetEvent(A1_mes);
//        }
//        if (WaitForSingleObject(C_mes, 0) == WAIT_OBJECT_0) {
//            cout << "MES: C" << endl;
//         //   ResetEvent(C_mes);
//            SetEvent(C1_mes);
//        }
//        if (WaitForSingleObject(B_mes, 0) == WAIT_OBJECT_0) {
//            cout << "MES: B" << endl;
//         //   ResetEvent(B_mes);
//            SetEvent(B1_mes);
//        }
//        if (WaitForSingleObject(D_mes, 0) == WAIT_OBJECT_0) {
//            cout << "MES: D" << endl;
//          //  ResetEvent(D_mes);
//            SetEvent(D1_mes);
//        }

        //WaitForSingleObject(sem, INFINITE);
        cout<<endl;
    }




