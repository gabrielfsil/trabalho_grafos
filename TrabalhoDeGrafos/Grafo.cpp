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
    cout<< "" <<endl;
    cout<< "Frequencia relativa de cada grau" <<endl;
    cout<< "" <<endl;

    for (int i = 0; i < numVertices; i++)
    {
        float frquencia = float (contadorDeGraus[i])/numVertices;
        frquencia = frquencia * 100;
        cout << "Grau " << i << ": " << frquencia << "%" << endl;
    }

    delete[] contadorDeGraus;
}
int Grafo::grauMedioDoGrafo()
{
    int somaDosGraus = 0;
    for (int i = 0; i < numVertices; i++)
    {
        somaDosGraus += vertices[i].tamanho();
    }
    return (somaDosGraus/numVertices);
}

bool existeAberto(bool abertos[], int numVertices){
    for(int i = 0; i < numVertices; i++){
        if(abertos[i]){
            return true;
        }
    }
    return false;
}

int menorDistanciaAberto(int estimativa[], bool abertos[], int numVertices){
    int menor;
    for(int i = 0; i<numVertices; i++){
        if(abertos[i]){
            menor = i;
            break;
        }
    }
    for(int i = menor+1; i<numVertices; i++){
        if(abertos[i] && estimativa[i] < estimativa[menor]){
            menor = i;
        }
    }
    return menor;
}

void Grafo::caminhoMinimoDijkstra(int origem)
{
    ///Preparando
    int* estimativa = new int[numVertices];
    int* precedentes = new int[numVertices];
    bool* abertos = new bool[numVertices];
    int subsequente;
    int aux;
    for(int i = 0; i < numVertices; i++){
        estimativa[i] = INT8_MAX/2;
        precedentes[i] = -1;
        abertos[i] = true;
    }
    ///Iniciando a origem
    estimativa[origem] = 0;
    precedentes[origem] = origem;
    abertos[origem] = false;
    for(int i = 0; i < vertices[origem].tamanho(); i++){
        aux = vertices[origem].get(i);
        estimativa[aux] = 1;
        precedentes[aux] = origem;
    }

    ///Dijkstra
    while (existeAberto(abertos,numVertices)){
        subsequente = menorDistanciaAberto(estimativa,abertos,numVertices);
        abertos[subsequente] = false;
        ///Relaxamento
        for(int i = 0; i<vertices[subsequente].tamanho(); i++){
            aux = vertices[subsequente].get(i);
            if(estimativa[subsequente] + 1 < estimativa[aux]){
                estimativa[aux] = estimativa[subsequente] + 1;
                precedentes[aux] = subsequente;
            }
        }

    }

    ///Imprimindo
    cout << "DIJKSTRA" << endl;
    for(int i = 0; i < numVertices; i++){
        cout << "Vértice " << i << " -> Distancia: " << estimativa[i] << " e Precedente: " << precedentes[i] << endl;
    }
    


    ///Encerrando
    delete [] estimativa;
    delete [] precedentes;
    delete [] abertos;

}

int Grafo::getNumVertices(){
    return numVertices;
}
