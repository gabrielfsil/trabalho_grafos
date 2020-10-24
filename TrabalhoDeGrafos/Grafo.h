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
        int grauMedioDoGrafo();
        void caminhoMinimoDijkstra(int origem);
        int getNumVertices();
    private:
        ListaAdjacencia* vertices;
        int numVertices;
};

#endif // GRAFO_H
