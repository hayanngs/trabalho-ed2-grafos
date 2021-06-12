#include <bits/stdc++.h>

using namespace std;

long int dist[2000];
long int pai[2000];

long int converte_hora(string a, string b);
long int dijkstra(vector<vector<pair<long int, long int>>> &adjlist, vector<struct Vertice> &vertice, long int N, long int S, long int D);
void printPath(vector<int> &caminho, int destiny );

struct Vertice{
    long int i_voo;
    long int i_aero;
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
    vector<vector<pair<long int, long int>>> adjlist;

    map < string, long int > indice_aeroporto;
    map < long int, string > nome_aeroporto;
    long int count_aero = 0;

    map < string, long int > indice_voo;
    map < long int, string > nome_voo;
    long int count_voo = 0;
    string str;

    ifstream entrada("entrada2.txt");
    while (getline(entrada, str))
    { //lendo arquivo e criando vetor de voo e aeroporto
        vector<string> vet_string;
        string y = "";
        for (long int i = 0, k = 0; str[i] != '\0'; i++)
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
                        nome_aeroporto.insert(pair<long int, string>(count_aero, y));
                        indice_aeroporto.insert(pair<string, long int>(y, count_aero++));
                    }
                }
                else if (k == 0)
                {//criar vetor de voo
                    if (indice_voo.find(y) == indice_voo.end())
                    {
                        nome_voo.insert(pair<long int, string>(count_voo, y));
                        indice_voo.insert(pair<string, long int>(y, count_voo++));
                    }
                    else
                        cout << "VOO FDP AQUI: " << y << endl;
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
    vector <long int> vector_aeroporto[count_aero];
    for (long int i = 0; i < count_aero; i++)
    {
        struct Vertice V;
        V.hora   = "00:00";
        V.tipo   = 'O';
        V.i_voo  = -1;
        V.i_aero = i;
        vertice.push_back(V);
        vector<pair<long int, long int>> origem;
        adjlist.push_back(origem);
        vector_aeroporto[i].push_back(i);
    }

    //CRIAR VERTICES E MATRIZ DE ADJACENCIA

    long int k = count_aero;
    for (long int i = 0; i < (long int)input.size(); i++)
    {
        vector<pair<long int, long int>> ADJ;
        struct Vertice V;
        long int v1 = k++;
        long int v2 = k++;

        V.i_voo = indice_voo.find(input[i][0])->second;
        V.i_aero = indice_aeroporto.find(input[i][1])->second;
        V.hora = input[i][2];
        V.tipo = 'P';
        vertice.push_back(V);                     //vetor de vértice struct
        vector_aeroporto[V.i_aero].push_back(v1); //separar vértice por aeroporto
        adjlist.push_back(ADJ);                   //acrescentando adjacência
        adjlist[v1].push_back(pair<long int, long int>(v2, converte_hora(input[i][2], input[i][4])));


        V.i_aero = indice_aeroporto.find(input[i][3])->second;
        V.hora = input[i][4];
        V.tipo = 'C';
        vertice.push_back(V);
        vector_aeroporto[V.i_aero].push_back(v2); //separar vértice por aeroporto
        adjlist.push_back(ADJ);                   //acrescentando adjacência


        if (input[i].size() > 5)
        {
            long int v3 = k++;
            long int v4 = k++;
            long int minuto = converte_hora(input[i][4], input[i][5]);
            if (minuto < 30)
                minuto += 1440;
            adjlist[v2].push_back(pair<long int, long int>(v3, minuto));

            V.i_aero = indice_aeroporto.find(input[i][3])->second;
            V.hora = input[i][5];
            V.tipo = 'P';
            vertice.push_back(V);
            vector_aeroporto[V.i_aero].push_back(v3); //separar vértice por aeroporto
            adjlist.push_back(ADJ);                   //acrescentando adjacência

            adjlist[v3].push_back(pair<long int, long int>(v4, converte_hora(input[i][5], input[i][7])));

            V.i_aero = indice_aeroporto.find(input[i][6])->second;
            V.hora = input[i][7];
            V.tipo = 'C';
            vertice.push_back(V);
            vector_aeroporto[V.i_aero].push_back(v4); //separar vértice por aeroporto
            adjlist.push_back(ADJ);                   //acrescentando adjacência
        }
    }

    //LIGANDO OS PONTOS
    for (long int i = 0; i < count_aero; i++)
    {
        long int origem = vector_aeroporto[i][0];
        for (long int j = 1; j < (long int)vector_aeroporto[i].size(); j++)
        {
            long int partida = vector_aeroporto[i][j];
            if (vertice[partida].tipo == 'P')
            {
                adjlist[origem].push_back(pair<long int, long int>(partida, 0));
            }
            else
            {
                if (vertice[partida].tipo == 'C')
                {
                    for (long int y = 1; y < (long int)vector_aeroporto[i].size(); y++)
                    {
                        long int outro = vector_aeroporto[i][y];
                        if (vertice[outro].tipo == 'P')
                        {
                            int minuto = converte_hora(vertice[partida].hora, vertice[outro].hora);
                            if (minuto < 30)
                                minuto += 1440;
                            adjlist[partida].push_back(pair<long int, long int>(outro, minuto));
                        }
                    }
                }
            }
        }
    }
//    for (map < string, long int >::iterator it = indice_aeroporto.begin(); it != indice_aeroporto.end(); ++it)
//    {
//        cout << it->second << " - " << it->first << endl;
//    }
    //RUSHAR DIJKSTRA
    //passar por parametro vetor de distância, quantidade de vértice, adjlist,
    long int S = indice_aeroporto.find("Budapeste")->second;
    long int D = indice_aeroporto.find("Bruxelas")->second;
    cout << dijkstra(adjlist, vertice, vertice.size(), S, D) << endl;
    vector<int> caminho;
    printPath(caminho, D);
    for (int i = 0; i < (int)caminho.size(); i++)
    {
        int id = caminho[i];
        if (id != -1 && vertice[id].tipo != 'O')
        {
            string voo  = nome_voo.find(vertice[id].i_voo)->second;
            string aero = nome_aeroporto.find(vertice[id].i_aero)->second;
            cout << voo << " " << aero << " " << vertice[id].hora << endl;
        }
    }

  return 0;
}

