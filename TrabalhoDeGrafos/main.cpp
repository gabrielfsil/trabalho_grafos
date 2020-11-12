#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include "Grafo.h"
using namespace std;

// Lê a aresta do grafo e separa os vértices e o peso em um array de 3 posições
// Transforma o formato string do arquivo em um tipo int
// array [] = [ Vértice, Vértice Adjacente, Peso ]
void split(string str, char separator, int array[])
{
    istringstream iss;

    int index = 0;

    iss.str(str);

    // "0 1 25"
    // array[0] = 0
    // array[1] = 1
    // array[2] = 25

    for (int i = 0; i < 3; i++)
    {
        int val;
        iss >> val;
        array[index] = val;
        index++;
    }

    return;
}

Grafo *readGrafo(string fileDirectory)
{

    Grafo *grafo;

    int numVertices = 0;

    string line;

    ifstream myfile(fileDirectory);

    if (myfile.is_open())
    {
        while (!myfile.eof())
        {
            getline(myfile, line);

            if (numVertices != 0)
            {
                int aresta[3];

                // Lê a linha e insere os vértices e peso
                // no array passado no parametro da função
                split(line, ' ', aresta);

                // Adiciona a aresta no grafo
                grafo->adicinarAdjacencia(aresta[0], aresta[1]);

                grafo->adicionarPeso(aresta[0], aresta[1], aresta[2]);
                grafo->adicionarPeso(aresta[1], aresta[0], aresta[2]);
            }
            else
            {
                // Chama o construtor do grafo passando o número de vértices como parâmetro
                numVertices = stoi(line);
                grafo = new Grafo(numVertices);
            }
        }

        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
        exit(1);
    }

    return grafo;
}

void escreveSaida(Grafo *grafo, string fileDirectory)
{
    //Abrindo arquivo de saída
    ofstream outfile(fileDirectory);

    grafo->imprimeGrafoSaida(outfile);

    outfile << "" << endl;

    outfile << "Numero de vertices: " << grafo->getNumVertices() << endl;

    outfile << "" << endl;

    outfile << "Numero de arestas: " << grafo->numArestas() << endl;

    outfile << "" << endl;

    outfile << "Grau médio do grafo: " << grafo->grauMedioDoGrafo() << endl;

    grafo->frequenciaRelativaGraus(outfile);
    
    outfile.close();
}
int main(int argc, char *argv[])
{

    Grafo *grafo;

    // Lê o grafo no arquivo de entrada
    grafo = readGrafo(argv[1]);

    int comando = -1;

    grafo->imprimeGrafo();

    while (comando != 0)
    {

        cout << endl
             << "=========== Menu ===========" << endl
             << endl;
        cout << "[1] Caminhamento em Largura" << endl;
        cout << "[2] Caminhamento em Profundidade" << endl;
        cout << "[3] Dijkstra: Caminho Mínimo" << endl;
        cout << "[4] Floyd: Caminho Mínimo" << endl;
        cout << "[5] Prim: Árvore Geradora" << endl;
        cout << "[6] Kruskal: Árvore Geradora Mínima;" << endl;
        cout << endl
             << "[0] Sair" << endl;
        cout << endl
             << "============================" << endl;

        cout << endl
             << "Escolha uma das operações do menu: ";
        cin >> comando;

        cout << endl;
        switch (comando)
        {
        case 1:
            // Realiza caminhamento em largura no grafo
            grafo->buscaLargura(0);
            break;
        case 2:
            // Realiza caminhamento em profundidade no grafo
             grafo->buscaProf(0);
            break;
        case 3:
            // Busca caminho mínimo por Dijkstra no grafo
            grafo->caminhoMinimoDijkstra(0);
            break;
        case 4:
            // Busca caminho mínimo por Floyd no grafo
            break;
        case 5:
            // Árvore Geradora por Prim no grafo
            grafo->arvoreGeradoraPrim();
            break;
        case 6:
            // Árvore Geradora Mínima por Kruskal no grafo
            grafo->arvoreGeradoraMinimaKruskal();
            break;

        default:
            comando = 0;
            break;
        }
    }

    cout << endl
         << "Encerrando programa..." << endl;
    cout << endl
         << "Obrigado pela preferência!" << endl;
    cout << "Volte sempre! ;)" << endl;

    grafo->imprimeGrafo();

    escreveSaida(grafo, argv[2]);

    delete grafo;

    system("pause");

    return 0;
}
