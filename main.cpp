#include <bits/stdc++.h>
/*
 * Aluno: Hayann Gonçalves Silva
 *
 * Obs: Se estiver no sistema operacional Windows trocar os "system("clear")" por "system("cls")"
*/
using namespace std;

typedef long int                        li;
typedef map < string, li >              i_map;
typedef map < li, string >              n_map;
typedef vector<vector<string>>          vet_str;
typedef vector < vector <li> >          vet_aero;
typedef vector<struct Vertice>          vet_vertice;
typedef vector<vector<pair<li, li>>>    Adjlist;

#define inf 10000000000000
#define arquivo "entrada.txt"

li dist[2000];
li pai[2000];

//-----------------------------MONTANDO A ESTRUTURA----------------------------
void entrada_arquivo(vet_str &input, i_map &indice_aeroporto, i_map &indice_voo, n_map &nome_aeroporto, n_map &nome_voo, li &count_voo, li &count_aero);
void criar_vertices_origem(li count_aero, vet_aero &vector_aeroporto, Adjlist &adjlist, vet_vertice &vertice);
void criar_vertices_matriz_adj(vet_str &input, i_map &indice_aeroporto, i_map &indice_voo, Adjlist &adjlist, vet_vertice &vertice, vet_aero &vector_aeroporto, li &count_aero);
void ligando_os_vertices(Adjlist &adjlist, vet_vertice &vertice,vet_aero &vector_aeroporto, li count_aero);
//-----------------------------------------------------------------------------

//-----------------------------------EXECUÇÃO----------------------------------
void menu1(char &opcao);
void menu2(char &opcao);
void listagem_aeroportos(n_map &nome_aero);
void rodar_todos_os_casos(i_map &indice_aeroporto, n_map &nome_aeroporto, n_map &nome_voo, Adjlist &adjlist, vet_vertice &vertice);
void rodar_caso_tempo_livre(n_map &nome_aeroporto, n_map &nome_voo, Adjlist &adjlist, vet_vertice &vertice, long S, long D);
void rodar_caso_limitando_partida(n_map &nome_aeroporto, n_map &nome_voo, Adjlist &adjlist, vet_vertice &vertice, li S, li D, li h_partida);
void rodar_caso_limitando_chegada(n_map &nome_aeroporto, n_map &nome_voo, Adjlist &adjlist, vet_vertice &vertice, li S, li D, li h_chegada);
void rodar_caso_limitando_partida_chegada(n_map &nome_aeroporto, n_map &nome_voo, Adjlist &adjlist, vet_vertice &vertice, li S, li D, li h_partida, li h_chegada);

li converte_hora(string a, string b);
li converte_hora_unica(string a);
li dijkstra(vector<vector<pair<li, li>>> &adjlist, vector<struct Vertice> &vertice, li N, li S, li D);
li dijkstra_limitando_partida(vector<vector<pair<li, li>>> &adjlist, vector<struct Vertice> &vertice, li N, li S, li D, li h_partida);
li dijkstra_limitando_chegada(vector<vector<pair<li, li>>> &adjlist, vector<struct Vertice> &vertice, li N, li S, li D, li h_chegada);
li dijkstra_limitando_partida_chegada(vector<vector<pair<li, li>>> &adjlist, vector<struct Vertice> &vertice, li N, li S, li D, li h_partida, li h_chegada);
void printPath(vector<int> &caminho, int destiny );
//-----------------------------------------------------------------------------

struct Vertice{
    li i_voo;
    li i_aero;
    string hora;
    char tipo; //C = Chegada, P = Partida, O = Origem
};

