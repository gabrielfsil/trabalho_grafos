#ifndef GRAFO_H
#define GRAFO_H
#include "ListaAjacencia.h"


class Grafo
{
    public:
        Grafo(int numVertices);
        ~Grafo();
        void adicinarAresta(int vertice, int verticeAdjacente);
    private:
        ListaAjacencia* vertices;
};

#endif // GRAFO_H
