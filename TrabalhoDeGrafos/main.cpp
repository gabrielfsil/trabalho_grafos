#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include "Grafo.h"
using namespace std;

string *split(string str, char separator)
{

    int start = 0;
    int end = str.length();

    string *array = new string[end];

    int index = 0;

    // "0 1 25"
    for (int i = 0; i < end; i++)
    {

        if (str[i] == separator && str[i - 1] != separator)
        {

            array[index] = str.substr(start, i - start);

            start = i + 1;
            index++;
        }
    }

    array[index] = str.substr(start, end - 1);

    return array;
}

Grafo* readGrafo(string fileDirectory)
{

    Grafo *grafo;

    int numVertices = 0;

    string line;

    ifstream myfile(fileDirectory);

    string * aresta;

    if (myfile.is_open())
    {
        while (!myfile.eof())
        {
            getline(myfile, line);

            if (numVertices != 0)
            {

                aresta = split(line, ' ');
                grafo->adicinarAdjacencia(std::stoi(aresta[0]), std::stoi(aresta[1]));
                
            }
            else
            {
                numVertices = std::stoi(line);
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

    delete [] aresta;

    return grafo;
}

int main(int argc, char *argv[])
{

    Grafo* grafo;
    grafo = readGrafo(argv[1]);

    // Grafo *grafo = new Grafo(3);
    // grafo->adicinarAdjacencia(0, 1);
    // grafo->adicinarAdjacencia(1, 2);
    // grafo->adicinarAdjacencia(2, 0);
    grafo->imprimeGrafo();

    delete grafo;

    return 0;
}
