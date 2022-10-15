#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <random>
#include <stdlib.h>

#include "./header/ProductReview.h"
#include "./header/ManipulandoArquivo.h"
#include "./header/AlgoritmosOrdenacao.h"

using namespace std;

//// Funcoes de Teste

void printArrayProd(ProductReview* arr, int tam)
{
    for (int i = 0; i < tam; i++)
        arr[i].print();
}

void printArray(int* arr, int tam)
{
    for (int i = 0; i < tam; i++)
        cout << arr[i] << endl;
}

//// Etapa 1: Processamento dos dados

// https://www.kaggle.com/datasets/saurav9786/amazon-product-reviews

/*
    void ProductReview::print(): imprime os dados de um registro do tipo ProductReview.
    
    void createBinary(std::string& path): gera o arquivo binário correspondente ao arquivo 
    CSV armazenado no caminho passado como parâmetro. O arquivo binário deve ser gerado no 
    mesmo diretório do arquivo CSV.

    void getReview(int i): acessa diretamente o i-ésimo registro do arquivo binário e o 
    imprime na tela. O valor de i deve ser recebido via parâmetro. Considere i = 0 como o 
    índice do primeiro registro.

    ProductReview* import(int n): importa n registros aleatórios do arquivo binário e 
    retorna um vetor contendo estes registros.
*/


void createBinary(string path)
{
    ManipulandoArquivo arq;
    arq.preProcessamento(path);
    system("clear");
}

void getReview(int i)
{
    ManipulandoArquivo arq;
    ProductReview prod;

    prod = arq.findRegistryPosition(i);
    prod.print();
}

ProductReview* import(int n)
{
    ManipulandoArquivo arq;
    ProductReview* produtos = new ProductReview[n];

    // CHAVE RANDOMICA
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, n);

    for (int i = 0; i < n; i++)
        produtos[i] = arq.findRegistryPosition(distr(gen));

    return produtos;
}

//// Etapa 2: Análise de algoritmos de ordenação

/*
    Nesta etapa, você irá comparar o desempenho de diferentes algoritmos de ordenação 
    quando aplicados sobre os dados pré-processados. O seu programa deverá seguir os 
    seguintes passos:

    1. importar conjuntos de N registros aleatórios do arquivo binário gerado pelo 
       pré-processamento

    2. realizar a ordenação desses registros, utilizando como chave de ordenação userId. 
       Durante a ordenação, deverão ser computados o total de comparações de chaves e o 
       total de movimentações de chaves. Além disso, o tempo de execução do algoritmo 
       deverá ser medido.
    
    Para gerar as estatísticas de desempenho, você deverá executar os passos acima para M 
    diferentes conjuntos de N registros aleatórios. Minimamente, utilize M=3. Ao final, 
    compute as médias de cada uma das métricas (comparações, movimentações e tempo). 
    Salve todos os resultados obtidos em um arquivo saida.txt, contendo tanto os resultados 
    individuais quanto a média final.

    Você deverá realizar a simulação descrita acima para os seguintes valores de N:

        10.000
        50.000
        100.000
        500.000
        1.000.000
    
    Faça a leitura dessas informações a partir de um arquivo chamado input.dat.
*/

void sort(ProductReview *vet, int n, int methodId)
{
    AlgoritmosOrdenacao algoritmo;

    switch (methodId)
    {
        case 0:
            algoritmo.quickSort(vet, n);
            break;
        case 1:
            algoritmo.mergeSort(vet, n);
            break;
        case 2:
            algoritmo.algumAlgoritmo(vet, n);
            break;
    }
}

void testarAlgoritmo(int methodId, int M, int* N, int sizeN)
{
    ManipulandoArquivo arq;
    ProductReview* vet;
    string metodosOrdenacao[3] = {"Quick Sort", "Merge Sort", "Algum Algoritmo"};

    cout << "ANALISE ALGORITMO ORDENACAO: " << metodosOrdenacao[methodId] << endl;
    
    for (int j = 0; j < sizeN; j++)
    {
        for (int i = 0; i < M; i++)
        {
            vet = import(N[j]);
            sort(vet, N[j], methodId);
        }    

        // Gerando resultados parciais ..., true)
        arq.gerarResultado(N[j], methodId, j * M, true);
    }
    
    // Gerando resultado final ..., false)
    arq.gerarResultado(N[0], methodId, 0, false);
    arq.resetTempFile();

    remove("./files/temp.bin");
    delete[] vet;
}

void etapaOrdenacao(int M)
{
    system("clear");
    cout << "EXECTANDO ETAPA DE ORDENACAO" << endl;

    ManipulandoArquivo arq;
    int size;
    int* N = arq.readInput(size);
    
    arq.clearOutputFile();

    // Testando Algoritmo 0 - Quick Sort
    testarAlgoritmo(0, M, N, size);

    // Testando Algoritmo 1 - Quick Sort
    // testarAlgoritmo(1, M, N, size);

    // Testando Algoritmo 2 - Quick Sort
    // testarAlgoritmo(2, M, N, size);

    delete[] N;
}

void etapaHash()
{
    system("clear");
    cout << "EXECUTANDO ETAPA DE HASH" << endl;
}

void interface()
{
    int option;
    do
    {
        system("clear");
        cout << "Escolha qual etapa sera executada: " << endl <<
                "1. Ordenacao" << endl <<
                "2. Hash" << endl <<
                "0. Quit" << endl << "> " << flush;
        cin >> option;
        
        if (option == 1)
            etapaOrdenacao(3);
        else if (option == 2)
            etapaHash();

    } while (option != 0);
}

int main(int argc, char* arg[])
{
    string PATH;
    ManipulandoArquivo arq;

    if (argc == 2) 
        PATH = arg[1];

    createBinary(PATH);
    interface();

    return 0;
}