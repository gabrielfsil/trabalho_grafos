#ifndef LISTAAJACENCIA_H
#define LISTAAJACENCIA_H
#include "No.h"

class ListaAjacencia
{
    public:
    ListaAjacencia();
    ~ListaAjacencia();
    int get(int k);
    void inserir(int val);

private:
    No *primeiro;
};

#endif // LISTAAJACENCIA_H
