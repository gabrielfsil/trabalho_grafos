#include "Grafo.h"
#include "ListaAdjacencia.h"
#include "Aresta.h"
#include "No.h"
#include <iostream>
#include <fstream>



using namespace std;

Grafo::Grafo(int numVertices)
{
    Grafo::vertices = new ListaAdjacencia[numVertices];
    Grafo::numVertices = numVertices;

    Grafo::pesos = new int *[numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        Grafo::pesos[i] = new int[numVertices];
    }
}

Grafo::~Grafo()
{
    delete[] vertices;

    for (int i = 0; i < numVertices; i++)
    {
        delete[] pesos[i];
    }

    delete[] pesos;
}

void Grafo::adicinarAdjacencia(int vertice, int verticeAdjacente)
{

    Grafo::vertices[vertice].inserir(verticeAdjacente);
    Grafo::vertices[verticeAdjacente].inserir(vertice);
}

int Grafo::numArestas()
{
    int somaGrau = 0;
    int numArestas=0;
    for (int i = 0; i < numVertices; i++)
    {
        somaGrau += vertices[i].tamanho();
    }
    numArestas = somaGrau/2;
    return numArestas;
}

void Grafo::imprimeGrafo()
{
    cout << "Grafo: " << endl;
    for (int i = 0; i < numVertices; i++)
    {
        cout << "[" << i << "]: ";
        vertices[i].imprime();
        cout << endl;
    }

}

void Grafo::imprimeGrafoSaida(ofstream &outfile)
{
    outfile << "Grafo: " << endl;
    for (int i = 0; i < numVertices; i++)
    {
        outfile << "[" << i << "]: ";
        vertices[i].imprimeSaida(outfile);
        outfile << endl;
    }

}

