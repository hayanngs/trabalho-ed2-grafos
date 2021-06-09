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
    vector<vector<pair<int, int>>> adjlist;
    map < string, int > indice_aeroporto; int count_aero = 0;
    map < string, int > indice_voo; int count_voo = 0;
    string str;

    ifstream entrada("entrada.txt");
    while (getline(entrada, str))
    { //lendo arquivo e criando vetor de voo e aeroporto
        vector<string> vet_string;
        string y = "";
        for (int i = 0, k = 0; str[i] != '\0'; i++)
        {//monta string por string
            if (str[i] != ' ')
            {
                y += str[i];
            }
            else //depois que monta string ela vai ser encaixada de acordo com o que ela é
            {
                if (k == 1 || k == 3 || k == 6)
                {//criar vetor de aeroportos
                    if (indice_aeroporto.find(y) == indice_aeroporto.end())
                    {
                        indice_aeroporto.insert(pair<string, int>(y, count_aero++));
                    }
                }
                else if (k == 0)
                {//criar vetor de voo
                    if (indice_voo.find(y) == indice_voo.end())
                    {
                        indice_voo.insert(pair<string, int>(y, count_voo++));
                    }
                }
                vet_string.push_back(y);
                y.clear();
                k++;
            }
        }
        vet_string.push_back(y);

        input.push_back(vet_string);
    }

    //CRIAR VÉRTICES ORIGEM
    vector <int> vector_aeroporto[count_aero];
    for (int i = 0; i < count_aero; i++)
    {
        struct Vertice V;
        V.hora   = "00:00";
        V.tipo   = 'O';
        V.i_voo  = -1;
        V.i_aero = i;
        vertice.push_back(V);
        vector<pair<int, int>> origem;
        adjlist.push_back(origem);
        vector_aeroporto[i].push_back(i);
    }

    //CRIAR VERTICES E MATRIZ DE ADJACENCIA

    int k = count_aero;
    for (int i = 0; i < (int)input.size(); i++)
    {
        vector<pair<int, int>> ADJ;
        struct Vertice V;
        int v1 = k++;
        int v2 = k++;

        V.i_voo = indice_voo.find(input[i][0])->second;
        V.i_aero = indice_aeroporto.find(input[i][1])->second;
        V.hora = input[i][2];
        V.tipo = 'P';
        vertice.push_back(V);                     //vetor de vértice struct
        vector_aeroporto[V.i_aero].push_back(v1); //separar vértice por aeroporto
        adjlist.push_back(ADJ);                   //acrescentando adjacência
        adjlist[v1].push_back(pair<int, int>(v2, converte_hora(input[i][2], input[i][4])));


        V.i_aero = indice_aeroporto.find(input[i][3])->second;
        V.hora = input[i][4];
        V.tipo = 'C';
        vertice.push_back(V);
        vector_aeroporto[V.i_aero].push_back(v2); //separar vértice por aeroporto
        adjlist.push_back(ADJ);                   //acrescentando adjacência


        if (input[i].size() > 5)
        {
            int v3 = k++;
            int v4 = k++;
            adjlist[v2].push_back(pair<int, int>(v3, converte_hora(input[i][4], input[i][5])));

            V.i_aero = indice_aeroporto.find(input[i][3])->second;
            V.hora = input[i][5];
            V.tipo = 'P';
            vertice.push_back(V);
            vector_aeroporto[V.i_aero].push_back(v3); //separar vértice por aeroporto
            adjlist.push_back(ADJ);                   //acrescentando adjacência

            adjlist[v3].push_back(pair<int, int>(v4, converte_hora(input[i][5], input[i][7])));

            V.i_aero = indice_aeroporto.find(input[i][6])->second;
            V.hora = input[i][7];
            V.tipo = 'C';
            vertice.push_back(V);
            vector_aeroporto[V.i_aero].push_back(v4); //separar vértice por aeroporto
            adjlist.push_back(ADJ);                   //acrescentando adjacência
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
