#include "Grafo.h"
#include "ListaAdjacencia.h"
#include "No.h"
#include <iostream>

using namespace std;

Grafo::Grafo(int numVertices)
{
    Grafo::vertices = new ListaAdjacencia[numVertices];
    Grafo::numVertices = numVertices;

    Grafo::pesos = new int *[numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        Grafo::pesos[i] = new int[numVertices];
    }
}

Grafo::~Grafo()
{
    delete[] vertices;

    for (int i = 0; i < numVertices; i++)
    {
        delete[] pesos[i];
    }

    delete[] pesos;
}

void Grafo::adicinarAdjacencia(int vertice, int verticeAdjacente)
{

    Grafo::vertices[vertice].inserir(verticeAdjacente);
    Grafo::vertices[verticeAdjacente].inserir(vertice);
}

void Grafo::imprimeGrafo()
{
    for (int i = 0; i < numVertices; i++)
    {
        cout << "[" << i << "]: ";
        vertices[i].imprime();
        cout << endl;
    }
}

void Grafo::adicionarPeso(int vertice, int verticeAdjacente, int peso)
{

    Grafo::pesos[vertice][verticeAdjacente] = peso;
}

void Grafo::imprimirMatrizPeso()
{

    for (int i = -1; i < numVertices; i++)
    {

        if (i == -1)
        {
            cout << "    ";
            for (int j = 0; j < numVertices; j++)
            {

                cout << j << "   ";
            }

            cout << endl;
        }
        else
        {
            cout << i << " | ";

            for (int j = 0; j < numVertices; j++)
            {

                cout << pesos[i][j] << "  ";
            }

            cout << endl;
        }
    }
}

void Grafo::arvoreGeradoraPrim()
{
    int i = -1;
    bool tDiferenteDeN = true;
    // Dado um grafo G = {N,M} e D = [d]ij a matriz de pesos de G

    // Escolher um vértice i contido em N

    cout << "Os vertices do grafo variam de 0 até " << numVertices - 1 << endl;
    cout << "Digite o vertice que deseja iniciar a árvore: ";
    cin >> i;

    // Enquanto o valor do vértice for inválido
    while (i == -1 || i > numVertices - 1)
    {   
        cout << endl << " ---- VÉRTICE INVÁLIDO ---- " << endl << endl; 
        cout << "Os vertices do grafo variam de 0 até " << numVertices - 1 << endl;
        cout << "Digite o vertice que deseja iniciar a árvore: ";
        cin >> i;
    }

    // T um conjunto de vertices composto, inicialmente, por { i }
    int *conjuntoT = new int[numVertices];

    // V um conjunto de vertices composto, inicialmente, por N - { i }
    int *conjuntoV = new int[numVertices];
    for (int a = 0; a < numVertices; a++)
    {
        if (a == i)
        {
            conjuntoT[a] = i;
            conjuntoV[a] = -1;
        }
        else
        {
            conjuntoT[a] = -1;
            conjuntoV[a] = a;
        }
    }
    // Tmin um conjunto de arestas, inicialmente, vazio
    ListaAdjacencia *conjuntoTmin = new ListaAdjacencia[numVertices];

    // Enquanto T é diferente de N, ou seja, enquanto todos os vertices ainda não forem percorridos fazer:
    while (tDiferenteDeN)
    {

        // Encontrar uma aresta (j,k) contida no conjunto M, de forma que j pertença a T e k pertença a V e [d]jk seja mínimo
        int menorValor = -1;
        int jMenor = -1;
        int kMenor = -1;
        bool tIgualAN = true;

        for (int j = 0; j < numVertices; j++)
        {

            if (conjuntoT[j] != -1)
            {

                for (int k = 0; k < numVertices; k++)
                {

                    if (conjuntoV[k] != -1)
                    {

                        if ((menorValor > pesos[j][k] && j != k && pesos[j][k] != 0) || menorValor == -1)
                        {
                            menorValor = pesos[j][k];
                            jMenor = j;
                            kMenor = k;
                        }
                    }
                }
            }
            else
            {
                tIgualAN = false;
            }
        }

        if (kMenor != -1 && jMenor != -1)
        {

            // Adicionar k em T
            conjuntoT[kMenor] = conjuntoV[kMenor];

            // Remover o K de V
            conjuntoV[kMenor] = -1;

            // Adicionar a aresta (j,k) no Tmin
            conjuntoTmin[jMenor].inserir(kMenor);
        }

        // Se o conjunto T é igual ao conjunto N de todos os vertices
        if (tIgualAN)
        {
            tDiferenteDeN = false;
        }
    }
    cout << endl << "*******************************************" << endl;

    cout << endl
         << "Árvore Geradora de Prim no vértice " << i << endl
         << endl;

    cout << "Lista de Adjacência da Árvore" << endl;

    // Finaliza algoritmo
    for (int i = 0; i < numVertices; i++)
    {
        cout << "[" << i << "]:";
        conjuntoTmin[i].imprime();
        cout << endl;
    }

    cout << endl
         << "*******************************************" << endl;

    delete[] conjuntoT;
    delete[] conjuntoV;
    delete[] conjuntoTmin;
}