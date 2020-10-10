#include "Grafo.h"
#include "ListaAjacencia.h"
Grafo::Grafo(int numVertices)
{
    Grafo::vertices = new ListaAjacencia[numVertices];
}

Grafo::~Grafo()
{
    delete [] vertices;
}

void Grafo::adicinarAresta(int vertice, int verticeAdjacente){
    Grafo::vertices[vertice].inserir(verticeAdjacente);
}
