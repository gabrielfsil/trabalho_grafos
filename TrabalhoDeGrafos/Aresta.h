#ifndef ARESTA_H
#define ARESTA_H

class Aresta
{

private:
    int vertice;
    int verticeAdjacente;
    int peso;

public:
    Aresta();
    Aresta(int vertice, int verticeAdjcente, int peso);
    ~Aresta();
    void setAresta(int vertice, int verticeAdjcente, int peso);
    int getPeso() { return peso; };
    int getVertice() { return vertice; };
    int getVerticeAdjacente() { return verticeAdjacente; };
};

#endif // ARESTA_H