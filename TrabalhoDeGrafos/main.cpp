#include <iostream>
#include <fstream>
#include <string>
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


  string allFile = readFile("/home/joao_lima/Git/trabalho_grafos/ExemploInstancias.txt");
  return 0;
}
