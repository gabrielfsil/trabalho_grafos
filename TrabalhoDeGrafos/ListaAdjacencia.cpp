#include <iostream>
#include <cstdlib>
#include "ListaAdjacencia.h"
#include "No.h"

using namespace std;

ListaAdjacencia::ListaAdjacencia()
{
    primeiro = NULL;
}

ListaAdjacencia::~ListaAdjacencia()
{
    No *p = primeiro;
    while(p != NULL)
    {
        No *t = p->getProx();
        delete p;
        p = t;
    }
}

int ListaAdjacencia::get(int k){
    No *p = primeiro;
    int i = 0;
    while(i < k && p != NULL)
    {
        i++;
        p = p->getProx();
    }
    if(p == NULL)
    {
        exit(1);
    }
    else
        return p->getInfo();
}

void ListaAdjacencia::inserir(int val){
    No* p = new No(val);
    p->setProx(NULL);
    if(primeiro == NULL){
        primeiro = p;
    } else {
        No* t = primeiro;
        while(t->getProx() != NULL){
            t = t->getProx();
        }
        t->setProx(p);
    }
}

void ListaAdjacencia::imprime(){
    No* p = primeiro;
    while(p != NULL){
        cout << p->getInfo() << " -> ";
        p = p->getProx();
    }
}