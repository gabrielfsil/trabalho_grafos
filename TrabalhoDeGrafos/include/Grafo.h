#ifndef GRAFO_H
#define GRAFO_H
#include "No.h"

class Grafo
{
    public:
        Grafo(int numVertices);
        ~Grafo();

    private:
        No* listaVertices;

};

#endif // GRAFO_H
