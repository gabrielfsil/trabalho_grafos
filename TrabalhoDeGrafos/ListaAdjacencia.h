#ifndef ListaAdjacencia_H
#define ListaAdjacencia_H
#include "No.h"

class ListaAdjacencia
{
    public:
    ListaAdjacencia();
    ~ListaAdjacencia();
    int get(int k);
    void inserir(int val);
    void imprime();
    int tamanho();
    
private:
    No *primeiro;
};

#endif // ListaAdjacencia_H
