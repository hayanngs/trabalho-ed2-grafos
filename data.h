#ifndef DATA_H
#define DATA_H

#include <string>
using namespace std;

class Data
{
private:
    int dia;
    int mes;
    int ano;
public:
    Data();
    Data(int d, int m, int a);
    void setData(int d, int m, int a);
    string getData();
    bool validaData(int d, int m, int a);
    Data soma(int num);
};

#endif // DATA_H
