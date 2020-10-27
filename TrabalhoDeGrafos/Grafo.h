#ifndef GRAFO_H
#define GRAFO_H
#include "ListaAdjacencia.h"
#include <fstream>
using namespace std;


class Grafo
{
    public:
        Grafo(int numVertices);
        ~Grafo();
        void adicinarAdjacencia(int vertice, int verticeAdjacente);
        void imprimeGrafo(ofstream &outfile);
        void frequenciaRelativaGraus(ofstream &outfile);
        int grauMedioDoGrafo();
        void caminhoMinimoDijkstra(int origem);
    private:
        ListaAdjacencia* vertices;
        int numVertices;
};

#endif // GRAFO_H