int main(void)
{
//---------------------------------DECLARAÇÕES---------------------------------
    vet_str input;
    vet_vertice vertice;
    Adjlist adjlist;

    vet_aero vector_aeroporto;

    i_map indice_aeroporto;
    n_map nome_aeroporto;
    li count_aero = 0;

    i_map indice_voo;
    n_map nome_voo;
    li count_voo = 0;
//-----------------------------------------------------------------------------

//-----------------------------MONTANDO A ESTRUTURA----------------------------
    entrada_arquivo(input, indice_aeroporto, indice_voo, nome_aeroporto, nome_voo, count_voo, count_aero);

    criar_vertices_origem(count_aero, vector_aeroporto, adjlist, vertice);

    criar_vertices_matriz_adj(input, indice_aeroporto, indice_voo, adjlist, vertice, vector_aeroporto, count_aero);

    ligando_os_vertices(adjlist, vertice, vector_aeroporto, count_aero);
//-----------------------------------------------------------------------------

//-----------------------------------EXECUÇÃO----------------------------------
    char opcao1, opcao2, voltar;
    do
    {
        menu1(opcao1);
        switch (opcao1) {
        case '1':
            rodar_todos_os_casos(indice_aeroporto, nome_aeroporto, nome_voo, adjlist, vertice);
            cout << "> 0 - Voltar: ";cin >> voltar;
            system("clear");
            break;
        case '2':
            do
            {
                menu2(opcao2);
                int origem, destino;
                string hora_partida, hora_chegada;
                listagem_aeroportos(nome_aeroporto);
                cout << "> ID Origem: ";cin >> origem;
                cout << "> ID Destino: ";cin >> destino;
                switch (opcao2) {
                case '1'://tempo livre
                    rodar_caso_tempo_livre(nome_aeroporto, nome_voo, adjlist, vertice, origem, destino);
                    break;
                case '2'://limitar hora de partida
                {
                    cout << "> Hora Partida: ";cin >> hora_partida;
                    rodar_caso_limitando_partida(nome_aeroporto, nome_voo, adjlist, vertice, origem, destino, converte_hora_unica(hora_partida));
                }
                    break;
                case '3'://limitar hora de chegada
                {
                    cout << "> Hora Chegada: ";cin >> hora_chegada;
                    rodar_caso_limitando_chegada(nome_aeroporto, nome_voo, adjlist, vertice, origem, destino, converte_hora_unica(hora_chegada));
                }
                    break;
                case '4'://limitar hora de partida e chegada
                {
                    cout << "> Hora Partida: ";cin >> hora_partida;
                    cout << "> Hora Chegada: ";cin >> hora_chegada;
                    rodar_caso_limitando_partida_chegada(nome_aeroporto, nome_voo, adjlist, vertice, origem, destino, converte_hora_unica(hora_partida), converte_hora_unica(hora_chegada));
                }
                    break;
                }
                cout << "\n> 0-Voltar 1-Novo Teste: "; cin >> opcao2;
            } while (opcao2 != '0');

            break;
        }
    } while (opcao1 != '0');
//-----------------------------------------------------------------------------
    return 0;
}

li dijkstra(vector<vector<pair<li, li>>> &adjlist, vector<struct Vertice> &vertice, li N, li S, li D)
{
    priority_queue<pair<li, li>, vector<pair<li, li> >, greater<pair<li, li> > > q;
    priority_queue<pair<li, li>, vector<pair<li, li> >, greater<pair<li, li> > > vamos_ver;
    for (li i = 0; i < N; i++)
    {
        dist[i] = inf;
        pai[i]  = -1;
        q.push(pair<li, li>(dist[i], i));
    }
    dist[S] = 0;
    q.push(pair<li, li>(dist[S], S));

    while (!q.empty())
    {
        li at = q.top().second;
        q.pop();
        if (vertice[at].i_aero == D)
        {
            vamos_ver.push(pair<li, li>(dist[at], at));
        }

        for (pair<li, li> it : adjlist[at])
        {
            li to = it.first;
            li G = it.second;

            if (dist[to] > dist[at] + G)
            {
                dist[to] = dist[at] + G;
                pai[to]  = at;
                q.push(pair<li, li>(dist[to], to));
            }
        }
    }
    if (!vamos_ver.empty())
    {
        pai[D] = vamos_ver.top().second;
        return vamos_ver.top().first;
    }
    else
        return -1;
}

