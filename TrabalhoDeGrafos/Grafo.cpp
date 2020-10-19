#include "Grafo.h"
#include "ListaAdjacencia.h"
#include <iostream>

using namespace std;

Grafo::Grafo(int numVertices)
{
    Grafo::vertices = new ListaAdjacencia[numVertices];
    Grafo::numVertices = numVertices;
}

Grafo::~Grafo()
{
    delete[] vertices;
}

void Grafo::adicinarAdjacencia(int vertice, int verticeAdjacente)
{

    Grafo::vertices[vertice].inserir(verticeAdjacente);
    Grafo::vertices[verticeAdjacente].inserir(vertice);
    
}

void Grafo::imprimeGrafo()
{
    for (int i = 0; i < numVertices; i++)
    {
        cout << "[" << i << "]: ";
        vertices[i].imprime();
        cout << endl;
    }

}

void Grafo::frequenciaRelativaGraus()
{
   
    //vetor para guardar a quantidade de vezes que o grau de um vértice aparece
    //considerando que o grau máximo de um vértice é N-1
    int * contadorDeGraus = new int [numVertices];

    //inicializando vetor com 0

    for(int i = 0; i<=numVertices; i++)
    {
      contadorDeGraus[i] = 0;
    }

    //cada posição do contador de graus é o grau em si
    //a função tamanho retorna o grau do vértice, então adicionamos 1 ao vetor nessa posição
 

    for (int i = 0; i < numVertices; i++)
    {
        //cout << contadorDeGraus[i] << endl;
       int grauDoVertice = vertices[i].tamanho();
       contadorDeGraus[grauDoVertice] = contadorDeGraus[grauDoVertice] + 1;
    }
    
    //assim temos as frequências absolutas, depois cada uma é dividida pela quantidade de nós
    //então temos a frequência relativa de cada grau
    for (int i = 0; i < numVertices; i++)
    {
        float frquencia = float (contadorDeGraus[i])/numVertices;
        frquencia = frquencia * 100;
        cout << "Frequencia relativa para grau " << i << ": " << frquencia << "%" << endl;
    }
}