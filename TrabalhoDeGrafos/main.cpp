#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include "Grafo.h"
using namespace std;

// Lê a aresta do grafo e separa os vértices e o peso em um array de 3 posições
// Transforma o formato string do arquivo em um tipo int
// array [] = [ Vértice, Vértice Adjacente, Peso ]
void split(string str, char separator, int array[])
{
    istringstream iss;

    int index = 0;

    iss.str(str);

    // "0 1 25"
    // array[0] = 0
    // array[1] = 1
    // array[2] = 25

    for (int i = 0; i < 3; i++)
    {
        int val;
        iss >> val;
        array[index] = val;
        index++;
        
    }
    
    return;

}

Grafo *readGrafo(string fileDirectory)
{

    Grafo *grafo;

    int numVertices = 0;

    string line;

    ifstream myfile(fileDirectory);

    if (myfile.is_open())
    {
        while (!myfile.eof())
        {
            getline(myfile, line);

            if (numVertices != 0)
            {
                int aresta[3];

                // Lê a linha e insere os vértices e peso 
                // no array passado no parametro da função
                split(line, ' ', aresta);

                // Adiciona a aresta no grafo
                grafo->adicinarAdjacencia(aresta[0], aresta[1]);
            }
            else
            {
                // Chama o construtor do grafo passando o número de vértices como parâmetro
                numVertices = stoi(line);
                grafo = new Grafo(numVertices);

            }
        }

        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
        exit(1);
    }

    return grafo;
}

int main(int argc, char *argv[])
{

    Grafo *grafo;

    // Lê o grafo no arquivo de entrada
    grafo = readGrafo(argv[1]);

    grafo->imprimeGrafo();
    cout << "Grau médio do Grafo: " << grafo->grauMedioDoGrafo() << endl;

    delete grafo;

    return 0;
    
}
