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
        void adicionarPeso(int vertice, int verticeAdjacente, int peso);
        void imprimirMatrizPeso();
        void arvoreGeradoraPrim();
        void arvoreGeradoraMinimaKruskal();
        int numArestas();

        void frequenciaRelativaGraus();
        int grauMedioDoGrafo();
        void caminhoMinimoDijkstra(int origem);
    private:
        ListaAdjacencia* vertices;
        int numVertices;
        int** pesos;
};

#endif // GRAFO_H
