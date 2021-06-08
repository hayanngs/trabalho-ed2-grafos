#include <bits/stdc++.h>

using namespace std;

int busca_indice(string str, vector<string> &vet);
int converte_hora(string a, string b);

struct Vertice{
    int i_voo;
    int i_aero;
    string hora;
    char tipo; //C = Chegada, P = Partida, O = Origem
};

int main(void)
{
    //[VOO]  [ VERTICE 1 ] [VERTICE 2] [V3 ] [VERTICE 4]
    //   0      1      2    3      4     5    6      7
    //IB8717 Madrid  12:00 LPGC  15:00 15:30 SCT   16:20

    vector<vector<string>> input;
    vector<struct Vertice> vertice;
    vector<string> aeroporto;
    vector<string> voo;
    string str;

    ifstream entrada("entrada.txt");
    while (getline(entrada, str))
    {
        //lendo arquivo e criando vetor de voo e aeroporto
        vector<string> vet_string;
        string y = "";
        for (int i = 0, k = 0; str[i] != '\0'; i++)
        {
            //monta string por string
            if (str[i] != ' ')
            {
                y += str[i];
            }
            else //depois que monta string ela vai ser encaixada de acordo com o que ela é
            {
                if (k == 1 || k == 3 || k == 6)
                {//criar vetor de aeroportos
                    bool entrou = true;
                    for (int j = 0; j < (int)aeroporto.size(); j++)
                    {
                        if (y == aeroporto[j])
                            entrou = false;
                    }
                    if (entrou)
                        aeroporto.push_back(y);
                }
                else if (k == 0)
                {//criar vetor de voo
                    bool entrou = true;
                    for (int j = 0; j < (int)voo.size(); j++)
                    {
                        if (y == voo[j])
                            entrou = false;
                    }
                    if (entrou)
                        voo.push_back(y);
                }
                vet_string.push_back(y);
                y.clear();
                k++;
            }
        }
        vet_string.push_back(y);

        input.push_back(vet_string);
    }

    vector<vector<pair<int, int>>> adjlist;
//    map< int, Vertice > mapa;
    int k = 0;
    for (int i = 0; i < (int)input.size(); i++)
    {
        struct Vertice V;
        V.i_voo = busca_indice(input[i][0], voo);
        V.i_aero = busca_indice(input[i][1], aeroporto);
        V.hora = input[i][2];
        V.tipo = 'P';
        vertice.push_back(V);
        k++;
        vector<pair<int, int> > vert;

        V.i_voo = busca_indice(input[i][0], voo);
        V.i_aero = busca_indice(input[i][3], aeroporto);
        V.hora = input[i][4];
        V.tipo = 'C';
        vertice.push_back(V);
        int c = converte_hora(input[i][2], input[i][4]);
        vert.push_back(pair<int, int>(k, c));

        if (input[i].size() > 5)
        {
            V.i_voo = busca_indice(input[i][0], voo);
            V.i_aero = busca_indice(input[i][3], aeroporto);
            V.hora = input[i][5];
            V.tipo = 'P';
            vertice.push_back(V);

            V.i_voo = busca_indice(input[i][0], voo);
            V.i_aero = busca_indice(input[i][6], aeroporto);
            V.hora = input[i][7];
            V.tipo = 'C';
            vertice.push_back(V);
        }
    }

  return 0;
}

int busca_indice(string str, vector<string> &vet)
{
    for (int i = 0; i < (int)vet.size(); i++)
    {
        if (str == vet[i])
        {
            return i;
        }
    }
    return -1;
}

int converte_hora(string a, string b)
{
    int i = a.size()-1;
    int minuto_a = 0;
    int minuto_b = 0;
    int pot = 1;
    while (a[i] != ':')
    {
        minuto_a += (a[i] - 48)*pot;
        minuto_b += (b[i--] - 48)*pot;
        pot *= 10;
    }
    i--;
    pot = 1;
    while (i != -1)
    {
        minuto_a += ((a[i] - 48)*pot)*60;
        minuto_b += ((b[i--] - 48)*pot)*60;
        pot *= 10;
    }
    return minuto_b - minuto_a;
}
