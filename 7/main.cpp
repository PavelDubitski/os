#include <windows.h>
#include <ctime>
#include <stdlib.h>
#include <iostream>
using namespace std;

char* stack;
HANDLE Add;
HANDLE Remove;
CRITICAL_SECTION cs;

class MonitorStack {
private:
    int maxSize, Size;
public:
    MonitorStack() {
        maxSize = 0;
        Size = 0;
    }

    explicit MonitorStack(int nSize) {
        stack = new char[nSize];
        maxSize = nSize;
        Size = 0;
    };


    char Pop() {
        WaitForSingleObject(Remove, INFINITE);
        char elem = stack[Size - 1];
        Size--;
        ReleaseSemaphore(Add, 1, NULL);
        return elem;
    };
    void Push(char nElement) {
        WaitForSingleObject(Add, INFINITE);
        stack[Size] = nElement;
        Size++;
        ReleaseSemaphore(Remove, 1, NULL);
    };

};

MonitorStack mon;

DWORD WINAPI consume(LPVOID n) {
int cnt = (int)n;
for (int i = 0; i < cnt; i++) {
char t = mon.Pop();
EnterCriticalSection(&cs);
cout << "Consumed char: " << t << endl;
LeaveCriticalSection(&cs);

}
return 0;
}

DWORD WINAPI produce(LPVOID n) {
int cnt = (int)n;
int t;
for (int i = 0; i < cnt; i++) {
   
    srand(time(0));
    t = rand() % (254-1);
EnterCriticalSection(&cs);
cout << "Produced char: " << (char)t << endl;
LeaveCriticalSection(&cs);
mon.Push((char)t);

}
return 0;
}

int main() {
    int c, p, size;
    int* consumed;
    int* produced;
    HANDLE* handles;
    DWORD* consumersID;
    DWORD* producersID;
    cout << "Enter consumers number: " << endl;
    cin >> c;
    consumed = new int[c];
    cout << "Enter producers number: " << endl;
    cin >> p;
    produced = new int[p];
    cout << "Enter stack size: " << endl;
    cin >> size;
    mon = MonitorStack(size);
    Add = CreateSemaphore(NULL, size, size, NULL);
    Remove = CreateSemaphore(NULL, 0, size, NULL);
    InitializeCriticalSection(&cs);
    handles = new HANDLE[c + p];
    consumersID = new DWORD[c];
    producersID = new DWORD[p];
    int pos = 0;
    for (int i = 0; i < c; i++) {
        cout << "Enter consumed number of: "<<i +1<< endl;
        cin >> consumed[i];
    }
    for (int i = 0; i < p; i++) {
        cout << "Enter produced number of: "<<i+1 << endl;
        cin >> produced[i];
    }

    for (int i = 0; i < p; i++, pos++)
        handles[i] = CreateThread(NULL, 0, produce, (char*)produced[i], 0, &producersID[i]);
    for (int i = 0; i < c; i++, pos++)
        handles[pos] = CreateThread(NULL, 0, consume, (char*)consumed[i], 0, &consumersID[i]);
    WaitForMultipleObjects(c + p, handles, TRUE, INFINITE);
    return 0;
};