#include "Aresta.h"

Aresta::Aresta()
{
    Aresta::vertice = -1;
    Aresta::verticeAdjacente = -1;
    Aresta::peso = -1;
}

Aresta::Aresta(int vertice, int verticeAdjacente, int peso)
{

    Aresta::vertice = vertice;
    Aresta::verticeAdjacente = verticeAdjacente;
    Aresta::peso = peso;
}

void Aresta::setAresta(int vertice, int verticeAdjacente, int peso)
{

    Aresta::vertice = vertice;
    Aresta::verticeAdjacente = verticeAdjacente;
    Aresta::peso = peso;
}

Aresta::~Aresta()
{
}