li dijkstra_limitando_partida(vector<vector<pair<li, li>>> &adjlist, vector<struct Vertice> &vertice, li N, li S, li D, li h_partida)
{
    priority_queue<pair<li, li>, vector<pair<li, li> >, greater<pair<li, li> > > q;
    priority_queue<pair<li, li>, vector<pair<li, li> >, greater<pair<li, li> > > vamos_ver;
    for (li i = 0; i < N; i++)
    {
        dist[i] = inf;
        pai[i]  = -1;
        q.push(pair<li, li>(dist[i], i));
    }
    dist[S] = 0;
    q.push(pair<li, li>(dist[S], S));

    while (!q.empty())
    {
        li at = q.top().second;
        q.pop();
        li horario_partida = converte_hora_unica(vertice[at].hora);
        if (horario_partida > h_partida && vertice[at].i_aero == vertice[S].i_aero) continue;
        if (vertice[at].i_aero == D)
        {
            vamos_ver.push(pair<li, li>(dist[at], at));
        }

        for (pair<li, li> it : adjlist[at])
        {
            li to = it.first;
            li G = it.second;

            if (dist[to] > dist[at] + G)
            {
                dist[to] = dist[at] + G;
                pai[to]  = at;
                q.push(pair<li, li>(dist[to], to));
            }
        }
    }
    if (!vamos_ver.empty())
    {
        pai[D] = vamos_ver.top().second;
        return vamos_ver.top().first;
    }
    else
        return -1;
}

li dijkstra_limitando_chegada(vector<vector<pair<li, li>>> &adjlist, vector<struct Vertice> &vertice, li N, li S, li D, li h_chegada)
{
    priority_queue<pair<li, li>, vector<pair<li, li> >, greater<pair<li, li> > > q;
    priority_queue<pair<li, li>, vector<pair<li, li> >, greater<pair<li, li> > > vamos_ver;
    for (li i = 0; i < N; i++)
    {
        dist[i] = inf;
        pai[i]  = -1;
        q.push(pair<li, li>(dist[i], i));
    }
    dist[S] = 0;
    q.push(pair<li, li>(dist[S], S));

    while (!q.empty())
    {
        li at = q.top().second;
        q.pop();
        li horario_chegada = converte_hora_unica(vertice[at].hora);
        if (horario_chegada > h_chegada && vertice[at].i_aero == vertice[D].i_aero) continue;
        if (vertice[at].i_aero == D)
        {
            vamos_ver.push(pair<li, li>(dist[at], at));
        }

        for (pair<li, li> it : adjlist[at])
        {
            li to = it.first;
            li G = it.second;

            if (dist[to] > dist[at] + G)
            {
                dist[to] = dist[at] + G;
                pai[to]  = at;
                q.push(pair<li, li>(dist[to], to));
            }
        }
    }
    if (!vamos_ver.empty())
    {
        pai[D] = vamos_ver.top().second;
        return vamos_ver.top().first;
    }
    else
        return -1;
}

li dijkstra_limitando_partida_chegada(vector<vector<pair<li, li>>> &adjlist, vector<struct Vertice> &vertice, li N, li S, li D, li h_partida, li h_chegada)
{
    priority_queue<pair<li, li>, vector<pair<li, li> >, greater<pair<li, li> > > q;
    priority_queue<pair<li, li>, vector<pair<li, li> >, greater<pair<li, li> > > vamos_ver;
    for (li i = 0; i < N; i++)
    {
        dist[i] = inf;
        pai[i]  = -1;
        q.push(pair<li, li>(dist[i], i));
    }
    dist[S] = 0;
    q.push(pair<li, li>(dist[S], S));

    while (!q.empty())
    {
        li at = q.top().second;
        q.pop();
        li horario = converte_hora_unica(vertice[at].hora);
        if (horario > h_partida && vertice[at].i_aero == vertice[S].i_aero) continue;
        if (horario > h_chegada && vertice[at].i_aero == vertice[D].i_aero) continue;
        if (vertice[at].i_aero == D)
        {
            vamos_ver.push(pair<li, li>(dist[at], at));
        }

        for (pair<li, li> it : adjlist[at])
        {
            li to = it.first;
            li G = it.second;

            if (dist[to] > dist[at] + G)
            {
                dist[to] = dist[at] + G;
                pai[to]  = at;
                q.push(pair<li, li>(dist[to], to));
            }
        }
    }
    if (!vamos_ver.empty())
    {
        pai[D] = vamos_ver.top().second;
        return vamos_ver.top().first;
    }
    else
        return -1;
}

