#include "Grafo.h"
#include "ListaAdjacencia.h"
#include <iostream>

using namespace std;

Grafo::Grafo(int numVertices)
{
    Grafo::vertices = new ListaAdjacencia[numVertices];
    Grafo::numVertices = numVertices;
}

Grafo::~Grafo()
{
    delete[] vertices;
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
