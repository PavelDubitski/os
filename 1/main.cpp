// 13
#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;

volatile DWORD dwCount;
vector<int> result;

struct mydata{
    vector<int> mas1;
    int size1;
};

void * Count(){
    int a=1;
    int b=0;
    int t;
    cout<<"fibonachi: ";
    while(true){
        cout<<a<<endl;
        t = a;
        a+=b;
        b = t;

        Sleep(1000);
    }

}

void worker(void* p)
{
  auto* d = (mydata*) p;

  for(int i=0;i<d->size1;i++){

      if(d->mas1[d->size1]%d->mas1[i]==0){
         result.push_back(d->mas1[i]);
      }
      Sleep(13);
  }


}

int main()
{   int size = 0;
    int time = 13;

    cout<<"sleep time = "<<time<<endl;
    cout<<"Input size:";
    cin>>size;
    int m;
    vector<int> mas;
    for(int i=0; i<size; i++){
        cout<<"input mas["<<i<<"]: ";
        cin>>m;

        mas.push_back(m);
    }
    int x;
    cout<<"x=";
    cin>>x;
    mas.push_back(x);
    HANDLE hThread;
    HANDLE hThread2;
    DWORD IDThread;

    mydata * d = new mydata{mas,size};
    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) worker, (void*)d, 0, &IDThread);
    if (hThread == NULL)
        return GetLastError();

    dwCount = SuspendThread(hThread);
    cout<<"Thread Suspended dwCount = "<<dwCount<<endl;
    Sleep(50);
    dwCount = ResumeThread(hThread);
    cout<<"Thread Resumed dwCount = "<<dwCount<<endl;

// прерываем выполнение потока worker

   if(WaitForSingleObject(hThread, INFINITE) == WAIT_OBJECT_0){
    TerminateThread(hThread, 0);
// закрываем дескриптор потока
    CloseHandle(hThread);}
    cout<<"Deliteli: "<<endl;
for(int i = 0; i < result.size(); i++){
cout <<i+1 << ") " << result[i] << endl;}


    hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) Count(), 0, CREATE_SUSPENDED, &IDThread);
    if (hThread2 == NULL)
        return GetLastError();
    ResumeThread(hThread2);
    if(WaitForSingleObject(hThread2, 111) != WAIT_OBJECT_0){
        SuspendThread(hThread2);
        TerminateThread(hThread2, 0);
// закрываем дескриптор потока
        CloseHandle(hThread2);}
    return 0;


}