
#include <iostream>
#include<Windows.h>
#include<conio.h>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    HANDLE end = CreateEvent(NULL, FALSE, FALSE, "end");
    HANDLE write = (HANDLE) atoi(argv[1]);
    HANDLE read = (HANDLE) atoi(argv[2]);
    HANDLE event = OpenEvent(SYNCHRONIZE, FALSE, "1");
    if (event == NULL) {
        GetLastError();
    }

    WaitForSingleObject(event, INFINITE);
    float *a = new float[atoi(argv[3])];
    int n = atoi(argv[3]);

    for (int i = 0; i < atoi(argv[3]); i++) {
        DWORD s;
        ReadFile(read, &a[i], sizeof(a[i]), &s, NULL);
    }

    for (int i = 0; i < atoi(argv[3]); i++) {
        cout << a[i]<<endl;
    }
    int new_size;
    cout << "enter size:"<<endl;
    cin >> new_size;
    float *new_mas = new float[new_size];
    float elem;
    for (int i = 0; i < new_size; i++) {
        cout << "enter elem" << endl;
        cin >> elem;
        new_mas[i] = elem;
    }

    float *new_mas1 = new float[new_size + atoi(argv[3])];
    for (int i = 0; i < atoi(argv[3]); i++) {

        new_mas1[i] = a[i];
    }
    for (int i = atoi(argv[3]); i < new_size + atoi(argv[3]); i++) {

        new_mas1[i] = new_mas[i - atoi(argv[3])];
    }

    for (int i = 0; i < new_size + atoi(argv[3]); i++) {

        cout << i << ":" << new_mas1[i] << endl;
    }

    cout << '\n';

    int b = 0;

    set<int> del;
    for (size_t i = 0; i < b; i++) {
        del.insert(rand() % n);

    }
    DWORD sz;
    float c[2];

    c[0]=8;
    c[1]=new_size+n;
    WriteFile(write, &c[1], sizeof(c[1]), &sz, NULL);
    for (size_t i = 0; i < n+new_size; i++) {
        WriteFile(write, &new_mas1[i], sizeof(new_mas1[i]), &sz, NULL);
    }

    SetEvent(end);
    _getch();

}
