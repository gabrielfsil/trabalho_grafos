#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include "Grafo.h"
using namespace std;

void split(string str, char separator, int array[])
{
    istringstream iss;

    int index = 0;

    iss.str(str);

    // "0 1 25"
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

                split(line, ' ', aresta);

                // cout << aresta[0] << " - " << aresta[1] << endl;

                grafo->adicinarAdjacencia(aresta[0], aresta[1]);
            }
            else
            {
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

    grafo = readGrafo(argv[1]);

    // Grafo *grafo = new Grafo(3);
    // grafo->adicinarAdjacencia(0, 1);
    // grafo->adicinarAdjacencia(1, 2);
    // grafo->adicinarAdjacencia(2, 0);
    grafo->imprimeGrafo();

    delete grafo;

    return 0;
}