void Grafo::frequenciaRelativaGraus(ofstream &outfile)
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
    outfile << "" <<endl;
    outfile << "Frequencia relativa de cada grau" <<endl;
    outfile << "" <<endl;

    for (int i = 0; i < numVertices; i++)
    {
        float frquencia = float (contadorDeGraus[i])/numVertices;
        frquencia = frquencia * 100;
        outfile << "Grau " << i << ": " << frquencia << "%" << endl;
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
void Grafo::adicionarPeso(int vertice, int verticeAdjacente, int peso)
{

    Grafo::pesos[vertice][verticeAdjacente] = peso;
}

void Grafo::imprimirMatrizPeso()
{

    for (int i = -1; i < numVertices; i++)
    {

        if (i == -1)
        {
            cout << "    ";
            for (int j = 0; j < numVertices; j++)
            {

                cout << j << "   ";
            }

            cout << endl;
        }
        else
        {
            cout << i << " | ";

            for (int j = 0; j < numVertices; j++)
            {

                cout << pesos[i][j] << "  ";
            }

            cout << endl;
        }
    }
}

void Grafo::arvoreGeradoraPrim()
{
    int i = -1;
    bool tDiferenteDeN = true;
    // Dado um grafo G = {N,M} e D = [d]ij a matriz de pesos de G

    // Escolher um vértice i contido em N

    cout << "Os vertices do grafo variam de 0 até " << numVertices - 1 << endl;
    cout << "Digite o vertice que deseja iniciar a árvore: ";
    cin >> i;

    // Enquanto o valor do vértice for inválido
    while (i == -1 || i > numVertices - 1)
    {
        cout << endl
             << " ---- VÉRTICE INVÁLIDO ---- " << endl
             << endl;
        cout << "Os vertices do grafo variam de 0 até " << numVertices - 1 << endl;
        cout << "Digite o vertice que deseja iniciar a árvore: ";
        cin >> i;
    }

    // T um conjunto de vertices composto, inicialmente, por { i }
    int *conjuntoT = new int[numVertices];

    // V um conjunto de vertices composto, inicialmente, por N - { i }
    int *conjuntoV = new int[numVertices];
    for (int a = 0; a < numVertices; a++)
    {
        if (a == i)
        {
            conjuntoT[a] = i;
            conjuntoV[a] = -1;
        }
        else
        {
            conjuntoT[a] = -1;
            conjuntoV[a] = a;
        }
    }
    // Tmin um conjunto de arestas, inicialmente, vazio
    ListaAdjacencia *conjuntoTmin = new ListaAdjacencia[numVertices];

    // Enquanto T é diferente de N, ou seja, enquanto todos os vertices ainda não forem percorridos fazer:
    while (tDiferenteDeN)
    {

        // Encontrar uma aresta (j,k) contida no conjunto M, de forma que j pertença a T e k pertença a V e [d]jk seja mínimo
        int menorValor = -1;
        int jMenor = -1;
        int kMenor = -1;
        bool tIgualAN = true;

        for (int j = 0; j < numVertices; j++)
        {

            if (conjuntoT[j] != -1)
            {

                for (int k = 0; k < numVertices; k++)
                {

                    if (conjuntoV[k] != -1)
                    {

                        if ((menorValor > pesos[j][k] && j != k && pesos[j][k] != 0) || menorValor == -1)
                        {
                            menorValor = pesos[j][k];
                            jMenor = j;
                            kMenor = k;
                        }
                    }
                }
            }
            else
            {
                tIgualAN = false;
            }
        }

        if (kMenor != -1 && jMenor != -1)
        {

            // Adicionar k em T
            conjuntoT[kMenor] = conjuntoV[kMenor];

            // Remover o K de V
            conjuntoV[kMenor] = -1;

            // Adicionar a aresta (j,k) no Tmin
            conjuntoTmin[jMenor].inserir(kMenor);
            conjuntoTmin[kMenor].inserir(jMenor);
        }

        // Se o conjunto T é igual ao conjunto N de todos os vertices
        if (tIgualAN)
        {
            tDiferenteDeN = false;
        }
    }
    cout << endl
         << "*******************************************" << endl;

    cout << endl
         << "Árvore Geradora de Prim no vértice " << i << endl
         << endl;

    cout << "Lista de Adjacência da Árvore" << endl;

    // Finaliza algoritmo
    for (int i = 0; i < numVertices; i++)
    {
        cout << "[" << i << "]:";
        conjuntoTmin[i].imprime();
        cout << endl;
    }

    cout << endl
         << "*******************************************" << endl;

    delete[] conjuntoT;
    delete[] conjuntoV;
    delete[] conjuntoTmin;
}

void swap(Aresta *xp, Aresta *yp)
{
    Aresta temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(Aresta arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j].getPeso() > arr[j + 1].getPeso())
                swap(&arr[j], &arr[j + 1]);
}

