#include "Grafo.h"
#include "ListaAdjacencia.h"
#include "Aresta.h"
#include "No.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>  
#include <math.h>
#include <thread>
#include <chrono> 



#include <list>

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
    int numArestas = 0;
    for (int i = 0; i < numVertices; i++)
    {
        somaGrau += vertices[i].tamanho();
    }
    numArestas = somaGrau / 2;
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
    int *contadorDeGraus = new int[numVertices];

    //inicializando vetor com 0

    for (int i = 0; i <= numVertices; i++)
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
    outfile << "" << endl;
    outfile << "Frequencia relativa de cada grau" << endl;
    outfile << "" << endl;

    for (int i = 0; i < numVertices; i++)
    {
        float frquencia = float(contadorDeGraus[i]) / numVertices;
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
    return (somaDosGraus / numVertices);
}

bool existeAberto(bool abertos[], int numVertices)
{
    for (int i = 0; i < numVertices; i++)
    {
        if (abertos[i])
        {
            return true;
        }
    }
    return false;
}

int menorDistanciaAberto(int estimativa[], bool abertos[], int numVertices)
{
    int menor;
    for (int i = 0; i < numVertices; i++)
    {
        if (abertos[i])
        {
            menor = i;
            break;
        }
    }
    for (int i = menor + 1; i < numVertices; i++)
    {
        if (abertos[i] && estimativa[i] < estimativa[menor])
        {
            menor = i;
        }
    }
    return menor;
}

void Grafo::caminhoMinimoDijkstra(int origem)
{
    ///Preparando
    int *estimativa = new int[numVertices];
    int *precedentes = new int[numVertices];
    bool *abertos = new bool[numVertices];
    int subsequente;
    int aux;
    for (int i = 0; i < numVertices; i++)
    {
        estimativa[i] = INT8_MAX / 2;
        precedentes[i] = -1;
        abertos[i] = true;
    }
    ///Iniciando a origem
    estimativa[origem] = 0;
    precedentes[origem] = origem;
    abertos[origem] = false;
    for (int i = 0; i < vertices[origem].tamanho(); i++)
    {
        aux = vertices[origem].get(i);
        estimativa[aux] = 1;
        precedentes[aux] = origem;
    }

    ///Dijkstra
    while (existeAberto(abertos, numVertices))
    {
        subsequente = menorDistanciaAberto(estimativa, abertos, numVertices);
        abertos[subsequente] = false;
        ///Relaxamento
        for (int i = 0; i < vertices[subsequente].tamanho(); i++)
        {
            aux = vertices[subsequente].get(i);
            if (estimativa[subsequente] + 1 < estimativa[aux])
            {
                estimativa[aux] = estimativa[subsequente] + 1;
                precedentes[aux] = subsequente;
            }
        }
    }

    ///Imprimindo
    cout << "DIJKSTRA" << endl;
    for (int i = 0; i < numVertices; i++)
    {
        cout << "Vértice " << i << " -> Distancia: " << estimativa[i] << " e Precedente: " << precedentes[i] << endl;
    }

    ///Encerrando
    delete[] estimativa;
    delete[] precedentes;
    delete[] abertos;
}

