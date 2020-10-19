#ifndef GRAFO_H
#define GRAFO_H
#include "ListaAdjacencia.h"


class Grafo
{
    public:
        Grafo(int numVertices);
        ~Grafo();
        void adicinarAdjacencia(int vertice, int verticeAdjacente);
        void imprimeGrafo();
        void frequenciaRelativaGraus();
    private:
        ListaAdjacencia* vertices;
        int numVertices;
};

#endif // GRAFO_H