void Grafo::arvoreGeradoraMinimaKruskal()
{

    // Ler um grafo G=(N,M), onde D=[d]ij é a matriz de pesos das arestas do grafo

    // Ordenar as arestas em ordem não crescente em um H vetor
    // H = [h]i , i = 1,2,3,...,m
    int numMaxArestas = (numVertices * (numVertices - 1) / 2);
    Aresta *listAresta = new Aresta[numMaxArestas];

    // Vetor de subárvores do grafo
    int *subArvores = new int[numVertices];

    int indexH = 0;
    // Percorre a lista de adjacência
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < i; j++)
        {

            listAresta[indexH] = Aresta(i, j, pesos[i][j]);
            indexH++;
        }
        subArvores[i] = i;
    }

    bubbleSort(listAresta, indexH);

    // T é o conjunto de arestas da árvore em construção
    ListaAdjacencia *conjuntoT = new ListaAdjacencia[numVertices];

    // i é o contador
    int i = 0;

    // Index do vetor de arestas
    int a = 0;

    // Enquanto T não combrir todos os vértices continua a executar o loop
    while (i < numVertices - 1)
    {
        // Seja (u,v) a próxima aresta de listAresta
        Aresta ArestaUV = listAresta[a];

        // Verifica se pertencem a mesma subárvore
        if (subArvores[ArestaUV.getVertice()] != subArvores[ArestaUV.getVerticeAdjacente()])
        {

            // Adicionar a aresta (u,v) ao conjunto T
            conjuntoT[listAresta[a].getVertice()].inserir(listAresta[a].getVerticeAdjacente());
            conjuntoT[listAresta[a].getVerticeAdjacente()].inserir(listAresta[a].getVertice());

            cout << "Adicionando aresta: ";
            cout << "( " << ArestaUV.getVertice() << " , " << ArestaUV.getVerticeAdjacente() << " ) , peso = " << ArestaUV.getPeso() << endl;

            int valorDaSubArvore;

            // Verifica qual o menor vértice para alterar todos que pertencem a subárvore com seu valor
            if (ArestaUV.getVertice() < ArestaUV.getVerticeAdjacente())
            {
                valorDaSubArvore = subArvores[ArestaUV.getVerticeAdjacente()];
            }
            else
            {
                valorDaSubArvore = subArvores[ArestaUV.getVertice()];
            }

            // Atualiza o vetor de subárvores
            for (int j = 0; j < numVertices; j++)
            {
                // Verifica qual o menor vértice para alterar todos que pertencem a subárvore com seu valor
                if (ArestaUV.getVertice() < ArestaUV.getVerticeAdjacente())
                {
                    // Se o valor do vetor na posição "j" pertence a subarvore ele é atualizado com o valor do menor vérice
                    if (subArvores[j] == valorDaSubArvore)
                    {

                        subArvores[j] = ArestaUV.getVertice();
                    }
                }
                else
                {
                    // Se o valor do vetor na posição "j" pertence a subarvore ele é atualizado com o valor do menor vérice
                    if (subArvores[j] == valorDaSubArvore)
                    {

                        subArvores[j] = ArestaUV.getVerticeAdjacente();
                    }
                }
            }

            i++;
        }

        // Acrescenta no iterador i do vetor H de arestas
        a++;
    }

    // Escrever Árvore Geradora Mínima formada pelas arestas do conjunto T
    cout << endl
         << "*******************************************" << endl;

    cout << endl
         << "Árvore Geradora Mínima de Kruskal" << endl
         << endl;

    cout << "Lista de Adjacência da Árvore" << endl;

    // Finaliza algoritmo
    for (int i = 0; i < numVertices; i++)
    {
        cout << "[" << i << "]:";
        conjuntoT[i].imprime();
        cout << endl;
    }

    cout << endl
         << "*******************************************" << endl;
    delete[] conjuntoT;
    delete[] listAresta;
}

void Grafo::imprimeUmaMatriz(int **matriz)
{
    for (int i = -1; i < numVertices; i++)
    {
        if (i == -1)
        {
            cout << "    ";
            for (int j = 0; j < numVertices; j++)
            {

                cout << j << "   ";
            }

            cout << endl;
        }
        else
        {
            cout << i << " | ";

            for (int j = 0; j < numVertices; j++)
            {
                if(!(existeAdjacencia(i,j))){
                    cout << "-" << "  ";

                }
               else{
                    cout << matriz[i][j] << " ";
               }
            }

            cout << endl;
        }
    }
    
}

bool Grafo::existeAdjacencia(int i, int j)
{
    for(int k=0; k< vertices[i].tamanho(); k++){
        if(vertices[i].get(k)== j){
            return true;
        }
    }
    return false;
}

void Grafo::caminhoMinimoFloyd()
{
    //Matriz L guardando todas as distâncias entre os vértices (peso das arestas)
    int ** L = pesos;
    //Vértice k = intermediário por onde passamos para percorrer um caminho entre os vértics i e j
    int i, j, k;

    int infinito = INT8_MAX;

    int maior =0;
    //tratando matriz de pesos para remover lixo de memória
    for(int i =0; i<numVertices;i++)
    {
        for(j=0;j<numVertices; j++)
        {
            if(!existeAdjacencia(i,j))
            {
                L[i][j] = infinito;
            }
        }
    }

    //implementação alogritmo de Floyd
    for(k =0; k <numVertices; k++)
    {
        for(i=0; i<numVertices; i++)
        {
            for(j=0; j<numVertices; j++)
            {
                if(L[i][k] < infinito && L[k][j] < infinito)
                {
                    if(L[i][j] > (L [i][k] + L[k][j]))
                        L[i][j] = L [i][k] + L[k][j];
                }     
            }
        }
    }

    //Imprimindomenores caminhos para cada par de vértices
    imprimeUmaMatriz(L);
    
}

