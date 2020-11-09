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
        void imprimeGrafo();
        void imprimeGrafoSaida(ofstream &outfile);
        void adicionarPeso(int vertice, int verticeAdjacente, int peso);
        void imprimirMatrizPeso();
        void arvoreGeradoraPrim();
        void arvoreGeradoraMinimaKruskal();
        int numArestas();
        int grauMedioDoGrafo();
        void frequenciaRelativaGraus(ofstream &outfile);
        void caminhoMinimoDijkstra(int origem);
        int getNumVertices();
        void buscaLargura(int atual);
    private:
        ListaAdjacencia* vertices;
        int numVertices;
        int** pesos;
};

#endif // GRAFO_H
