#include <windows.h>
#include <iostream>
#include <vector>
using namespace std;
int count1;
int main(int argc, char *argv[]){
vector<int> mas;
vector<int> mas7;
vector<int> masn;
    for (int i = 0; i < argc; i++) {
        // Выводим список аргументов в цикле
        cout << "Argumentt " << i << " : " << argv[i] << endl;

    }
    for (int i = 1; i < argc; i++) {
        // Выводим список аргументов в цикле
        mas.push_back(atoi(argv[i]));
    }
//    for (int i = 0; i < argc-1; i++) {
//        // Выводим список аргументов в цикле
//        cout<<mas[i];
//    }
cout<<endl;

    for(int i = 0; i < mas.size();i++){
    if(mas[i]%7==0){
        mas7.push_back(mas[i]);
    }else
    {masn.push_back(mas[i]);}
}
for(int i = 0; i<mas7.size();i++) {
    cout << mas7[i]<<" ";
}
cout<<endl;
    for(int i = 0; i<masn.size();i++) {
        cout << masn[i]<<" ";
    }
 Sleep(500000);

}