int Grafo::getNumVertices()
{
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

                if(existeAdjacencia(i,j))
                {
                    cout << pesos[i][j] << "  ";
                }
                else
                {
                    cout << '-' << "  ";
                }
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
    while (i <= -1 || i > numVertices - 1)
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

                        // pesos[j][k] == 0 significa que a aresta (j,k) não existe
                        if ((menorValor != -1 && menorValor > pesos[j][k] && j < k && pesos[j][k] != 0) ||( menorValor == -1 &&  pesos[j][k] != 0))
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

            cout << jMenor << " -> " << kMenor << endl;

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
    int numMaxArestas = (numVertices * (numVertices - 1) / 2) * 2;
    Aresta *listAresta = new Aresta[numMaxArestas];

    // Vetor de subárvores do grafo
    int *subArvores = new int[numVertices];

    int indexH = 0;
    // Percorre a lista de adjacência
    for (int i = 0; i < numVertices; i++)
    {
        int j = 0;
        int verticeAdjacente = vertices[i].get(j);

        while (verticeAdjacente != -1)
        {
            // Matriz Triangulo Superior
            if (i < verticeAdjacente)
            {
                listAresta[indexH] = Aresta(i, verticeAdjacente, pesos[i][verticeAdjacente]);
                indexH++;
            }

            j++;
            verticeAdjacente = vertices[i].get(j);
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

        // Acrescenta + 2 no iterador i do vetor H de arestas, porque as arestas estão duplicadas (u,v) = (v,u)
        a = a + 1;
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

void Grafo::imprimeMatriz(int **matriz, int maiorValor, int menorNegativo)
{

    int digitos = 1;
    int dezena = 10;
    int infinito = INT8_MAX;

   if(menorNegativo!=0)
   {
        while((menorNegativo/dezena)!=0)
        {
            digitos++;
            dezena = dezena * 10;
        }
        digitos++;
    
   }
   else
   {
       while((maiorValor/dezena)!=0)
    {
        digitos++;
        dezena = dezena * 10;
    }
    
   }
   
    for (int i = -1; i < numVertices; i++)
    {
        if (i == -1)
        {
            cout << "    ";
            for (int j = 0; j < numVertices; j++)
            {

               cout << setw (digitos+1);
               cout << j ;
               cout << "  ";

            }

            cout << endl;
        }
        else
        {
            cout << i << " | ";

            for (int j = 0; j < numVertices; j++)
            {
                cout << "[" << setw(digitos);

                if(matriz[i][j]==infinito){
                    cout << "X" << "]";

                }
               else{
                    cout << matriz[i][j] << "] ";
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

    //variavel pra guardar o maior valor da matriz para fim de formataçãp
    //na impressão
    int maior =0; int menor = 0;

    int infinito = INT8_MAX;

    for(int i =0; i<numVertices;i++)
    {
        for(int j=0;j<numVertices; j++)
        {
            if(!existeAdjacencia(i,j))
            {
                pesos[i][j] = infinito;
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
                //Define que o menor caminho de um vértice pra ele mesmo é 0
                if(i==j)
                L[i][j] = 0;

                //Checa se o custo da origem até o nó atual é menor do que o custo 
                //saindo da origem e passando por um nó intermediário até o nó atual
                
                if(((L[i][k] < infinito) && (L[k][j] < infinito))) 
                {
                    if(L[i][j] > (L[i][k] + L[k][j]))
                    {
                        L[i][j] = L[i][k] + L[k][j];

                        //Salvando maior numero pra enviar pra formatação da matriz
                        if(L[i][j]>maior)
                        maior = L[i][j];

                        //Salvando menor numero  negativo pra enviar pra formatação da matriz
                        if(L[i][j]<menor)
                        menor = L[i][j];

                    }
                }
              
            }
        }
    }
    
    cout << "Floyd caminho minimo entre todos os pares de vertices" << endl;
    cout << "" << endl;

    //Imprimindomenores caminhos para cada par de vértices
    imprimeMatriz(L, maior, menor);
    
}
void Grafo::buscaLargura(int origem)
{
    int i;
    bool *visitados = new bool[numVertices];

    //marca todos os vertices como nao visitados
    for (i = 0; i < numVertices; i++)
    {
        visitados[i] = false;
    }

    list<int> fila;

    //marca o vertice atual como visitado e coloca na fila
    visitados[origem] = true;
    fila.push_back(origem);

    while (!fila.empty())
    {
        int j;
        //tira da fila e printa
        origem = fila.front();
        cout << origem << " ";
        fila.pop_front();

        for (i = 0; i < vertices[origem].tamanho(); i++)
        {
            j = vertices[origem].get(i);
            if (!visitados[j] && j > origem)
            { //verifico se n foi visitado e se é filho
                visitados[j] = true;
                fila.push_back(j);
            }
        }
    }
    
}

// Algoritmo Recursivo Profundidade
// Recebe o índece de um nó e o vetor de visitados
void Grafo::PROF(int index, bool visitados[])
{

    // Marca o vértice index como visitado
    visitados[index] = true;

    // Imprime o vértice
    cout << "Vértice visitado: " << index << endl;

    int j = 0;

    // Pega o primeiro adjacente do vertice index
    int verticeAdjacente = vertices[index].get(0);

    // Percorre todos os adjacentes ao vértice index no while
    while (verticeAdjacente != -1)
    {
        // Se o adjacente não foi visitado
        if (!visitados[verticeAdjacente])
        {

            // Então visita o adjaente
            Grafo::PROF(verticeAdjacente, visitados);

        }

        // Próximo adjacente
        j++;
        verticeAdjacente = vertices[index].get(j);
    }
}

// Busca em Profundidade
void Grafo::buscaProf()
{
    // Vetor de Visitos
    bool visitados[numVertices];

    // Marcou todos como não visitados
    for (int i = 0; i < numVertices; i++)
    {
        visitados[i] = false;
    }

    // Percorre todos os vertices do grafo
    for (int i = 0; i < numVertices; i++)
    {
        // Se o vertice não foi visitado
        if (!visitados[i])
        {
            // Então visita o vértice i
            Grafo::PROF(i, visitados);
        }
    }
}


void Grafo::ordenaCandidatos (int candidatos[], int graus[])
{
     int k, j, aux;

     for ( k = 0; k < numVertices ; k++)
    {
        for ( j = k; j < numVertices; j++)
        {
            //cout <<"k | j : " << k << " " << j << endl;
            
            //cout<<"grau k | grau j : " << graus[k] << " " << graus[j] << endl;
            if (graus[candidatos[k]] < graus[candidatos[j]])
            {
                aux = candidatos[k];
                candidatos[k] = candidatos[j];
                candidatos[j] = aux;
            }

        }
    }
}

int Grafo::algoritmoGulosoSD()
{
    //Conjunto C de vértics candidatos a solução
    int * C = new int[numVertices];

    int* G = new int[numVertices];

    //Conjunto W de vértices que são adjacentes aos vértices escolhidos
    //para solução

    bool *W = new bool[numVertices];
    int contemplados = 0;

    //Conjunto S solução onde marcamos true os vértices que compõe a solução
    bool *S = new bool[numVertices];
    int solucao = 0;

    //Vetor para guardar os vértices do conjunto solução
    int *resultado = new int[numVertices];

    //Inicializando vetor de candidatos com os vértices do grafo e
    //inicializando o vetor de graus dos vértices do grafo com seus respectivos graus
    //(tamanho da lista de adjacência)
    for (int i=0; i<numVertices; i++)
    {
        C[i] = i;
        G[i] = vertices[i].tamanho();
        //cout << "G["<<i <<"]" << G[i] << endl;
    }

    //Ordenando candidatos em ordem descrescente de grau
    ordenaCandidatos(C, G);

    /*for (int i=0; i<numVertices; i++)
    {
        cout << C[i] << endl;
    */

    //Inicializando vetor de vértices contemplados e vertices da solução com false
    for (int i=0; i<numVertices; i++)
    {
        W[i] = false;
        S[i] = false;
    }

    int j = 0; //iteração do conjunto solução

    int k = 0;//iteração dos candidatos

  
    while(contemplados < numVertices)
    {
        //Escolhendo um candidato
        int Vc = C[k];
        
        //cout << "k: " << k << endl;

        //cout << " candidato: " << Vc << endl;

        //cout << "vertices: " << numVertices << endl;

        //Se o vértice escolhido ainda não foi contemplado (ou não está no conjunto solução)
        if((W[Vc]==false))
        {
            //Vértice vai pro conjunto solução 
            S[Vc] = true;
            resultado[j] = Vc;
            j++;
            solucao = j;


            W[Vc] = true;
            contemplados++;


            //cout << "contemplados: " << contemplados << endl;


            //Adicionando adjacentes do vertice escolhido ao conjunto W de contemplados
            for(int m=0; m < (vertices[Vc].tamanho()); m++)
            {
                //vertice adjacente Va
                int Va = vertices[Vc].get(m);
                //cout << "m = " << m << endl;
                //cout << "Va = " << Va << endl;

                //Se existe a adjacência e o vértice ainda não foi contemplado
                
                if(( Va!=-1) && (W[Va]==false))
                {
                        //cout << "[" << Va << "]" << "[" << Vc << "]" << endl;
                        W[Va] = true;
                       // cout << "adjacentes: true" << endl;

                       // cout << "W["<< Va << "] = " << W[Va] << endl;
                        contemplados++;
                }
                //else cout << "adjacentes: false" << endl;

                //cout << "contemplados: " << contemplados << endl;
                
          
            }            
        }
        //Na iteração, se o vértice da vez foi contemplado mas ainda não está no conjunto solução 
        //temos que verificar se o mesmo possui algum vizinho que ainda não foi contemplado, 
        //então assim podemos adicionar esse vértice ao conjunto solução e seu adjacente passa
        //a ser contemplado
        
        else if(S[Vc] == false)
        {
            //Contador para guardar os vizinhos do vértice Vc que foram contemplados
            int cont = 0;

            for(int m=0; m < (vertices[Vc].tamanho()); m++)
            {
                //vertice adjacente Va
                int Va = vertices[Vc].get(m);

                //cout << "m = " << m << endl;
                //cout << "Va = " << Va << endl;
                
                    if(( Va!=-1) && W[Va]==false)
                    {
                        //cout << "[" << Va << "]" << "[" << Vc << "]" << endl;
                        cont++;                    

                        W[Va] = true;
                        //cout << "adjacente de "<< Vc << ": true" << endl;
                        contemplados++;
                    }

                //cout << "contemplados: " << contemplados << endl;
                
          
            }
            if(cont!=0)
            {
                S[Vc] = true;
                resultado[j] = Vc;    
                j++;
                solucao = j;

            }
        }
        

        //cout << "vertices e contemplados: " << numVertices << " " <<  contemplados << endl;

        k++;
    }


    cout << "" << endl;
    cout << "Subconjunto dominante: " <<endl;

    cout << '[' ;
    for(int i=0; i<solucao; i++)
    {
        cout << resultado[i] ;
        if(i!=solucao-1)
        {
            cout << ',' ;
        }
    }

    cout << ']' << endl;


    delete C;
    delete G;
    delete W;
    delete S;
    return solucao;
}


int naoContemplados(bool contemplados[], int numVertices){
    int resultado = 0;
    for(int i = 0; i < numVertices; i++){
        if (!contemplados[i]){
            resultado++;
        }
    }
    return resultado;
}

void Grafo::algoritmoGulosoRandomizado(float alfa, int semente){
    
    
    srand(time(0)+semente); //Definindo semente da função rand

    //Contadores e limites
    int iteracoes = 0;
    int LIMITE_ITERACOES = 500;
    int iteracoesSemMelhora = 0;
    int LIMITE_ITERACOES_SEM_MELHORA = 200;

    int* possivelSolucao;                               //Possível solução encontrada em um iteração
    int* melhorSolucao;                                 //Melhor solução encontrada
    int tamanhoDaMelhorSolucao = algoritmoGulosoSD();   //Quantidade de vértice na melhor solução (Começa como o resultado do algoritmo guloso)
    int* candidatos;                                    //Candidatos a entrar na possível solução
    bool* contemplados;                                 //Vetor que indica os vértices contemplados
    int numeroDeNaoContemplados;
    int numeroMaximoDeCandidatos;

    int* vetorOrdenadoDeVertices = new int[numVertices]; //Vetores ordenados para facilitar a execução
    int* vetorDeGraus = new int[numVertices];

    int posicaoCandidato;
    int posicaoPossivelSolucao;

    for (int i=0; i<numVertices; i++)
    {
        vetorOrdenadoDeVertices[i] = i;
        vetorDeGraus[i] = vertices[i].tamanho();
    }
    ordenaCandidatos(vetorOrdenadoDeVertices, vetorDeGraus);//Ordenando vetores em ordem decrescente de graus
    
    while(iteracoes < LIMITE_ITERACOES && iteracoesSemMelhora < LIMITE_ITERACOES_SEM_MELHORA){
        //Iniciando vetores e variáveis
        possivelSolucao = new int[numVertices];
        contemplados = new bool[numVertices];
        for(int i = 0; i < numVertices; i++){
            possivelSolucao[i] = -1;
            contemplados[i] = false;
        }
        posicaoPossivelSolucao = 0;
        numeroDeNaoContemplados = naoContemplados(contemplados, numVertices);
        //Obtendo solução
        while(numeroDeNaoContemplados > 0){
            //Limitando a quantidade de candidatos para alfa*numeroDeNaoContemplados arredondado para cima caso possuir decimal
            numeroMaximoDeCandidatos = ceil((alfa*(numeroDeNaoContemplados)));
            candidatos = new int[numeroMaximoDeCandidatos];
            posicaoCandidato = 0;
            //Obtendo candidatos (primeiro do vetor ordenado que não estão contemplados)
            for(int i = 0; (i < numVertices) && (posicaoCandidato < numeroMaximoDeCandidatos); i++){
                if(!contemplados[vetorOrdenadoDeVertices[i]]){
                    candidatos[posicaoCandidato] = vetorOrdenadoDeVertices[i];
                    posicaoCandidato++;
                }
            }
            //Obtendo vértice aleatório dos candidatos
            if(posicaoCandidato > 1){
                possivelSolucao[posicaoPossivelSolucao] = candidatos[(rand()%(posicaoCandidato))];
            } else {
                possivelSolucao[posicaoPossivelSolucao] = candidatos[0];
            }
            //Atualizando contemplados
            contemplados[possivelSolucao[posicaoPossivelSolucao]] = true;
            for(int i = 0; i < vertices[possivelSolucao[posicaoPossivelSolucao]].tamanho(); i++){
                contemplados[vertices[possivelSolucao[posicaoPossivelSolucao]].get(i)] = true;
            }
            posicaoPossivelSolucao++;
            numeroDeNaoContemplados = naoContemplados(contemplados, numVertices);
            delete [] candidatos;
        }
        //Comparando possivel solução com a melhor solução
        if(tamanhoDaMelhorSolucao > posicaoPossivelSolucao){
            melhorSolucao = possivelSolucao;
            tamanhoDaMelhorSolucao = posicaoPossivelSolucao;
            iteracoesSemMelhora = 0;
            cout << "NOVA MELHOR SOLUÇÃO:\n[";
            for(int i = 0; i < posicaoPossivelSolucao; i++){
                if(i == posicaoPossivelSolucao - 1){
                    cout << melhorSolucao[i];
                } else {
                    cout << melhorSolucao[i] << ",";
                }
            }
            cout << "]" << endl;;
        } else {
            iteracoesSemMelhora++;
        }
        iteracoes++;
        delete [] possivelSolucao;
    }
}