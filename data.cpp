#include "data.h"

Data::Data()
{
    dia = 0;
    mes = 0;
    ano = 0;
}

Data::Data(int d, int m, int a)
{
    bool confirm = validaData(d, m, a);

    if (!confirm)
        throw string("\n> Data invalida!");
    dia = d;
    mes = m;
    ano = a;
}

void Data::setData(int d, int m, int a)
{
    bool confirm = validaData(d, m, a);

    if (!confirm)
        throw string("\n> Data invalida!");
    dia = d;
    mes = m;
    ano = a;
}

Data Data::soma(int num)
{
    int auxdia = dia, auxmes = mes, auxano = ano;
    auxdia += num;
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (auxdia > meses[auxmes-1])
    {
        auxdia -= meses[auxmes-1];
        auxmes++;
        if (auxmes > 12)
        {
            auxano++;
            auxmes = 1;
        }
    }
    Data x(auxdia, auxmes, auxano);
    return x;
}

string Data::getData()
{
    string d = "";
    string m = "";
    string a = "";

    //-----------Convertendo o dia pra string-----------
    int aux = dia;
    while (aux != 0) {
        d += (aux % 10) + 48;
        aux /= 10;
    }
    int tam = (int)d.length();
    for (int i = 0; i < tam/2; i++)
    {
        char x = d[i];
        d[i] = d[tam-1-i];
        d[tam-1-i] = x;
    }
    if (tam == 1)
        d = '0' + d;

    //-----------Convertendo o mes pra string-----------
    aux = mes;
    while (aux != 0) {
        m += (aux % 10) + 48;
        aux /= 10;
    }
    tam = (int)m.length();
    for (int i = 0; i < tam/2; i++)
    {
        char x = m[i];
        m[i] = m[tam-1-i];
        m[tam-1-i] = x;
    }
    if (tam == 1)
        m = '0' + m;

    //-----------Convertendo o ano pra string-----------
    aux = ano;
    while (aux != 0) {
        a += (aux % 10) + 48;
        aux /= 10;
    }
    tam = (int)a.length();
    for (int i = 0; i < tam/2; i++)
    {
        char x = a[i];
        a[i] = a[tam-1-i];
        a[tam-1-i] = x;
    }

    //-----------Retornando a data formatada-----------
    string data = d + '/' + m + '/' + a;
    return data;
}

bool Data::validaData(int d, int m, int a)
{
    if (m > 12 || m < 1)
        return false;
    if (a < 1)
        return false;
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //-----------Validando o ano bissexto-----------
    if(a % 400 == 0)
        meses[1]++;
    else if((a % 4 == 0) && (a % 100 != 0))
        meses[1]++;
    else
        meses[1] = 28;

    //-----------Validando o dia-----------

    switch (m) {
    case 1:
        if (d > meses[0] || d < 1)
            return false;
        break;
    case 2:
        if (d > meses[1] || d < 1)
            return false;
        break;
    case 3:
        if (d > meses[2] || d < 1)
            return false;
        break;
    case 4:
        if (d > meses[3] || d < 1)
            return false;
        break;
    case 5:
        if (d > meses[4] || d < 1)
            return false;
        break;
    case 6:
        if (d > meses[5] || d < 1)
            return false;
        break;
    case 7:
        if (d > meses[6] || d < 1)
            return false;
        break;
    case 8:
        if (d > meses[7] || d < 1)
            return false;
        break;
    case 9:
        if (d > meses[8] || d < 1)
            return false;
        break;
    case 10:
        if (d > meses[9] || d < 1)
            return false;
        break;
    case 11:
        if (d > meses[10] || d < 1)
            return false;
        break;
    case 12:
        if (d > meses[11] || d < 1)
            return false;
        break;
    }
    return true;
}
