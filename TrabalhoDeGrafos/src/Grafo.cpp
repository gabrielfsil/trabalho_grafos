#include "Grafo.h"

Grafo::Grafo(int numVertices)
{
    listaVertices = new No[numVertices];
}

Grafo::~Grafo()
{
    delete [] listaVertices;
}