long int dijkstra(vector<vector<pair<long int, long int>>> &adjlist, vector<struct Vertice> &vertice, long int N, long int S, long int D)
{
    priority_queue<pair<long int, long int>, vector<pair<long int, long int> >, greater<pair<long int, long int> > > q;

    for (long int i = 0; i < N; i++)
    {
        dist[i] = 10000000000000;
        pai[i]  = -1;
        q.push(pair<long int, long int>(dist[i], i));
    }
    dist[S] = 0;
    q.push(pair<long int, long int>(dist[S], S));


    while (!q.empty())
    {
        long int at = q.top().second;
        q.pop();
        if (vertice[at].i_aero == D)
        {
            pai[D] = at;
            return dist[at];
        }

        for (pair<long int, long int> it : adjlist[at])
        {
            long int to = it.first;
            long int G = it.second;

            if (dist[to] > dist[at] + G)
            {
                dist[to] = dist[at] + G;
                pai[to]  = at;
                q.push(pair<long int, long int>(dist[to], to));
            }
        }
    }
//    return dist[D];
}

void printPath(vector<int> &caminho, int destiny )
{
    if ( destiny != -1)
        printPath( caminho, pai[ destiny ]);
    caminho.push_back(pai[destiny]);
}

long int converte_hora(string a, string b)
{
    long int i = a.size()-1;
    long int minuto_a = 0;
    long int minuto_b = 0;
    long int pot = 1;
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
    long int diferenca = minuto_b - minuto_a;
    return diferenca < 0? diferenca + 1440 : diferenca;
}
