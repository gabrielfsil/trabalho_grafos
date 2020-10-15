#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include<stdlib.h>
#include "Grafo.h"
using namespace std;

string readFile(string fileDirectory){
    string allFile = "";
    string line;
    ifstream myfile (fileDirectory);
    if (myfile.is_open()){
        while (! myfile.eof() )
        {
            getline (myfile,line);
            if(allFile != "")
                allFile = allFile + "\n" + line;
            else
                allFile = allFile + line;
        }
    myfile.close();
    } else {
        cout << "Unable to open file";
        exit(1);
    }
    cout << allFile;
    return allFile;
}


int main () {

  Grafo* grafo = new Grafo(3);
  grafo->adicinarAdjacencia(0,1);
  grafo->adicinarAdjacencia(1,2);
  grafo->adicinarAdjacencia(2,0);
  grafo->imprimeGrafo();
  
  delete grafo;
  return 0;
}
