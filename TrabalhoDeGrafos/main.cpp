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
void split(string str, char separator, int array[], int size)
{
    istringstream iss;

    int index = 0;

    iss.str(str);

    // "0 1 25"
    // array[0] = 0
    // array[1] = 1
    // array[2] = 25

    for (int i = 0; i < size; i++)
    {
        int val;
        iss >> val;
        array[index] = val;
        index++;
    }

    return;
}

Grafo *leGrafoComPeso(string fileDirectory)
{
    Grafo *grafo;

    int numVertices = 0;

    string line;

    ifstream myfile(fileDirectory);

    int verticeLine = 0;

    bool matrizDeAdjacencia = false;

    if (myfile.is_open())
    {
        while (!myfile.eof())
        {
            getline(myfile, line);

            if (numVertices != 0)
            {

                // Verifica se já está na Matriz de Adjacências
                if (matrizDeAdjacencia)
                {

                    int *linhaMatriz = new int[numVertices];

                    // Lê a linha e insere os vértices e peso
                    // no array passado no parametro da função
                    split(line, ' ', linhaMatriz, numVertices);

                    // Adiciona todos os adjacentes de verticeLine
                    for (int i = 0; i < numVertices; i++)
                    {
                        // Se o valor na Matriz for igual a 1 e estiver em alguma posição triangulo superior
                        if (linhaMatriz[i] == 1 && i > verticeLine)
                        {
                            // Adiciona aresta no grafo
                            grafo->adicinarAdjacencia(verticeLine, i);

                            // Adiciona peso igual a 0
                            grafo->adicionarPeso(verticeLine, i, 1);
                            grafo->adicionarPeso(i, verticeLine, 1);
                        }
                    }

                    // Passa para o próximo vertice
                    verticeLine++;
                    delete[] linhaMatriz;
                }

                // Verifica se chegou na Matriz de Adjacências
                if (line.compare("*****************CONNECTIONS****************") == 1)
                {
                    matrizDeAdjacencia = true;
                }
            }
            else
            {

                if (!(line.compare("NumberOfNodes:") == 1))
                {
                    // Chama o construtor do grafo passando o número de vértices como parâmetro
                    numVertices = stoi(line);
                    grafo = new Grafo(numVertices);
                }
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
                split(line, ' ', aresta, 3);

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

    int leitura = -1;
    cout << endl
         << "=========== Arquivo de Leitura ===========" << endl
         << endl;
    cout << "[1] Leitura com peso nas arestas" << endl;
    cout << "[2] Leitura com peso nos vértices" << endl;
    cout << endl
         << "============================" << endl;

    cout << endl
         << "Escolha uma das operações do menu: ";
    cin >> leitura;

    // Lê o grafo no arquivo de entrada
    if (leitura == 1)
    {
        grafo = readGrafo(argv[1]);
    }
    else
    {

        grafo = leGrafoComPeso(argv[1]);
        leitura = 2;
    }

    int comando = -1;

    //grafo->imprimeGrafo();
    if (leitura == 2)
    {
        grafo->algoritmoGulosoSD();

        cout << "\n\nALFA: 0.1" << endl;
        for (int i = 0; i < 10; i++)
        {
            grafo->algoritmoGulosoRandomizado(0.1, i);
        }
        cout << "\n\nALFA: 0.2" << endl;
        for (int i = 0; i < 10; i++)
        {
            grafo->algoritmoGulosoRandomizado(0.2, i);
        }
        cout << "\n\nALFA: 0.3" << endl;
        for (int i = 0; i < 10; i++)
        {
            grafo->algoritmoGulosoRandomizado(0.3, i);
        }
        cout << "\n\nALFA: 0.5" << endl;
        for (int i = 0; i < 10; i++)
        {
            grafo->algoritmoGulosoRandomizado(0.5, i);
        }
        cout << "\n\nALFA: 0.7" << endl;
        for (int i = 0; i < 10; i++)
        {
            grafo->algoritmoGulosoRandomizado(0.7, i);
        }
    }

    while (comando != 0 && leitura == 1)
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
            grafo->buscaProf();
            break;
        case 3:
            // Busca caminho mínimo por Dijkstra no grafo
            int vertice;
            cout << "Escolha um valor entre 0 e " << grafo->getNumVertices() - 1 << ": " << endl;
            cin >> vertice;

            grafo->caminhoMinimoDijkstra(vertice);
            break;
        case 4:
            // Busca caminho mínimo por no grafo
            grafo->caminhoMinimoFloyd();
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


    escreveSaida(grafo, argv[2]);

    delete grafo;

    system("pause");

    return 0;
}
