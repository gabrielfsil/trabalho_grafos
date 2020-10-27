#ifndef ListaAdjacencia_H
#define ListaAdjacencia_H
#include "No.h"
#include <fstream>
using namespace std;

class ListaAdjacencia
{
    public:
        ListaAdjacencia();
        ~ListaAdjacencia();
        int get(int k);
        void inserir(int val);
        void imprime(ofstream &outfile);
        int tamanho();
    private:
        No *primeiro;
};

#endif // ListaAdjacencia_H
