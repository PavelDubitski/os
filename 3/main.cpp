
#include <windows.h>
#include <iostream>
#include <vector>
using namespace std;
volatile int n;
CRITICAL_SECTION cs;
HANDLE hOutEvent, hAddEvent;
vector<int> mas2;
vector<int>masn;
vector<int>mas3;
int res = 1;

struct mydata{
    vector<int> mas1;
    int size1;
};

DWORD WINAPI work(LPVOID p)
{
    int ti;
    auto* d = (mydata*) p;
    cout<<"input rest time: ";
    cin>>ti;
    for(int i = 0; i < d->mas1.size(); i++){
        if(d->mas1[i]%2==0){
            mas2.push_back(d->mas1[i]);
        }else{
            masn.push_back(d->mas1[i]);
        }
        Sleep(d->size1);
    }
    mas3.insert(mas3.end(), mas2.begin(),mas2.end());
    mas3.insert(mas3.end(), masn.begin(),masn.end());
    SetEvent(hOutEvent);
    return 0;
}

DWORD WINAPI MultElement(LPVOID p)
{   WaitForSingleObject(hAddEvent, INFINITE);

    EnterCriticalSection (&cs);

    auto* d2 = (mydata*) p;
//    for(int i = 0; i <d2->mas1.size();i++){
//        cout<<"nas"<<i<<"="<<d2->mas1[i]<<endl;
//    }
    //res = d2->mas1[0];
    for(int i = 0; i<d2->size1;i++){
    res=res * d2->mas1[i];}
    LeaveCriticalSection(&cs);
    cout<<"result: = "<<res<<endl;
    return 0;
}

int main()
{
    HANDLE hThread;
    DWORD IDThread;
    HANDLE hThread2;
    DWORD IDThread2;
    InitializeCriticalSection(&cs);
    int size = 0;
    cout<<"Input mas size:";
    cin>>size;
    vector<int> mas;
    int m;
    int k;
    cout<<"Input k:";
    cin>>k;
    for(int i=0; i<size; i++){
        cout<<"input mas["<<i<<"]: "<<endl;
        cin>>m;

        mas.push_back(m);
    }

    mydata * d = new mydata{mas,k};



    hOutEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (hOutEvent == NULL)
        return GetLastError();
    hAddEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (hAddEvent == NULL)
        return GetLastError();

    hThread = CreateThread(NULL, 0, work, d, CREATE_SUSPENDED, &IDThread);
    if (hThread == NULL)
        return GetLastError();
    ResumeThread(hThread);
    WaitForSingleObject(hOutEvent, INFINITE);
    mydata * d2 = new mydata{mas3,k};
    hThread2 = CreateThread(NULL, 0, MultElement, d2, CREATE_SUSPENDED, &IDThread2);
    if (hThread == NULL)
        return GetLastError();
    ResumeThread(hThread2);




    for(int i=0;i<mas3.size();i++){
        EnterCriticalSection(&cs);
        cout<<"mas["<<i<<"]: "<<mas3[i]<<endl;
        LeaveCriticalSection(&cs);
        if(i==k-1){
            SetEvent(hAddEvent);
            WaitForSingleObject(hThread2,INFINITE);
        }
    }


   // cout<<"Result: "<<res;
    WaitForSingleObject(hThread, INFINITE);
    DeleteCriticalSection(&cs);
    CloseHandle(hThread);
    CloseHandle(hOutEvent);
    CloseHandle(hAddEvent);
    return 0;
}