void printPath(vector<int> &caminho, int destiny )
{
    if ( destiny != -1)
    {
        printPath( caminho, pai[ destiny ]);
        caminho.push_back(destiny);
    }
}

li converte_hora(string a, string b)
{
    li i = a.size()-1;
    li minuto_a = 0;
    li minuto_b = 0;
    li pot = 1;
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
    li diferenca = minuto_b - minuto_a;
    return diferenca < 0? diferenca + 1440 : diferenca;
}

li converte_hora_unica(string a)
{
    li i = a.size()-1;
    li minuto_a = 0;
    li pot = 1;
    while (a[i] != ':')
    {
        minuto_a += (a[i--] - 48)*pot;
        pot *= 10;
    }
    i--;
    pot = 1;
    while (i != -1)
    {
        minuto_a += ((a[i--] - 48)*pot)*60;
        pot *= 10;
    }
    return minuto_a;
}

void entrada_arquivo(vet_str &input, i_map &indice_aeroporto, i_map &indice_voo, n_map &nome_aeroporto, n_map &nome_voo, long &count_voo, long &count_aero)
{
    //[VOO]  [ VERTICE 1 ] [VERTICE 2] [V3 ] [VERTICE 4]
    //   0      1      2    3      4     5    6      7
    //IB8717 Madrid  12:00 LPGC  15:00 15:30 SCT   16:20

    string str;
    ifstream entrada(arquivo);
    while (getline(entrada, str))
    { //lendo arquivo e criando vetor de voo e aeroporto
        vector<string> vet_string;
        string y = "";
        for (li i = 0, k = 0; str[i] != '\0'; i++)
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
                        nome_aeroporto.insert(pair<li, string>(count_aero, y));
                        indice_aeroporto.insert(pair<string, li>(y, count_aero++));
                    }
                }
                else if (k == 0)
                {//criar vetor de voo
                    if (indice_voo.find(y) == indice_voo.end())
                    {
                        nome_voo.insert(pair<li, string>(count_voo, y));
                        indice_voo.insert(pair<string, li>(y, count_voo++));
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
}

void criar_vertices_matriz_adj(vet_str &input, i_map &indice_aeroporto, i_map &indice_voo, Adjlist &adjlist, vet_vertice &vertice,vet_aero &vector_aeroporto, li &count_aero)
{
    li k = count_aero;
    for (li i = 0; i < (li)input.size(); i++)
    {
        vector<pair<li, li>> ADJ;
        struct Vertice V;
        li v1 = k++;
        li v2 = k++;

        V.i_voo = indice_voo.find(input[i][0])->second;
        V.i_aero = indice_aeroporto.find(input[i][1])->second;
        V.hora = input[i][2];
        V.tipo = 'P';
        vertice.push_back(V);                     //vetor de vértice struct
        vector_aeroporto[V.i_aero].push_back(v1); //separar vértice por aeroporto
        adjlist.push_back(ADJ);                   //acrescentando adjacência
        adjlist[v1].push_back(pair<li, li>(v2, converte_hora(input[i][2], input[i][4])));


        V.i_aero = indice_aeroporto.find(input[i][3])->second;
        V.hora = input[i][4];
        V.tipo = 'C';
        vertice.push_back(V);
        vector_aeroporto[V.i_aero].push_back(v2); //separar vértice por aeroporto
        adjlist.push_back(ADJ);                   //acrescentando adjacência


        if (input[i].size() > 5)
        {
            li v3 = k++;
            li v4 = k++;
            li minuto = converte_hora(input[i][4], input[i][5]);
            adjlist[v2].push_back(pair<li, li>(v3, minuto));

            V.i_aero = indice_aeroporto.find(input[i][3])->second;
            V.hora = input[i][5];
            V.tipo = 'P';
            vertice.push_back(V);
            vector_aeroporto[V.i_aero].push_back(v3); //separar vértice por aeroporto
            adjlist.push_back(ADJ);                   //acrescentando adjacência

            adjlist[v3].push_back(pair<li, li>(v4, converte_hora(input[i][5], input[i][7])));

            V.i_aero = indice_aeroporto.find(input[i][6])->second;
            V.hora = input[i][7];
            V.tipo = 'C';
            vertice.push_back(V);
            vector_aeroporto[V.i_aero].push_back(v4); //separar vértice por aeroporto
            adjlist.push_back(ADJ);                   //acrescentando adjacência
        }
    }
}

void criar_vertices_origem(li count_aero, vet_aero &vector_aeroporto, Adjlist &adjlist, vet_vertice &vertice)
{
    for (li i = 0; i < count_aero; i++)
    {
        vector <li> int_aero;
        vector_aeroporto.push_back(int_aero);
        struct Vertice V;
        V.hora   = "00:00";
        V.tipo   = 'O';
        V.i_voo  = -1;
        V.i_aero = i;
        vertice.push_back(V);
        vector<pair<li, li>> origem;
        adjlist.push_back(origem);
        vector_aeroporto[i].push_back(i);
    }
}

void ligando_os_vertices(Adjlist &adjlist, vet_vertice &vertice,vet_aero &vector_aeroporto, li count_aero)
{
    for (li i = 0; i < count_aero; i++)
    {
        li origem = vector_aeroporto[i][0];
        for (li j = 1; j < (li)vector_aeroporto[i].size(); j++)
        {
            li partida = vector_aeroporto[i][j];
            if (vertice[partida].tipo == 'P')
            {
                adjlist[origem].push_back(pair<li, li>(partida, 0));
            }
            else
            {
                if (vertice[partida].tipo == 'C')
                {
                    for (li y = 1; y < (li)vector_aeroporto[i].size(); y++)
                    {
                        li outro = vector_aeroporto[i][y];
                        if (vertice[outro].tipo == 'P')
                        {
                            int minuto = converte_hora(vertice[partida].hora, vertice[outro].hora);
                            if (minuto < 30)
                            {
                                minuto += 1440;
                            }
                            adjlist[partida].push_back(pair<li, li>(outro, minuto));
                        }
                    }
                }
            }
        }
    }
}

void rodar_todos_os_casos(i_map &indice_aeroporto, n_map &nome_aeroporto, n_map &nome_voo, Adjlist &adjlist, vet_vertice &vertice)
{
    for (map < string, li >::iterator at = indice_aeroporto.begin(); at != indice_aeroporto.end(); ++at)
    {
        for (map < string, li >::iterator to = indice_aeroporto.begin(); to != indice_aeroporto.end(); ++to)
        {
            if (at->second != to->second)
            {
                cout << "Origem: " << at->first << endl;
                cout << "Destino: " << to->first << endl;
                li S = indice_aeroporto.find(at->first)->second;
                li D = indice_aeroporto.find(to->first)->second;
                li distancia = dijkstra(adjlist, vertice, vertice.size(), S, D);
                if (distancia == -1 || distancia == inf)
                {
                    cout << "> Não há rota." << endl;
                    cout << "**********************************************************************" << endl;
                    continue;
                }
                cout << "Tempo min.: " << distancia << endl;
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
                cout << "**********************************************************************" << endl;
            }
        }
        //char i;cin >> i; //interrupção
    }
}

void rodar_caso_tempo_livre(n_map &nome_aeroporto, n_map &nome_voo, Adjlist &adjlist, vet_vertice &vertice, li S, li D)
{
    li distancia = dijkstra(adjlist, vertice, vertice.size(), S, D);
    if (distancia != -1 && distancia != inf)
    {
        cout << "> Tempo min.: " << distancia << endl << endl;
        vector<int> caminho;
        printPath(caminho, D);
        int prox = 0;
        for (int i = 0; i < (int)caminho.size(); i++)
        {
            int id = caminho[i];
            if (id != -1 && vertice[id].tipo != 'O')
            {
                if (vertice[id].i_voo != vertice[prox].i_voo)
                {
                    string voo  = nome_voo.find(vertice[id].i_voo)->second;
                    string aero = nome_aeroporto.find(vertice[id].i_aero)->second;
                    cout << "\n" << voo << " " << aero << " " << vertice[id].hora;// << endl;
                }
                else
                {
                    string aero = nome_aeroporto.find(vertice[id].i_aero)->second;
                    cout << " " << aero << " " << vertice[id].hora;// << endl;
                }
                prox = id;
            }
        }
        cout << endl;
    }
    else
    {
        cout << "> Não há rota para essa origem e destino." << endl;
    }
}

void rodar_caso_limitando_partida(n_map &nome_aeroporto, n_map &nome_voo, Adjlist &adjlist, vet_vertice &vertice, li S, li D, li h_partida)
{
    li distancia = dijkstra_limitando_partida(adjlist, vertice, vertice.size(), S, D, h_partida);
    if (distancia != -1 && distancia != inf)
    {
        cout << "> Tempo min.: " << distancia << endl << endl;
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
    }
    else
    {
        cout << "> Não há rota." << endl;
    }
}

void rodar_caso_limitando_chegada(n_map &nome_aeroporto, n_map &nome_voo, Adjlist &adjlist, vet_vertice &vertice, li S, li D, li h_chegada)
{
    li distancia = dijkstra_limitando_chegada(adjlist, vertice, vertice.size(), S, D, h_chegada);
    if (distancia != -1 && distancia != inf)
    {
        cout << "> Tempo min.: " << distancia << endl << endl;
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
    }
    else
    {
        cout << "> Não há rota." << endl;
    }
}

void rodar_caso_limitando_partida_chegada(n_map &nome_aeroporto, n_map &nome_voo, Adjlist &adjlist, vet_vertice &vertice, li S, li D, li h_partida, li h_chegada)
{
    li distancia = dijkstra_limitando_partida_chegada(adjlist, vertice, vertice.size(), S, D, h_partida, h_chegada);
    if (distancia != -1 && distancia != inf)
    {
        cout << "> Tempo min.: " << distancia << endl << endl;
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
    }
    else
    {
        cout << "> Não há rota." << endl;
    }
}

void menu1(char &opcao)
{
    system("clear");
    cout << "\tTrabalho Grafos\n"
            "-------------------------------\n"
            "[1] Executar todos os casos possíveis.\n"
            "[2] Executar casos específicos.\n"
            "[0] Sair do programa.\n\n"
            "> Escolha a forma de execução: ";
    cin >> opcao;
    cout << endl;
}

void menu2(char &opcao)
{
    system("clear");
    cout << "-------------------------------\n"
            "[1] Tempo livre.\n"
            "[2] Limitar hora de partida.\n"
            "[3] Limitar hora de chegada.\n"
            "[4] Limitar hora de partida e chegada.\n"
            "[0] Voltar.\n\n"
            "> Escolha a forma de execução: ";
    cin >> opcao;
}

void listagem_aeroportos(n_map &nome_aero)
{
    cout << "\n> ID\tAeroporto";
    cout << "\n-------------------------------\n";
    for (n_map::iterator it = nome_aero.begin(); it != nome_aero.end(); ++it)
    {
        cout << "> " << it->first << "\t" << it->second << endl;
    }
    cout << "-------------------------------\n\n";
}
