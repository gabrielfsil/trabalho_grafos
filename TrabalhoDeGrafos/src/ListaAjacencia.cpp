#include <iostream>
#include <cstdlib>
#include "ListaAjacencia.h"
#include "No.h"

ListaAjacencia::ListaAjacencia()
{
    primeiro = NULL;
}

ListaAjacencia::~ListaAjacencia()
{
    No *p = primeiro;
    while(p != NULL)
    {
        No *t = p->getProx();
        delete p;
        p = t;
    }
}

int ListaAjacencia::get(int k){
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

void ListaAjacencia::inserir(int val){
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
